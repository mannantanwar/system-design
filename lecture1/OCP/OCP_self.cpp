#include<bits/stdc++.h>
using namespace std;

class Product{
    private:
    double price;
    
    public :
    string name;
    Product( string name , double price){
        this-> name = name ;
        this->price = price ;
    }
    double getPrice(){
        return this->price;
    }
    void setPrice(double price){
        this->price= price;     
    }
};

class ShoppingCart{
    private:
    vector<Product*>products;
    
    public:
    vector<Product*>getProducts(){
        return products;
    }
    void addProduct(Product * product){
        products.push_back(product);
    }
    // shopping cart will only cater the function of calculating the price 
    double calculateTotalPrice(){
        double total = 0;
        for(auto &product:products){
            total+=product->getPrice();
        }
        return total;
    }
};
// another class to print the invoice and anothe r to execute save to db 
class PrintInvoice{
    private :
    ShoppingCart *cart ;

    public :
    PrintInvoice(ShoppingCart * cart){
        this->cart = cart;
    }
    void print(){
        vector<Product*>products = cart->getProducts();
        for( auto & product: products){
            cout<<"printing invoice for the "<<product->name<<endl;
        }
    }
};


// class SaveToDb{
//     private :
//     ShoppingCart *cart ;

//     public :
//     SaveToDb(ShoppingCart* cart){
//         this->cart = cart;
//     }
//     void Save(){
//         cout<<"saving this product to the db ";
//     }
// };

//commenting out he code for thesave to db as what if we got the method for the save to mongo db , save to file or save to sql 
// sotechnically we wuld be thinkng that this is the same logic only ie of the saving so this should come inside the same class as the Single responsibility princliple states
// but acc to th open cose princlipe w eshould not change ouyr old code if we are adding a new featuire or anything ,, the change in the existing code should be minimal 

// now making a persistance interface or an abstract class we call it in c++
class Persistence{
    private :
    ShoppingCart *cart;

    public: 
    virtual void save(ShoppingCart * cart)=0;
};
class SaveToDb : public Persistence{
    public : 
    
    void save (ShoppingCart * cart)override{
        cout<<"saving to DB"<<endl;
    }
};
class SaveToMongo : public Persistence{
    public : 
    void save (ShoppingCart * cart)override{
        cout<<"saving to Mongo"<<endl;
    }
};
class SaveToFile : public Persistence{
    public : 
    void save (ShoppingCart * cart)override{
        cout<<"saving to file"<<endl;
    }
};
// ab agar koi new functionality ayga bhi to dobara se inherit krke override krdenge ise purani classes me change bilkul nhi hoga and thus we can maintan the open close principle 
int main(){
    ShoppingCart * cart = new ShoppingCart();
    cart->addProduct(new Product("cap",20));
    cart->addProduct(new Product("hat",20));
    cart->addProduct(new Product("mop",20));
    cart->addProduct(new Product("bat",20));

    PrintInvoice * invoice = new PrintInvoice(cart);
    Persistence * saveToDb = new SaveToDb();
    Persistence * savToMongo = new SaveToMongo();
    Persistence * saveToFile = new SaveToFile();

    invoice->print();
    saveToDb->save(cart);
    savToMongo->save(cart);
    saveToFile->save(cart);
    return 0;
}
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
            cout<<"printing invoice for the "<<product->name;
        }
    }
};
class SaveToDb{
    private :
    ShoppingCart *cart ;

    public :
    SaveToDb(ShoppingCart* cart){
        this->cart = cart;
    }
    void Save(){
        cout<<"saving this product to the db ";
    }
};

int main(){
    ShoppingCart * cart = new ShoppingCart();
    cart->addProduct(new Product("cap",20));
    cart->addProduct(new Product("hat",20));
    cart->addProduct(new Product("mop",20));
    cart->addProduct(new Product("bat",20));

    PrintInvoice * invoice = new PrintInvoice(cart);
    SaveToDb * save = new SaveToDb(cart);

    invoice->print();
    save->Save();
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

// building the sys des of zomato over here , built the uml and high level diagrams in the notebook so you can refer that

// just a basic overview over here for al of the classes
// to sbse phelekya aata hai isme ,
/*
REstraunt class ->
name , id , vector<Menuitem * > menu;

Menu Item class->
string dish ,double price

RestrauntManager->
vector<REstraunt*> restranuts , addREstraunt(), search byLoc()

cart->
Restraunt *res, vector<MEnuItem*> items, caclTotal()

user->
cart * cart , name ,address...

now the turn of the payment interface
payment strategy ->
pay() strategy DP because there are diff alogos for this on class and we are separating those from the main class itself

Netbanking-> pay()
upi()-> pay()
credit/debitCard-> pay()

// now comes the omst impo class of them all

order class->
Restraunt * res , int id, vector<MenuItem*>itms , PAyementStrategy * modeOfPayment,  gettype();

subclass->
deliveryOrder->getType()
DineInOrder-> getType()

// now since order has varioous types ca n i carete a order factory which will be providing me with the order objects based on the type of  order ??

orderFactory-> createOrder()

scheduledOrder-> createOrder()
nowOrder->createOrder()

// now can we say we can keep one ordrManager too for managing all of the orders
OrderManager->
vector<Order*>orders, addOrdder()


this is all for now , lets jump int ocodig and we will figure out on the way


*/
class MenuItem
{
private:
    string name;
    double price;
    string itemCode;

public:
    MenuItem(string name, double price, string itemCode)
    {
        this->name = name;
        this->price = price;
        this->itemCode = itemCode;
    }

    string getName()
    {
        return name;
    }
    void setName(string name)
    {
        this->name = name;
    }
    double getPrice()
    {
        return price;
    }
    void setPrice(double price)
    {
        this->price = price;
    }
    string getItemCode()
    {
        return itemCode;
    }
    void setItemCode(string itemCode)
    {
        this->itemCode = itemCode;
    }
};
class Restraunt
{
private:
    vector<MenuItem *> menu;

public:
    string name;
    string location;

    vector<MenuItem *> getMenu()
    {
        return menu;
    }
    void setMenu(vector<MenuItem *> menu)
    {
        this->menu = menu;
    }
    void addMenuItem(MenuItem *item)
    {
        menu.push_back(item);
    }
};
// now we have to make one restraunt manager which will be managing the restraunts
// the reason that we make the restraunt manager singleton is that there should be
// a single person who should be managing the orders otherwise there might be a confusion as
// whom to go to when we have to manage the order , which manager has order number 103 , which manager should be assigned the order number 105 etc etc ....
class RestrauntManager
{
    // class ko singleton bnane ke liye uska constructor private bnadete hai na
private:
    vector<Restraunt *> restraunts;
    static RestrauntManager *instance;
    RestrauntManager()
    {
        cout << "this is the restraunt managers constructor " << endl;
    }

public:
    // is method ko static isliye banaya hai kyuki agar static hi likhte to ye object se related bnjata method , since we want to get the object only from this method thus had to make it static

    static RestrauntManager *getInstance()
    {
        return instance;
    }
    // all of the crud operations on the restraunts or for the restraunts can be performed here
    void addRestraunt(Restraunt *restraunt)
    {
        restraunts.push_back(restraunt);
    }
    vector<Restraunt *> getRestraunts()
    {
        return restraunts;
    }
    vector<Restraunt *> searchByLocation(string loc)
    {
        vector<Restraunt *> result;
        transform(loc.begin(), loc.end(), loc.begin(), ::tolower);
        for (auto r : restraunts)
        {
            string rl = r->location;
            transform(rl.begin(), rl.end(), rl.begin(), ::tolower);
            if (rl == loc)
            {
                result.push_back(r);
            }
        }
        return result;
    }
    // and many more operations can be performed here
};
// initialising the static variable
RestrauntManager *RestrauntManager::instance = new RestrauntManager();

class Cart
{
public:
    vector<MenuItem *> items;
    Restraunt *restraunt;

    int totalPrice()
    {
        int count = 0;
        for (auto &item : items)
        {
            count += item->getPrice();
        }
        return count;
    }

    void clearCart()
    {
        items.clear();
    }

    Restraunt *getRestaurant()
    {
        return restraunt;
    }
    void setRestaurant(Restraunt *restraunt)
    {
        this->restraunt = restraunt;
    }
    void addItem(MenuItem *item)
    {
        items.push_back(item);
    }
};

// now the task of the cart and user to be created
class User
{
private:
    Cart *cart;

public:
    string name;
    int id;

    void addToCart(Restraunt *restraunt, MenuItem *item)
    {
        cart->items.push_back(item);
        cart->restraunt = restraunt;
    }

    Cart *getCart()
    {
        return cart;
    }
    void setCart(Cart *cart)
    {
        this->cart = cart;
    }
};

// now time for the payment gateway
/*
payment krne ki kaafi saari strategies
hoskti hai like upi credit card of netbanking so we will be using strategy desgin pattern as
same thing ke liye we have different algorithms
*/
class Payment
{
public:
    virtual void pay(double total) = 0;
};

class NetBanking : public Payment
{
public:
    void pay(double total) override
    {
        cout << "paying thourgh the netbanking " << endl;
    }
};
class UPI : public Payment
{
public:
    void pay(double total) override
    {
        cout << "paying thourgh the UPI " << endl;
    }
};
class Card : public Payment
{
public:
    virtual void pay() = 0;
};
class DebitCard : public Card
{
public:
    void pay() override
    {
        cout << "payng through debit card" << endl;
    }
};
class CreditCard : public Card
{
public:
    void pay() override
    {
        cout << "paying thorugh the credit card " << endl;
    }
};
// now the payement interface areall comlete new we have make the order class
// orderFactory . orderanager
class Order
{
private:
    vector<MenuItem *> orderItems;
    Restraunt *restraunt;
    Payment *pay;
    User *user;
    double total;

public:
    Order()
    {
        this->restraunt = nullptr;
        this->pay = nullptr;
        this->user = nullptr;
        this->total = 0;
    }

    vector<MenuItem *> getOrderItems()
    {
        return orderItems;
    }
    void setOrderItems(vector<MenuItem *> orderItems)
    {
        this->orderItems = orderItems;
    }

    Restraunt *getRestraunt()
    {
        return restraunt;
    }
    void setRestraunt(Restraunt *restraunt)
    {
        this->restraunt = restraunt;
    }

    Payment *getPayment()
    {
        return pay;
    }
    void setPayment(Payment *pay)
    {
        this->pay = pay;
    }

    User *getUser()
    {
        return user;
    }
    void setUser(User *user)
    {
        this->user = user;
    }

    double getTotal()
    {
        return total;
    }
    void setTotal(double total)
    {
        this->total = total;
    }

    void calcTotal()
    {
        for (MenuItem *item : orderItems)
        {
            total += item->getPrice();
        }
    }
    bool processPayment()
    {
        if (pay)
        {
            pay->pay(total);
            return true;
        }
        else
        {
            cout << "Please choose a payment mode first" << endl;
            return false;
        }
    }

    virtual void getType() = 0;
};

class DeliveryOrder : public Order
{
public:
    DeliveryOrder() {}

    void getType() override
    {
        cout << "order type is delivery" << endl;
    }
};
class PickupOrder : public Order
{
public:
    PickupOrder() {}

    void getType() override
    {
        cout << "order type is pickup" << endl;
    }
};

// now have to crate a factory that would e giving out the object of this class
class OrderFactory
{
public:
    virtual Order *createOrder(string type) = 0;
};

class ScheduledOrder : public OrderFactory
{
public:
    Order *createOrder(string type) override
    {
        if (type == "delivery")
            return new DeliveryOrder();
        else
            return new PickupOrder();
    }
};
class NowOrder : public OrderFactory
{
public:
    Order *createOrder(string type) override
    {
        if (type == "delivery")
            return new DeliveryOrder();
        else
            return new PickupOrder();
    }
};

// same reasoning as RestrauntManager - single place responsible for tracking every order
class OrderManager
{
private:
    vector<Order *> orders;
    static OrderManager *instance;
    OrderManager()
    {
        cout << "this is the order managers constructor " << endl;
    }

public:
    static OrderManager *getInstance()
    {
        return instance;
    }
    void addOrder(Order *order)
    {
        orders.push_back(order);
    }
    vector<Order *> getOrders()
    {
        return orders;
    }
};
OrderManager *OrderManager::instance = new OrderManager();


class TomatoApp
{
public:
    TomatoApp()
    {
        initializeRestaurants();
    }

    void initializeRestaurants()
    {
        Restraunt *restraunt1 = new Restraunt();
        restraunt1->addMenuItem(new MenuItem("Pizza", 250, "P"));
        restraunt1->addMenuItem(new MenuItem("Burger", 20, "B"));

        Restraunt *restraunt2 = new Restraunt();
        restraunt1->addMenuItem(new MenuItem("Samosa", 50, "S"));
        restraunt1->addMenuItem(new MenuItem("Idli", 25, "I"));

        RestrauntManager *restManager = RestrauntManager::getInstance();
        restManager->addRestraunt(restraunt1);
        restManager->addRestraunt(restraunt2);

        // Add other sample restaurants...
    }

    vector<Restraunt *> searchRestaurants(const string &location)
    {
        return RestrauntManager::getInstance()->searchByLocation(location);
    }

    void selectRestaurant(User *user, Restraunt *restraunt)
    {
        Cart *cart = user->getCart();
        cart->setRestaurant(restraunt);
    }

    void addToCart(User *user, const string &itemCode)
    {
        Restraunt *restraunt = user->getCart()->getRestaurant();
        if (!restraunt)
        {
            cout << "Please select a restaurant first." << endl;
            return;
        }
        for (const auto &item : restraunt->getMenu())
        {
            if (item->getItemCode() == itemCode)
            {
                user->getCart()->addItem(item);
                break;
            }
        }
    }

    Order *checkoutNow(User *user, const string &orderType, Payment *paymentStrategy)
    {
        return checkout(user, orderType, paymentStrategy, new NowOrder());
    }

    Order *checkoutScheduled(User *user, const string &orderType, Payment *paymentStrategy, const string &scheduleTime)
    {
        return checkout(user, orderType, paymentStrategy, new ScheduledOrder());
    }

    Order *checkout(User *user, const string &orderType,
                    Payment *paymentStrategy, OrderFactory *orderFactory)
    {
        if (user->getCart()->items.empty())
            return nullptr;

        Cart *userCart = user->getCart();
        Restraunt *orderedRestaurant = userCart->getRestaurant();
        vector<MenuItem *> itemsOrdered = userCart->items;
        double totalCost = userCart->totalPrice();

        Order *order = orderFactory->createOrder(orderType);
        OrderManager::getInstance()->addOrder(order);
        return order;
    }

    void payForOrder(User *user, Order *order)
    {
        bool isPaymentSuccess = order->processPayment();

        // clear user cart if payment is successful.
        if (isPaymentSuccess)
        {
            user->getCart()->clearCart();
        }
    }

    void printUserCart(User *user)
    {
        cout << "Items in cart:" << endl;
        cout << "------------------------------------" << endl;
        for (const auto &item : user->getCart()->items)
        {
            cout << item->getItemCode() << " : " << item->getName() << " : Rs " << item->getPrice() << endl;
        }
        cout << "------------------------------------" << endl;
        cout << "Grand total : Rs " << user->getCart()->totalPrice() << endl;
    }
};

int main()
{
    // Create TomatoApp Object
    TomatoApp* tomato = new TomatoApp();

    // Simulate a user coming in (Happy Flow)
    User* user = new User();
    user->id = 101;
    user->name = "Aditya";
    cout << "User: " << user->name << " is active." << endl;

    // User searches for restaurants by location
    vector<Restraunt*> restaurantList = tomato->searchRestaurants("Delhi");

    if (restaurantList.empty()) {
        cout << "No restaurants found!" << endl;
        return 0;
    }
    cout << "Found Restaurants:" << endl;
    for (auto restaurant : restaurantList) {
        cout << " - " << restaurant->name << endl;
    }

    // User selects a restaurant
    tomato->selectRestaurant(user, restaurantList[0]);

    cout << "Selected restaurant: " << restaurantList[0]->name << endl;

    // User adds items to the cart
    tomato->addToCart(user, "P1");
    tomato->addToCart(user, "P2");

    tomato->printUserCart(user);

    // User checkout the cart
    Order* order = tomato->checkoutNow(user, "Delivery", new UPI());
    
    // User pay for the cart. If payment is success, notification is sent.
    tomato->payForOrder(user, order);

    // Cleanup Code.
    delete tomato;
    delete user;
    
    return 0;

    
}

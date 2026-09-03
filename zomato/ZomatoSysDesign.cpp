#include<bits/stdc++.h>
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


#include<bits/stdc++.h>
using namespace std;

// in this file we will be studying the factory design pattern 
// basically factpry pattern is th epattern which creates the things (objects ) it gives us the objects according to our needs

// coding the simple factory method first ..
class Burger{
    public:
    virtual void prepare()=0;
};
class PremiumBurger : public Burger{
    public:
    void prepare() override{
        cout<<"preparing premium Burgers"<<endl;
    }
};
class StandardBurger : public Burger{
    public:
    void prepare() override{
        cout<<"preparing standard Burgers"<<endl;
    }
};
class ExclusiveBurger : public Burger{
    public:
    void prepare() override{
        cout<<"preparing exclusive Burgers"<<endl;
    }
};
class PremiumWheatBurger : public Burger{
    public:
    void prepare() override{
        cout<<"preparing premium wheat Burgers"<<endl;
    }
};
class StandardWheatBurger : public Burger{
    public:
    void prepare() override{
        cout<<"preparing standard wheat Burgers"<<endl;
    }
};
class ExclusiveWheatBurger : public Burger{
    public:
    void prepare() override{
        cout<<"preparing exclusive wheat Burgers"<<endl;
    }
};

// no wthe factpry calss which takes an input and the gves us the genrated burger of that type 
class BurgerFactory{
    public :
    
   virtual Burger* createBurger(string type)=0;
};

class SinghBurger : public BurgerFactory{
    public:
    Burger* createBurger( string type){
        if(type =="premium"){
            Burger * burger = new PremiumBurger();
            return burger;
        }
        else if(type == "exclusive"){
            Burger * burger = new ExclusiveBurger();
            return burger;
        }
        else{
            // standard
            Burger * burger = new StandardBurger();
            return burger;
        }
    }
};
class KingBurger : public BurgerFactory{
    public:
    Burger* createBurger( string type){
        if(type =="premium"){
            Burger * burger = new PremiumWheatBurger();
            return burger;
        }
        else if(type == "exclusive"){
            Burger * burger = new ExclusiveWheatBurger();
            return burger;
        }
        else{
            // standard
            Burger * burger = new StandardWheatBurger();
            return burger;
        }
    }
};

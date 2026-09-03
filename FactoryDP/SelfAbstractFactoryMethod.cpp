#include<bits/stdc++.h>
using namespace std;

// now isem ky anew hai ki pehle sirf ek hi product bnrha tha now ek se zyada product bhi bnskta hai 

class Product{
    public:
    virtual void prepare()=0;
};
class Burger: public Product{
    public :
    virtual void prepare()=0;
};
class GarlicBread: public Product{
    public : 
    virtual void prepare()=0;
};

// types of the burgers below --->>>

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

// now time for the garlic bread 
class PremiumGarlicBread : public GarlicBread{
    public:
    void prepare() override{
        cout<<"preparing premium GarlicBreads"<<endl;
    }
};
class StandardGarlicBread : public GarlicBread{
    public:
    void prepare() override{
        cout<<"preparing standard GarlicBreads"<<endl;
    }
};
class ExclusiveGarlicBread : public GarlicBread{
    public:
    void prepare() override{
        cout<<"preparing exclusive GarlicBreads"<<endl;
    }
};
class PremiumWheatGarlicBread : public GarlicBread{
    public:
    void prepare() override{
        cout<<"preparing premium wheat GarlicBreads"<<endl;
    }
};
class StandardWheatGarlicBread : public GarlicBread{
    public:
    void prepare() override{
        cout<<"preparing standard wheat GarlicBreads"<<endl;
    }
};
class ExclusiveWheatGarlicBread : public GarlicBread{
    public:
    void prepare() override{
        cout<<"preparing exclusive wheat GarlicBreads"<<endl;
    }
};

//now time to create the factory 
class Factory{
    public:
    virtual Product* create()=0;
};
class BurgerFactory: public Factory{
    public:
    virtual Product * create()=0;
};
class GarlicBreadFactory: public Factory{
    public:
    virtual Product * create()=0;
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
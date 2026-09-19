#include<bits/stdc++.h>
using namespace std;

// is design pattern me what we use is whenever we have to create a new object we have to do the expensive operations 
// so insetad of doing those operations evrytime what we do is create a copy constructor 
// thats how we skip the expensive operatiopns 
/// one issue for the non primitive variables it creates a shallow copy so changig for one could maybe the change of all of them 
class Clonable{
    public: 
    virtual Clonable* clone() const=0;
};
class NPC : public Clonable{
    public:
    string name;
    int health;
    int attack;
    int defense;

    NPC(const string& name, int health, int attack, int defense) {
        // call database
        // complex calc
        // this is the expensive ops constructor 
        this->name = name; 
        this->health = health; 
        this->attack = attack; 
        this->defense = defense;
        cout << "Setting up template NPC '" << name << "'\n";
    }

    NPC(const NPC& other){
        name = other.name;
        health = other.health;
        attack = other.attack;
        defense = other.defense;
        cout << "Cloning NPC '" << name << "'\n";
    }
    Clonable * clone() const override{// const over in the end of the function call means that on the object on which it is called we cannot makes changes to that object 
        return new NPC(*this);
    }
    void describe() {
        cout << "NPC " << name  << " [HP=" << health  << " ATK=" << attack 
             << " DEF=" << defense << "]\n";
    }

    // setters to tweak the clone…
    void setName(const string& n) { 
        name = n;
    }
    void setHealth(int h) { 
        health = h;
    }
    void setAttack(int a) {
         attack = a; 
    }
    void setDefense(int d){ 
        defense = d;
    }
};
int main(){
    NPC* alien = new NPC("Alien", 30, 5, 2);

    // 2) quickly clone + tweak as many variants as you like:
    NPC* alienCopied1 = dynamic_cast<NPC*>(alien->clone());
        // we hve to the dynamic casting of the bobject as the dynamic casting is used when we have to change the object form its preant to the child object

    alienCopied1->describe();

    NPC* alienCopied2 = dynamic_cast<NPC*>(alien->clone());
    alienCopied2->setName("Powerful Alien");
    alienCopied2->setHealth(50);

}
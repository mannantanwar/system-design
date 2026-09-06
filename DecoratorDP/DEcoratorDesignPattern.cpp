#include<bits/stdc++.h>
using namespace std;

/*
basically is design pattern me hota kya hai instead of making lass pe calss pe class har baar 
jab bhi koi new ofrm chiaye hoti hai we tend to make new class and then try inhrit the base calss to make sense 
of the property 
 so instead of making new classes evrytime we try to make a decorator jisme ki new class ko bnane ke bajaye we tend 
 to make a decorator on top of the object that decorator is also an abstract but pt make the give or needed functionality w
 whta we do s niherit that decorator and also we store the rferance of the main class too so this pattern uses both inheritance and compostion 

 it will become more clear to you when we write the code 
*/

// we will be taking the example of the mario game how it levell ups by gaining hieght then gun etc etc 

class Character{
    public: 
    virtual void getAbility()=0;
};
class Mario : public Character{
    public: 
    void getAbility() override {
        cout<<"Mario";
    }
};

// now the decorator parrt 
class CharacterDecorator: public Character{
    protected :
    // iske andar character ka obj bhi store hoga jisse ki hum iska controller bhi call krva paye and uks aghet abilities bhi 
    Character * character;

    public: 
    CharacterDecorator(Character * character){
        this-> character  = character;
    }

};

class getFire : public CharacterDecorator{
    public : 
    getFire(Character * character )
    // this is the way we call the constructor of the base from the child class 
        : CharacterDecorator(character){}
    
    void getAbility ()override {
        character->getAbility() ;
        cout<<"  with the Fire abilities ";
    }
};
class Heightup : public CharacterDecorator{
    public : 
    Heightup(Character * character )
    // this is the way we call the constructor of the base from the child class 
        : CharacterDecorator(character){}
    
    void getAbility ()override {
        character->getAbility() ;
        cout<<"  with the height abilities ";
    }
};
class getGun : public CharacterDecorator{
    public : 
    getGun(Character * character )
    // this is the way we call the constructor of the base from the child class 
        : CharacterDecorator(character){}
    
    void getAbility ()override {
        character->getAbility() ;
        cout<<"  with the gun abilities ";
    }
};

int main(){
    Character * mario = new Mario();
    // mario->getAbility();
    Heightup * heightAbility= new Heightup(mario);

    // heightAbility-> getAbility();

    // now the mario with all of the abilities combined
    getGun * gunAbility = new getGun(heightAbility);
    getFire * fireAbility = new getFire(gunAbility);

    fireAbility->getAbility();
    return 0;
}
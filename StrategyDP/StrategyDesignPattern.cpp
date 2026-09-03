#include<bits/stdc++.h>
using namespace std;

// in this we are gonna look at the strategy design pattern ,

// DRY - > Do not repeat yourself 

// here the main problem is that lets say there is a robot and inside it has methods talk() , walk()

// now we can inherit this class and make a walkable robot and similarly talable , also there is method named projection of robo in the robot class which is overriden by its subclasses

// lets say we make companion robo , worker robo both can walk and talk , so no problem in inherting the robot class , but now what happens is that a new robo appears 
// named sparraow it can fly now , but th eparent class robo doesnt have the fly function ->> so we decide to write the fly func only for the child class ,
// now what if another robs come which have the fly type method so we would have to declare the fly method separatly for the another class, but what if more of them come , the we would be breaking our DRY principle as we would be repreating urself , we have to separate the chainging part of the code from the non changing part of the code , 

// another case now if we made another classs with the abtract method fly , but now one robo came fly with jet , now will we be making the another class  for it given the saem scenarios as above ??
// eg - > 
/*
                              ┌─────────────────────┐
                              │       Robot         │
                              ├─────────────────────┤
                              │ walk() {}           │
                              │ talk() {}           │
                              │ projection() {}     │
                              └─────────┬───────────┘
                                        │
                       ┌────────────────┼────────────────┐
                       │                │                │
                       ▼                ▼                ▼
              ┌────────────────┐ ┌────────────────┐ ┌────────────────┐
              │   Flyable R    │ │  Companion R   │ │   Worker R     │
              ├────────────────┤ ├────────────────┤ ├────────────────┤
              │ fly() {}       │ │ projection(){} │ │ projection(){} │
              └───────┬────────┘ └────────────────┘ └────────────────┘
                      │
                ┌─────┴─────┐
                │           │
                ▼           ▼
       ┌────────────────┐  ┌────────────────┐
       │   SparrowR     │  │     CrowR      │
       ├────────────────┤  ├────────────────┤
       │ projection(){} │  │ projection(){} │
       └────────────────┘  └────────────────┘
                      ◇
                      │
                      │
                      ▼
              ┌────────────────┐
              │    JetRobot    │
              ├────────────────┤ // ye alag se override krta hai to iski ab kya alag class banaye fly with jets then isko inherit krenge objects ???
              │ fly() {}       │
              └────────────────┘
*/


// sol is strategy desgn pattern 

class Robo{
    private:
    FlyableRobot * flyy;
    WalkableRobot* walkk;
    TalkableRobot * talkk;

    public:
    Robo(WalkableRobot * walk,TalkableRobot * talk,FlyableRobot* fly  ){
        this->flyy= fly;
        this->talkk= talk;
        this->walkk= walk;
    }
    
    virtual void projection()=0;

    void walk(){
        walkk->walk();
    }
    void talk(){
        talkk->talk();
    }
    void fly(){
        flyy->fly();
    }
};


class WalkableRobot {
public:
    virtual void walk() = 0;
    virtual ~WalkableRobot() {}
};

class NormalWalk : public WalkableRobot {
public:
    void walk() override { 
        cout << "Walking normally..." << endl; 
    }
};

class NoWalk : public WalkableRobot {
public:
    void walk() override { 
        cout << "Cannot walk." << endl; 
    }
};


// --- Strategy Interface for Talk ---
class TalkableRobot {
public:
    virtual void talk() = 0;
    virtual ~TalkableRobot() {}
};

// --- Concrete Strategies for Talk ---
class NormalTalk : public TalkableRobot {
public:
    void talk() override { 
        cout << "Talking normally..." << endl; 
    }
};

class NoTalk : public TalkableRobot {
public:
    void talk() override { 
        cout << "Cannot talk." << endl; 
    }
};

// --- Strategy Interface for Fly ---
class FlyableRobot {
public:
    virtual void fly() = 0;
    virtual ~FlyableRobot() {}
};

class NormalFly : public FlyableRobot {
public:
    void fly() override { 
        cout << "Flying normally..." << endl; 
    }
};

class NoFly : public FlyableRobot {
public:
    void fly() override { 
        cout << "Cannot fly." << endl; 
    }
};

// now making the robos 
// --- Concrete Robot Types ---
class CompanionRobot : public Robo {
public:
    CompanionRobot(WalkableRobot* w, TalkableRobot* t, FlyableRobot* f)
        : Robo(w, t, f) {}

    void projection() override {
        cout << "Displaying friendly companion features..." << endl;
    }
};

class WorkerRobot : public Robo {
public:
    WorkerRobot(WalkableRobot* w, TalkableRobot* t, FlyableRobot* f)
        : Robo(w, t, f) {} // calling the constructor of the base class forom the constructor of the chld class

    void projection() override {
        cout << "Displaying worker efficiency stats..." << endl;
    }
};

int main(){

    Robo *robot1 = new CompanionRobot(new NormalWalk(), new NormalTalk(), new NoFly());
    robot1->walk();
    robot1->talk();
    robot1->fly();
    robot1->projection();

    cout << "--------------------" << endl;

    Robo *robot2 = new WorkerRobot(new NoWalk(), new NoTalk(), new NormalFly());
    robot2->walk();
    robot2->talk();
    robot2->fly();
    robot2->projection();
    return 0;
}


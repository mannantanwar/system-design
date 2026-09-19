#include <bits/stdc++.h>
using namespace std;
class VendingMachine;
class VendingMachineState
{
public:
    virtual VendingMachineState *insertCoin(int coin, VendingMachine* machine) = 0;
    virtual VendingMachineState *refill(unordered_map<string, int> quantities, VendingMachine* machine) = 0;
    virtual VendingMachineState *getItem(string item, VendingMachine* machine) = 0;
    virtual VendingMachineState *dispense(string item, VendingMachine* machine) = 0;
    virtual VendingMachineState *returnCoin(VendingMachine* machine) = 0;
    virtual void getState() = 0;
};
class Item{
    public:
    string name ;
    int quantity;
    Item(string name , int quantity){
        this->name = name ;
        this->quantity = quantity;
    }
};

// can make this singleton
class VendingMachine
{
private:
    static VendingMachine* instance ;
    VendingMachineState *state;
    static vector<Item * > items;
    int insertedCoins ;
    string selectedItem;

    // State objects (pre-built singletons, shared for the lifetime of the machine)
    VendingMachineState* noCoinState;
    VendingMachineState* hasCoinState;
    VendingMachineState* dispenseState;
    VendingMachineState* soldOutState;

    VendingMachine(); // defined out-of-line below, once all four states are fully defined

public:
    // Getters for states
    VendingMachineState* getNoCoinState() {
        return noCoinState;
    }
    VendingMachineState* getHasCoinState() {
        return hasCoinState;
    }
    VendingMachineState* getDispenseState() {
        return dispenseState;
    }
    VendingMachineState* getSoldOutState() {
        return soldOutState;
    }

    void addItem(string name, int quantity) {
        items.push_back(new Item(name, quantity));
    }
    vector<Item*>& getItems() {
        return items;
    }

    void setInsertedCoins(int coins) {
        insertedCoins = coins;
    }
    int getInsertedCoins() {
        return insertedCoins;
    }

    void setSelectedItem(string item) {
        selectedItem = item;
    }
    string getSelectedItem() {
        return selectedItem;
    }

    static VendingMachine* getInstance() {
        if(instance == nullptr)instance= new VendingMachine();
        return instance;
    }
    VendingMachineState *insertCoin(int coin)
    {
        return state = state->insertCoin(coin, this);
    }
    VendingMachineState *refill(unordered_map<string, int>quantities )
    {
        return state = state->refill(quantities, this);
    }
    VendingMachineState *getItem(string item)
    {
        return state = state->getItem(item, this);
    }
    VendingMachineState *dispense(string item)
    {
        return state = state->dispense(item, this);
    }
    VendingMachineState *returnCoin()
    {
        return state = state->returnCoin(this);
    }
    void getState(){
        state->getState();
    }
};
VendingMachine* VendingMachine::instance = nullptr;
vector<Item*> VendingMachine::items;

// now making the concrete states
// each state gets the machine passed in, and transitions by asking the machine
// for one of its pre-built singleton states - no "new SomeOtherState()" needed,
// so none of these classes depend on another one being fully defined yet
class NoCoinState : public VendingMachineState
{
public:
    VendingMachineState *insertCoin(int coin, VendingMachine* machine) override{
        cout<<"coin inserted: "<<coin<<endl;
        machine->setInsertedCoins(coin);
        return machine->getHasCoinState();
    }
    VendingMachineState *refill(unordered_map<string, int> quantities, VendingMachine* machine) override {
        // refill i am allowing only in the no coin state
        for(auto & entry : quantities){
            machine->addItem(entry.first, entry.second);
        }
        return this;
    }
    VendingMachineState *getItem(string item, VendingMachine* machine) override {
        cout<<"insert a coin first"<<endl;
        return this;
    }
    VendingMachineState *dispense(string item, VendingMachine* machine) override {
        cout<<"insert a coin first"<<endl;
        return this;
    }
    VendingMachineState *returnCoin(VendingMachine* machine) override {
        cout<<"no coin to return"<<endl;
        return this;
    }
    void getState() override {
        cout<<"NoCoinState"<<endl;
    }
};
class HasCoinState : public VendingMachineState
{
public:
    VendingMachineState *insertCoin(int coin, VendingMachine* machine) override {
        machine->setInsertedCoins(coin+machine->getInsertedCoins());
        cout<<"added extra coins"<<endl;
        return this;
    }
    VendingMachineState *refill(unordered_map<string, int> quantities, VendingMachine* machine) override {
        cout<<"cannot refill while a coin is inserted"<<endl;
        return this;
    }
    VendingMachineState *getItem(string item, VendingMachine* machine) override {
        for(auto &it : machine->getItems()){
            if(it->name == item){
                if(it->quantity > 0){
                    cout<<"dispensing "<<item<<endl;
                    machine->setSelectedItem(item);
                    return machine->getDispenseState();
                }
                cout<<item<<" is out of stock"<<endl;
                return this;
            }
        }
        cout<<item<<" not found"<<endl;
        return this;
    }
    VendingMachineState *dispense(string item, VendingMachine* machine) override {
        cout<<"select an item first"<<endl;
        return this;
    }
    VendingMachineState *returnCoin( VendingMachine* machine) override {
        cout<<"returning coin "<<machine->getInsertedCoins()<<endl;
        machine->setInsertedCoins(0);
        return machine->getNoCoinState();
    }
    void getState() override {
        cout<<"HasCoinState"<<endl;
    }
};
class DispenseState : public VendingMachineState
{
public:
    VendingMachineState *insertCoin(int coin, VendingMachine* machine) override {
        cout<<"please wait, dispensing"<<endl;
        return this;
    }
    VendingMachineState *refill(unordered_map<string, int> quantities, VendingMachine* machine) override {
        cout<<"cannot refill while dispensing"<<endl;
        return this;
    }
    VendingMachineState *getItem(string item, VendingMachine* machine) override {
        cout<<"already dispensing an item, please wait"<<endl;
        return this;
    }
    VendingMachineState *dispense(string item, VendingMachine* machine) override {
        string selected = machine->getSelectedItem();
        for(auto &it : machine->getItems()){
            if(it->name == selected){
                it->quantity--;
                cout<<"dispensing "<<it->name<<", "<<it->quantity<<" left"<<endl;
                break;
            }
        }
        machine->setInsertedCoins(0);
        for(auto &it : machine->getItems()){
            if(it->quantity > 0) return machine->getNoCoinState();
        }
        cout<<"machine is now sold out"<<endl;
        return machine->getSoldOutState();
    }
    VendingMachineState *returnCoin(VendingMachine* machine) override {
        cout<<"cannot return coin while dispensing"<<endl;
        return this;
    }
    void getState() override {
        cout<<"DispenseState"<<endl;
    }
};
class SoldOutState : public VendingMachineState
{
public:
    VendingMachineState *insertCoin(int coin, VendingMachine* machine) override {
        cout<<"sold out, coin returned"<<endl;
        return this;
    }
    VendingMachineState *refill(unordered_map<string, int> quantities, VendingMachine* machine) override {
        for(auto &entry : quantities){
            machine->addItem(entry.first, entry.second);
        }
        return machine->getNoCoinState();
    }
    VendingMachineState *getItem(string item, VendingMachine* machine) override {
        cout<<"sold out"<<endl;
        return this;
    }
    VendingMachineState *dispense(string item, VendingMachine* machine) override {
        cout<<"sold out"<<endl;
        return this;
    }
    VendingMachineState *returnCoin(VendingMachine* machine) override {
        cout<<"nothing to return"<<endl;
        return this;
    }
    void getState() override {
        cout<<"SoldOutState"<<endl;
    }
};

// now that all four states are fully defined, VendingMachine's constructor can build them
VendingMachine::VendingMachine(){
    noCoinState = new NoCoinState();
    hasCoinState = new HasCoinState();
    dispenseState = new DispenseState();
    soldOutState = new SoldOutState();
    state = noCoinState;
    insertedCoins = 0;
}

int main()
{
    VendingMachine *vm = VendingMachine::getInstance();

    unordered_map<string,int> stock;
    stock["coke"] = 1;
    stock["chips"] = 2;
    vm->refill(stock);
    vm->getState();            // NoCoinState

    vm->insertCoin(10);
    vm->getState();            // HasCoinState
    vm->getItem("coke");
    vm->dispense("coke");      // last coke, but chips still left -> back to NoCoinState
    vm->getState();            // NoCoinState

    vm->insertCoin(10);
    vm->insertCoin(20);
    vm->getItem("coke");       // coke now out of stock
    vm->returnCoin();
    vm->getState();            // NoCoinState

    vm->insertCoin(10);
    vm->getItem("chips");
    vm->dispense("chips");

    vm->insertCoin(10);
    vm->getItem("chips");
    vm->dispense("chips");     // last chips -> whole machine sold out
    vm->getState();            // SoldOutState

    vm->insertCoin(10);        // rejected, sold out
    vm->refill(stock);         // refilling brings it back to NoCoinState
    vm->getState();            // NoCoinState

    return 0;
}

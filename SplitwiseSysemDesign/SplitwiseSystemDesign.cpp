#include<bits/stdc++.h>
using namespace std;

// first of all lets make the notification service the observer and the observable
class observer{
    virtual void update(string message)=0;
};
class User : public observer{
    private :
    string userId; 
    string email;
    string name ;
    public :
    unordered_map<string , double>balances; // stores tehe the userid-> amount that this userid ows this much to curr suer id or ows this much from curr user id
    void update(string message ) override{
        cout<<message<<endl;
    }
    string getId(){
        return userId;
    }
    void setId(string userId){
        this->userId = userId;
    }
    string getEmail(){
        return email;
    }
    void setEmail(string email){
        this->email = email;
    }
    string getName(){
        return name;
    }
    void setName(string name){
        this->name = name;
    }
};
class Split{
    public:
    string userId; 
    double amount;
    Split(string userId, double amount){
        this->userId= userId;
        this->amount = amount;
    }
};
class SplitStrategy{
    public:
    virtual vector<Split*> calcSplit(vector<Split *>&splits, double amount)=0;
};
class SplitType{
    // this is supposed to be a enum class
    // to mmake the class enum what we do is make the constructor private and make the obekct public static and final 
    private:
    string type;
    SplitType(string type){
        this->type = type;
    }
    public:
    static SplitType* const EQUAL ;
    static  SplitType * const PERCENTAGE ;
    static  SplitType * const EXACT ;
    static SplitType* getType(string type){
        transform(type.begin(), type.end(), type.begin(), ::tolower);
        type.erase(remove(type.begin(), type.end(), ' '),type.end());
        if( type == "equal")return EQUAL;
        else if( type =="exact")return EXACT;
        else if(type == "percentage")return PERCENTAGE;
        else return NULL;
    }
};
SplitType * const SplitType::EQUAL= new SplitType("EQUAL");
SplitType * const SplitType::EXACT= new SplitType("EXACT");
SplitType * const SplitType::PERCENTAGE= new SplitType("PERCENTAGE");

class EqualSplitStrategy : public SplitStrategy{
        vector<Split*> calcSplit(vector<Split *>&contributions , double amount) override{
        
        double share = amount/(double)contributions.size();
        //upar har bnde ka share aagya 
        vector<Split*> splits;
        for(Split * split : contributions){
            splits.push_back(new Split(split->userId, split->amount-share));
        }
        // ab is split ko map me bhi to update krna hai 
        return splits;
    }
};
class PercentageSplitStrategy : public SplitStrategy{
    public:
    vector<Split*> calcSplit(vector<Split*>&splits , double amount ) override{

    }
};
class ExactSplitStrategy : public SplitStrategy{
    public:
    vector<Split*> calcSplit(vector<Split*>&splits , double amount ) override{

    }
};
class SplitFactory{
    public :
    static SplitStrategy* createSplit(SplitType * type) {
        if(type == SplitType::EQUAL){
            return new EqualSplitStrategy();
        }
        else if(type == SplitType::EXACT){
            return new ExactSplitStrategy();
        }
        else if(type == SplitType::PERCENTAGE){
            return new PercentageSplitStrategy();
        }
        else return NULL;
    }
};

class Expense{
    private :
    string id ;
    string desc;
    double amount ;
    vector<Split *>splits;
    SplitStrategy *splitStrategy ;
    public : 
    Expense(vector<Split*> splits, double total ,SplitType * type){
        this->amount =  total;
        this->splitStrategy = SplitFactory::createSplit(type);
        this->splits = splitStrategy->calcSplit(splits,amount);
    }
    string getId(){
        return id;
    }
    void setId(string id){
        this->id = id;
    }
    string getDesc(){
        return desc;
    }
    void setDesc(string desc){
        this->desc = desc;
    }
    double getAmount(){
        return amount;
    }
    void setAmount(double amount){
        this->amount = amount;
    }
    vector<Split*> getSplits(){
        return splits;
    }
    void setSplits(vector<Split*> splits){
        this->splits = splits;
    }
    SplitStrategy* getSplitStrategy(){
        return splitStrategy;
    }
    void setSplitStrategy(SplitStrategy* splitStrategy){
        this->splitStrategy = splitStrategy;
    }
};
class DebtSimplifier{
    public :
    static void Simplify( unordered_map<string ,double>&netValue, unordered_map<string,User*>members){
        // ab iske andar humko algo implement krni hai 
        // sbse pehle isme har bnde ka net owe and net debt nikal lete hai ??
        // unordered_map<string , double>deneHai; // -
        // unordered_map<string , double>leneHai; // +
        // ab map ke andar total value is stored ie net give or take // ab 
        // ab sbko settle kaie kru ki pata lg jaye ki 
        
        priority_queue<pair<double,string>>maxHeap;
        priority_queue<pair<double,string>,vector<pair<double,string>>, greater<pair<double,string>>>minHeap;
        for(auto &entry : netValue) {
            string id = entry.first;
            double amount = entry.second;
            if(amount<0){
                minHeap.push({amount,id});
            }
            else maxHeap.push({amount,id});
        }

        while(!minHeap.empty() && !maxHeap.empty()){
            // is ops me merko netValue map bhi update krna hai
            auto maxi = maxHeap.top();
            auto mini = minHeap.top();
            string maxiName = members[maxi.second]->getName();
            string miniName = members[mini.second]->getName();
            double diff = (maxi.first - abs(mini.first));
            // if diff less than zero then i means mini vala element is bgger 
            if(diff<0){
                cout<<miniName<<" should pay "<<maxiName<<" "<<abs(maxi.first)<<endl;
                double balanceLeft = mini.first+maxi.first;
                cout<<maxiName<<" settled"<<endl;
                maxHeap.pop();
                minHeap.pop();
                minHeap.push({balanceLeft,mini.second});
            }
            else if(diff>0){
                cout<<miniName<<" should pay "<<maxiName<<" "<<abs(mini.first)<<endl;
                double balanceLeft = diff;
                cout<<miniName<<" settled"<<endl;
                maxHeap.pop();
                minHeap.pop();
                maxHeap.push({balanceLeft,maxi.second});
            }
            else{
                // dono ek dusre ko dedo
                cout<<miniName<<" should pay "<<maxiName<<" "<<abs(mini.first)<<endl;
                cout<<miniName<<" settled"<<endl;
                cout<<maxiName<<" settled"<<endl;
                minHeap.pop();
                maxHeap.pop();
            }
        }
        // everyone who had a nonzero balance has now been fully settled by the loop above -
        // just zero out netValue in one pass rather than writing it on every transaction
        for(auto &entry : netValue){
            entry.second = 0;
        }
        // algo khtm
    }
};
class Group {
private:
    string groupId;
    string groupName;
    
    vector<Expense *> expenses;
    unordered_map<string,double>netValue;
    unordered_map<string,User*> members;
public:
    Group(string name ,unordered_map<string,User*>u ){
        this->members=u;
        this->groupName = name;
        this->groupId= name;
    }
    // Move the function call inside a method
    void simplifyGroupDebts() {
        DebtSimplifier::Simplify(netValue, members);
    }
    void updateGlobalMap(Expense* expense){
        for(Split* split: expense->getSplits()) {
            netValue[split->userId]+=split->amount;
        }
    }
    void addExpense(vector<Split*>contributions, double total , string type){
        //assuming we have to  include all of the memebrs for no can be scaled later 
        Expense * expense = new Expense(contributions, total , SplitType::getType(type));
        expenses.push_back(expense);
        
        updateGlobalMap(expense);
    }
    void SettleExpenses(){
        simplifyGroupDebts();
    }
    void getGroupExpenses(){
        // print just all the expenses over 
        for(Expense * expense: expenses){
            cout<<expense->getDesc()<<endl;
            cout<<"people who paid along with the amount are .."<<endl;
            for(Split * split:expense->getSplits()){
                cout<<members[split->userId]->getName()<<" "<<split->amount<<endl;
            }
        }
        // printed all of the list 
    }
    void addMember(User* user){
        members[user->getId()]= user;
    }
    bool removeMember(User *user){
        for( auto &entry :netValue){
            // now iam traversing the map insid ethe string -> map
            double amount = entry.second;
            if(amount!=0){
                cout<< "cant remove this member untill its dues are cleared "<<endl;
                return false;
            }
        }
        //meaning all the dues are cleared
        // members array me se remove krdo and map me se saari entries hata do 
        return true;// or we cn make a new map removed members usme daaldenge usko or basically valid funcaio banaskte hai kisi bh useer ko processkrne se pehle validitiy check krlenge 
    }
    void notifyAll( string message){
        for(auto &entry :members){
            User* user = entry.second;
            user->update(message);
        }
    }
    void notify(User *u , string message){
        for(auto &entry :members){
            User* user = entry.second;
            if(user==u){
                user->update(message);
                break;
            }
        }
    }
    string getId(){
        return this->groupId;
    }
    void printNetBalances(){
        for(auto &entry : netValue){
            cout<<members[entry.first]->getName()<<": "<<entry.second<<endl;
        }
    }
};
class SplitwiseBasic{
    private:
    vector<User*> users;
    unordered_map<string,Group*>groups;
    public:
    void createGroup(string name ,unordered_map<string,User*>u){
        Group * group = new Group(name , u);
        groups[group->getId()]=group;
    }
    void addUser(User* user){
        users.push_back(user);
    }
    void addUserToGroup(User * user,string groupId ){
        groups[groupId]->addMember(user);
    }
    bool removeUserFromGroup(User * user, string groupId){
        return groups[groupId]->removeMember(user);
    }

    void addExpenseToGroup(vector<Split*>contributors,double amount, string type, string groupId){
        groups[groupId]->addExpense(contributors,amount ,type);
    }

    void displayAllexpensesofAgroup(string groupId){
        groups[groupId]->getGroupExpenses();
    }
    
    void settleExpensesOfAgroup(string groupId){
        groups[groupId]->SettleExpenses();
    }
    void printNetBalancesOfGroup(string groupId){
        groups[groupId]->printNetBalances();
    }
};
int main (){
    SplitwiseBasic app;

    // 1) create 6 users
    vector<User*> people;
    vector<string> names = {"mannan", "lakshay", "nikhil", "yash", "aditya", "anushka"};
    for(int i=0;i<6;i++){
        User* u = new User();
        u->setId("u"+to_string(i+1));
        u->setName(names[i]);
        u->setEmail(names[i]+"@example.com");
        people.push_back(u);
        app.addUser(u);
    }
    User *mannan=people[0], *lakshay=people[1], *nikhil=people[2], *yash=people[3], *aditya=people[4], *anushka=people[5];

    // 2) put all 6 into one group
    unordered_map<string,User*> members;
    for(User* u : people){
        members[u->getId()] = u;
    }
    app.createGroup("Trip", members);

    // 3) Dinner (600): mannan pays 200, lakshay pays 400 - split among mannan/lakshay/nikhil/yash
    vector<Split*> dinner;
    dinner.push_back(new Split(mannan->getId(), 200));
    dinner.push_back(new Split(lakshay->getId(), 400));
    dinner.push_back(new Split(nikhil->getId(), 0));
    dinner.push_back(new Split(yash->getId(), 0));
    app.addExpenseToGroup(dinner, 600, "equal", "Trip");

    // 4) Cab (300): nikhil pays - split among nikhil/yash/aditya
    vector<Split*> cab;
    cab.push_back(new Split(nikhil->getId(), 300));
    cab.push_back(new Split(yash->getId(), 0));
    cab.push_back(new Split(aditya->getId(), 0));
    app.addExpenseToGroup(cab, 300, "equal", "Trip");
    app.printNetBalancesOfGroup("Trip");

    // 5) Hotel (1200): priya pays for the whole group - split among all 6
    vector<Split*> hotel;
    for(User* u : people){
        hotel.push_back(new Split(u->getId(), u==anushka ? 1200 : 0));
    }
    app.addExpenseToGroup(hotel, 1200, "equal", "Trip");
    app.printNetBalancesOfGroup("Trip");

    // 6) show all expenses before settling
    cout<<"===== Expenses before settling =====\n";
    app.displayAllexpensesofAgroup("Trip");

    // 7) settle up
    cout<<"\n===== Settling debts =====\n";
    app.settleExpensesOfAgroup("Trip");

    // 8) confirm everyone nets to zero
    cout<<"\n===== Net balances after settling (should all be 0) =====\n";
    app.printNetBalancesOfGroup("Trip");

    return 0;
}
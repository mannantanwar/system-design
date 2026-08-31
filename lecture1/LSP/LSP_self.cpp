#include<bits/stdc++.h>
using namespace std;

class Accounts{
    public :
    virtual void deposit(int balance )=0;
    virtual void withdraw()=0;
};

class SavingsAccount: public Accounts{
    private :
    int balance;
    public:
    SavingsAccount(){
        this->balance = 0;
    }
    
    void deposit(int amount)override{
        this->balance += amount;
        cout<<" added the money in the savingsAccount"<<endl;
    }

    void withdraw()override{
        cout<<" balance for the savings account is "<<this->balance<<endl;
    }

};
class CurrentAccount: public Accounts{
    private :
    int balance;
    public:
    CurrentAccount(){
        this->balance = 0;
    }
    
    void deposit(int amount)override{
        this->balance += amount;
        cout<<" added the money in the currentAccount"<<endl;
    }

    void withdraw()override{
        cout<<" balance for the current account is "<<this->balance<<endl;
    }

};
class FixedDepositAccount: public Accounts{
    private :
    int balance;
    public:
    FixedDepositAccount(){
        this->balance =0 ;
    }
    
    void deposit(int amount)override{
        this->balance += amount;
        cout<<" added the money in the FixedDepositAccount"<<endl;
    }

    void withdraw()override{
       throw logic_error("Withdrawal not allowed in Fixed Term Account!");
    }
};

class Client{
    private :
    vector<Accounts*>accounts;
    public:
    void addAccount(Accounts * account){
        // what if we write this->accounts.push_back()????
        accounts.push_back(account);
    }
    void processTransactions() {
        for (Accounts* acc : accounts) {
            acc->deposit(1000);  //All accounts allow deposits

            //Assuming all accounts support withdrawal (LSP Violation)
            try {
                acc->withdraw();
            } catch (const logic_error& e) {
                cout << "Exception: " << e.what() << endl;
            }
        }
    }
};

int main(){
    Accounts * savings = new SavingsAccount();
    Accounts * current = new CurrentAccount();
    Accounts * fd= new FixedDepositAccount();

    Client client ;
    client.addAccount(savings);
    client.addAccount(current);
    client.addAccount(fd);

    client.processTransactions();


}

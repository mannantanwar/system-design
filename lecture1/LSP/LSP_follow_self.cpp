#include<bits/stdc++.h>
using namespace std;


//now as according to the LSP the sub or child  class should always extend the base class 
 // but inthis code the FD account doesnt extend the bse class instead it nrows it down si that means the FD should inherit the Account class inturn 
 // right ?? yes we can make 2 interfaces alike the withawable acc and non withdrawable accounts
class NonWithdrawableAccounts{
    public:
    virtual void deposit(int balance )=0;
};
class WithdrawableAccounts : public NonWithdrawableAccounts{
    public :
    virtual void withdraw()=0;
};

class SavingsAccount: public WithdrawableAccounts{
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
class CurrentAccount: public WithdrawableAccounts{
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
class FixedDepositAccount: public NonWithdrawableAccounts{
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
};

class Client{
    private :
    vector<NonWithdrawableAccounts*>nonWithdrawableAccounts;
    vector<WithdrawableAccounts*>withdrawableAccounts;

    public:
    Client( vector<WithdrawableAccounts*> withdrawableAccounts, 
        vector<NonWithdrawableAccounts*> depositOnlyAccounts) { 
        this->withdrawableAccounts = withdrawableAccounts; 
        this->nonWithdrawableAccounts = depositOnlyAccounts;
    }

    void processTransactions() {
        for (WithdrawableAccounts* acc : withdrawableAccounts) {
            acc->deposit(1000);
            acc->withdraw(); 
        }
        for (NonWithdrawableAccounts* acc : nonWithdrawableAccounts) {
            acc->deposit(5000);
        }
    }
};

int main(){
    WithdrawableAccounts * savings = new SavingsAccount();
    WithdrawableAccounts * current = new CurrentAccount();
    NonWithdrawableAccounts * fd = new FixedDepositAccount();

    vector<WithdrawableAccounts*> withdrawableAccounts = {savings, current};
    vector<NonWithdrawableAccounts*> nonWithdrawableAccounts = {fd};

    Client client(withdrawableAccounts, nonWithdrawableAccounts);
    client.processTransactions();
}

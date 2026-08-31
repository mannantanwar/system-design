#include<iostream>
#include<vector>
using namespace std;
class Accounts{
    public:
    virtual void deposit(double amount)=0;
    virtual void withdraw(double amount)=0;
};

class SavingAccount:public Accounts{
    private: double balance;
    public :
    SavingAccount(){
        balance=0;
    }
    void deposit(double price){
        balance+=price;
        cout<<"Savings account balance has been updated by " <<price<<" amount";
    }

    void withdraw(double price){
        if(balance- price <0){
            cout<<"insufficient funds in savings account";
        }
        else{
            //subtrance hoskta hai 
            balance= balance - price;
            cout<<"price has been deducted frm your savings acc as you withdrawed"; 
        }
    }

};
class CurrentAccount: public Accounts{
    private: double balance;
    public :
    CurrentAccount(){
        balance=0;
    }
    void deposit(double price){
        balance+=price;
        cout<<"Savings account balance has been updated by " <<price<<" amount";
    }

    void withdraw(double price){
        if(balance- price <0){
            cout<<"insufficient funds in current account";
        }
        else{
            //subtrance hoskta hai 
            balance= balance - price;
            cout<<"price has been deducted frm your current acc as you withdrawed"; 
        }
    }
};
class FixedTermAccount:public Accounts{

    private:
    double balance;

    public:
    FixedTermAccount(){
        balance =0;
    }
    void deposit(double amount) {
        balance += amount;
        cout << "Deposited: " << amount << " in Fixed Term Account. New Balance: " << balance << endl;
    }

    void withdraw(double amount) {
        throw logic_error("Withdrawal not allowed in Fixed Term Account!");
    }
};

class BankClient{
    private:
    vector<Accounts*>accs;
    public:
    BankClient(vector<Accounts*>accounts){
        this->accs=accounts;
    }
    void Process_Transaction(){
        for (Accounts* it: accs){
            try
            {
                it->deposit(500);
            }
            catch(const exception& e)
            {
                cout << e.what() << '\n';
            }
            
        }
    }
};

int main(){
    vector<Accounts*>accounts;
    accounts.push_back(new SavingAccount());
    accounts.push_back(new CurrentAccount());
    accounts.push_back(new FixedTermAccount());

    BankClient* Client= new BankClient(accounts);
    Client->Process_Transaction();
    return 0;
}



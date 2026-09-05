#include<bits/stdc++.h>
using namespace std;

class Adaptee{
    public:
    void specialReq(){
        cout<< " this is the special req for the 3rd party application "<<endl;
    }
};
class CurrentClass{
    public:
    virtual void req(){
        cout<<"this is how the the current req takes place and it has to interact with the 3rd party application which is incompatible "<<endl;
    }
};
class Adapter : public CurrentClass{
    private:
    Adaptee * adaptee;
    public :
    Adapter(Adaptee * adaptee){
        this->adaptee= adaptee;
    }
    void req() override{
        adaptee->specialReq();
        cout<<"adapting the both the req and submitting the adapted response as required by the current class"<<endl;
    }
};
class Client{
    public:
    void getReports(CurrentClass * curr , string data){
        curr->req();
    }
};
int main(){
    Adaptee * adaptee = new Adaptee();
    CurrentClass * adapter = new Adapter(adaptee);
    Client * client= new Client();
    client->getReports(adapter , "hello bhai");
    return 0;
}
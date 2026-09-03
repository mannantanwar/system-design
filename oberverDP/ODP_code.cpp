#include<bits/stdc++.h>
using namespace std;

class IChannel{
    public:
    virtual void addSubscriber( ISubscriber * subscriber)=0;
    virtual void removeSubscriber( ISubscriber * subscriber)=0;
    virtual void notifyAll()=0;
};
class ISubscriber{
    public :
    virtual void update()=0;
};

class Subscriber: public ISubscriber{
    private :
    IChannel * channel;
    public :
    Subscriber(IChannel * channel){
        this->channel = channel;
    }

    void update(){
        cout<<"reading the new value of the channel "<<endl;
    }
};

class Channel : public IChannel{
    private :
    int latestValue;
    vector<ISubscriber *> subscribers;
    public : 
    void addSubscriber(ISubscriber * subscriber) override{
        subscribers.push_back(subscriber);
    }
    void removeSubscriber(ISubscriber * subscriber) override{
        auto it = find(subscribers.begin(), subscribers.end(), subscribers );
        if(it!=subscribers.end()){
            subscribers.erase(it);
        }
        return ;
    }

    void notifyAll() override{
        for (auto & subscriber : subscribers){
            subscriber->update();
        }
    }

    void uploadLatestData(int latestValue){
        this-> latestValue= latestValue;
        // the latest value has been updated now notify the others 
        notifyAll();
    }
};

int main(){
    Channel *youTube  = new Channel();
    Subscriber *sub1= new Subscriber(youTube);
    Subscriber *sub2= new Subscriber(youTube);
    Subscriber *sub3= new Subscriber(youTube);

    youTube->addSubscriber(sub1);
    youTube->addSubscriber(sub2);
    youTube->addSubscriber(sub3);

    youTube->uploadLatestData(100);
    return 0;
}


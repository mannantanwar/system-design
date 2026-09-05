#include<bits/stdc++.h>
using namespace std;

/*
 Notiication system 

 plug and play 
 extndible - > sms , email , pop upo 
 notification me can be bale add the features dynamically 
 store all of the notification and also add the logging feature too 
*/

class Notification{
    public :
    virtual string getContent()=0;
};
class SimpleNotification : public Notification{
    private :
    string text;
    public:
    SimpleNotification(string text){
        this->text = text;
    }
    string getContent() override {
        return this->text;
    }
};

// now defining the decorator for the nottification clas s
class NotificationDecorator: public Notification{
    protected :
    Notification * notification;
    public: 
    NotificationDecorator(Notification * notification){
        this->notification = notification;
    }
};

// there can be two types pf the decorator one cam add the timestmp andthe other can add the signature to the notification
class TimeStampDecorator: public NotificationDecorator{
    public:
    TimeStampDecorator(Notification * notification)
        :NotificationDecorator(notification){}

    string getContent()override {
        return "5 Spetember 2026 , 7:23 pm"+ notification->getContent();
    }
};
class SignatureDecorator: public NotificationDecorator{
    public:
    SignatureDecorator(Notification * notification)
        :NotificationDecorator(notification){}

    string getContent()override {
        return notification->getContent() + " Signed By : Mannan Tanwar , SDE@Google"; 
    }
};

// now have to crete the list of the observables and the observers
class Observer{
    public :
    virtual void update()=0;
};
class IObservable{
    // ab iske anda value hoti jo ki update hoti hai vo value wuld be notification now 
    

    public :
    virtual void addObserver(Observer* observer) = 0;
    virtual void removeObserver(Observer* observer) = 0;
    virtual void notifyObservers() = 0;

};

// now the concrete class for the notification observable 
class NotificationObservable: public IObservable{
    private:
    Notification * notification;
    vector<Observer * >observers; 
    public:
    
    void addObserver(Observer * observer) override{
        observers.push_back(observer);
    }
    void removeObserver( Observer* observer) override{
        auto it = find(observers.begin(), observers.end(), observer);
        observers.erase(it);
    }
    void notifyObservers() override{
        for(Observer * it : observers){
            it->update();
        }
    }
    void setNotification(Notification * notification)  {
        if(!this->notification)delete this->notification;
        this-> notification = notification;
        notifyObservers();
    }

    Notification * getNotification(){
        return notification;
    }
    string getNotificationContent(){
        return notification->getContent();
    }
};

// now time to  make the concrete observer 
class Logger: public Observer{
    // this will help me create the logging the notifications 
    private :
    NotificationObservable * observable;
    public:
    Logger(NotificationObservable * observable){
        this->observable=  observable;
    }
    void update(){
        cout<<"logging the notification "<<observable->getNotificationContent();
    }
};
// now time for the other concerte observer which is the notification engine 
// but firts lets make the notification strategy 

class NotificationStrategy {
    public:
    virtual void sendNotification(string content)=0;
};
class EmailStrategy: public NotificationStrategy{
    private :
    string email;
    public :
    EmailStrategy(string email){
        this->email= email;
    }
    void sendNotification( string content )override{
        cout<<" sending email to "<< email <<" wihth content "<<content<<endl;
    }
};
class SmsStrategy: public NotificationStrategy{
    private :
    long long number;
    public :
    SmsStrategy(long  long number ){
        this->number = number;
    }
    void sendNotification( string content )override{
        cout<<" sending sms to "<< number <<" wihth content "<<content<<endl;
    }
};
class PopUpStrategy: public NotificationStrategy{
    public :
    void sendNotification( string content )override{
        cout<<" sending ntoification with content "<<content<<endl;
    }
};
// now the 2 observer concerte class which will be calling the notif startegy 
class NotificationEngine: public Observer{
    private :
    NotificationObservable * observable;
    vector<NotificationStrategy *>types;
    public:
    NotificationEngine(NotificationObservable * observable){
        this->observable= observable;
    }
    void addNotificationStrategy(NotificationStrategy * strategy){
        types.push_back(strategy);
    }
    void update()override{
        for(auto & it : types){
            it->sendNotification(observable->getNotificationContent());
        }
    }
};

// now time make th enotification service which will be conntectng the notication class to the observable class// also we will have to make this class singleton 

class NotificationService{
    private:
    NotificationService(){
        this->observable = new NotificationObservable();
    }
    static NotificationService * instance ;
    NotificationObservable * observable;
    vector<Notification*>notifications;// done to create the history of the notifications 

    public:
     void sendNotification(Notification* notification) {
        notifications.push_back(notification); // history
        observable->setNotification(notification);
    }
    NotificationObservable *getObservable(){
        return this->observable;
    }
    static NotificationService * getInstance(){
        return instance;
    }
};
NotificationService * NotificationService::instance = new NotificationService();

int main(){
    NotificationService * service = NotificationService::getInstance();

    Notification * notification = new SimpleNotification("Hello Anushka !!");
    // ab is notification kko send bhi to krna hai with deocartor
    // applying the deocrators
    notification = new TimeStampDecorator(notification);
    notification = new SignatureDecorator(notification);

    // now letting the notifiaction service handle the stuff but before that we have to initialise the observers and th eobservable s
    NotificationObservable * observable = service->getObservable();

    NotificationEngine * engine= new NotificationEngine(observable);
    Logger * logger = new Logger(observable);

    // attaching the observs 
    observable->addObserver(logger);
    observable->addObserver(engine);

    engine->addNotificationStrategy(new EmailStrategy("random.person@gmail.com"));
    engine->addNotificationStrategy(new SmsStrategy(9654661686));
    engine->addNotificationStrategy(new PopUpStrategy());
    // ab merko sirf service me observable pass krna hai and uska send notif call krna hai 

    service->sendNotification(notification);

    return 0;
}
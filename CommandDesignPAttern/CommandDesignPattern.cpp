#include<bits/stdc++.h>
using namespace std;

// taking the xample of the home automation system 
// in which we can assign a particular button any fucntionality be it light fan or ac 
// isme hum kya krte hai ki source hota hia ek receiver to dono cammand ke through communicate krte hai 
// hum us command ko hi object bnadte hai 
class ICommand{
    public:
    virtual void execute()=0;
    virtual void undo() =0;
};

class Light{
    public:
    void on(){
        cout<<" light has been turned on !!"<<endl;
    }
    void off(){
        cout<<" light has been turned off !!"<<endl;
    }
};
class LightCommand: public ICommand{
    private :
    Light * light ;
    public :
    LightCommand(Light * light){
        this->light = light;
    }
    void execute() override{
        light->on();
    }
    void undo() override{
        light->off();
    }
};
class Remote{
    private :
    vector<ICommand*> buttons;
    static const int numButtons=4;
    vector<bool>pressed;
    
    public:
    Remote(){
        // this->numButtons=numButtons;
        buttons.resize(numButtons);
        pressed.resize(numButtons);
        for( int i=0;i<numButtons;i++){
            buttons[i]=nullptr;
            pressed[i]= false;
        }
    }
    void setCommand(int index,ICommand* command){
        if(buttons[index]!=nullptr){
            delete buttons[index];
        }
        buttons[index]=command;
        pressed[index]=false;
    }
    void pressedButton(int index){
        if(buttons[index]==nullptr)cout<<"no command here to execute!!"<<endl;
        else if(pressed[index]){
            buttons[index]->undo();
            pressed[index]=false;
        }
        else{
            buttons[index]->execute();
            pressed[index]=true;
        }
    }
};

int main(){
    Light * light = new Light();
    ICommand * command = new LightCommand(light);

    Remote * remote = new Remote();
    remote->pressedButton(3);

    remote->setCommand(3,command);
    remote->pressedButton(3);
    remote->pressedButton(3);
    remote->pressedButton(3);
    return 0;
}
// use case 
// logging service

// database connection

// configuration manager
#include<bits/stdc++.h>
using namespace std;

class Singleton{
    private:
    static Singleton * instance;
    Singleton(){
        cout<<"constructor called for the singleton class"<<endl;
    }

    public:
    static Singleton * getInstance(){
        // but htis is not thread safe
    //     if(instance == nullptr){
    //         instance = new Singleton();
    //     }
    //     return instance;   
    // }

    // thread safe version 
    return instance;
    }
};

// Initialize static member
Singleton* Singleton::instance = new Singleton();
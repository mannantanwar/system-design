#include<bits/stdc++.h>
using namespace std;

class AsteroidBuilder{
    private :
    AsteroidFlyweight asteroid;
    public :
    AsteroidBuilder& withLength( int length){
        asteroid.length= length;
        return *this;
    }
    AsteroidBuilder& withWidth( int width){
        asteroid.width= width;
        return *this;
    }
    AsteroidBuilder& withWeight( int weight){
        asteroid.weight= weight;
        return *this;
    }
    AsteroidBuilder& withcolor(string color){
        asteroid.color= color;
        return *this;
    }
    AsteroidBuilder& withtexture(string texture){
        asteroid.texture= texture;
        return *this;
    }
    AsteroidBuilder& withmaterial( string material){
        asteroid.material= material;
        return *this;
    }
    AsteroidFlyweight build(){
        return asteroid;
    }
};

// cooding the flywieght design pattern with the help of the builder design pattern 
class AsteroidFlyweight{
    private :
    // Intrinsic properties (shared among asteroids of same type)
    int length;          
    int width;           
    int weight;          
    string color;       
    string texture;      
    string material; 
    AsteroidFlyweight(){
        // constructor ko pvt krdia so that the object creation happens inly through the builder
    }
    public :
    friend class AsteroidBuilder;
};
class AsteroidContext{
    private:
    int x;
    int y;
    int velocityx;
    int velocityy;
    AsteroidFlyweight *flyweight;
    public:
    AsteroidContext(int x, int y , int vX , int vY, AsteroidFlyweight * fw){
        this->flyweight = fw;
        this->x= x;
        this->y = y;
        this->velocityx= vX;
        this->velocityy=vY;
    }

};
class FlyweightFactory{
    private:
    static unordered_map<string,AsteroidFlyweight> cache;
    public:
    AsteroidFlyweight createAsteroid(int length, int width, int weight, string color, string texture, string material){
        string key = to_string(length) + "_" + to_string(width) + "_" + to_string(weight) + "_" + color + "_" + texture + "_" + material;
        if(cache.count(key)){
            return cache[key];
        }
        else return  AsteroidBuilder()
        .withLength(length)
        .withWidth(width)
        .withWeight(weight)
        .withcolor(color)
        .withmaterial(material)
        .withtexture(texture)
        .build();
    }

};
 int main(){
    
    return 0;
 }
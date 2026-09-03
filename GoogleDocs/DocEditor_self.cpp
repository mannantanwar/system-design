#include <bits/stdc++.h>

using namespace std;

// basicallly we have to design a doc editor by follwoing all of the solid principles i have learned so far SOLID

// it can have text , img ..... and have to design this in such a way that it can be scaled in future if we want to add any more things in it like tables and all

// what was happeining currently was that we had a element in which we stored the text img andn evvrythig so if that continues

// lets say i have added the tabl and then for that what i would have to do is add  a check for the table too amd other when we ar erendering the doucment .... so what to do ???

// appproah 1 we can make the doucment editor class to store the lists of allof th etypes of data it has ??

// so if we have a lot ot the data types ie text img table ....... tsoring their separate list would make sense or would that make a hassle ?

// saving ke logic ke liye bhi we can make an abstract class and then override the method on the basis of the data type

// object ko element ki list me add kre ka logic ke liye kya krskte hai ??-> main funcme hi elets ki array banake usme alagalag object m=vhi par pushbck krdenge ?

// or docueditor class me add ka method daledenge usme elemts add krskte hai but that will breakk SRP

class Element
{

public:
    virtual void render() = 0;
};

class Text : public Element
{

private:
    string value;

public:
    void render() override
    {

        /// render logic for the text
    }
};

class Image : public Element
{

private:
    string value;

public:
    void render() override
    {

        /// render logic for the image
    }
};

class Document
{

private:
    vector<Element *> elements; // humne ek parent to banalia sbka but jab sbko render krenge to humee kya firse if else lgana odega ??

    // ummm yes ig baar baar type check kr krke humko us hisaab se likhna pdega handling logic

    // to prvent his humne jo element classs nai hai usme virtual mehtod bnadenge rnder ka ki kaise krega vo render and then element me traverse krte time hum bs uska render call krdenge jo ki runt ime pr decide hoga object ke acc uska render

    // sounds good ....

    string renderDocument;

public:
    Document(vector<Element *> elements)
    {

        this->elements = elements;
    }

    // can write the adding logic of the file over here too

    void addElement(Element *element)
    {

        elements.push_back(element);
    }

    vector<Element*> getElements(){
        return this->elements;
    }
};

class Persistence
{

public:
    virtual void save() = 0;
};

class saveToFile : public Persistence
{
};

class saveToDB : public Persistence
{
};

class DocumentRenderer
{
    private:
    Document * document;

    public:
    DocumentRenderer(Document * document){
        this->document = document;
    }
    void render(){
        vector<Element*> elements= document->getElements();
        // now the render logic for the elements 

    }
};

// now the main class which will take care of evrything

class DocumentEditor
{

private:
    Document *document;

public:
    DocumentEditor(Document *document)
    {

        this->document = document;
    }

    void addElement(Element *element)
    {

        document->addElement(element);
    }

};
// ot is the joib for the client now to call the persistence and the renderand docuemtn classes and perform the above functionalities 


// principles used -> SRP OCP ISP LSP DIP
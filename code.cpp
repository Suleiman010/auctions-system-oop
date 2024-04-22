#include <iostream>
using namespace std;


class Person{
    private:
    string name;
    int age;

    public:
    Person(string name, int age){
        this->name = name;
        setAge(age);
    }
    string getname(){
        return name;
    }
    void setname(string name){
        name = name;
    }
    int getAgee(){
        return age;
    }
    void setAge(int age){
        if(age<18){
            cout<<"Your younger then the specifed age(18)";
        }else{
            this->age = age;
        }
    }
    
};

class Item{
    private:
    int id;
    string name;
    string descrip;
    float price;
    public:
    Item (int id, string name, string descrip, float price){
        this->id = id;
        this->name = name;
        this->descrip = descrip;
        this->price = price;
    }
    int gitId(){
        return this->id;
    }    
    string getName(){
        return this->name;
    }
    void setName(string name){
        this->name = name;
    }
    string getDescrip(){
        return this->descrip;
    }
    void setDescrip(string desc){
        this->descrip = descrip;
    }
    float getPrice(){
        return this->price;
    }
    void setPrice(float price){
        this->price = price;
    }
};

int main(){

    Person p1("ahmed", 18);
    Item it1(1,"iphone", "sdjfkksjfsdf",215.5);

    cout<<"name:"<<it1.getName()<<endl;
    cout<<"price:"<<it1.getPrice()<<endl;
    return 0;
}
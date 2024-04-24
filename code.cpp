#include <iostream>
#include <vector>
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

class Biders: public Person{
    private:
    float budget;
    public:
    Biders(string name, int age,float budget):Person(name,age),budget(budget){}
    float getBudget(){
        return this->budget;
    }
    void setBudget(float budget){
        this->budget = budget;
    }
};

class Owner: public Person{
    private:
    float wallet;
    public:
    Owner(string name, int age, float wallet): Person(name,age),wallet(wallet){}
    void setWallet(float wallet){
        this->wallet = wallet;
    }
    float wallet(){
        return this->wallet;
    }
    
};
class Company{
    private:
    string name;
    float commission =0.12;
    vector <Biders> bidersList;
    vector <Owner> owners;
    public:
    Company(string name): name(name){}
    
    };
int main(){

    Company mycomp("nnn");
    
    while(true){

    }
    return 0;
}
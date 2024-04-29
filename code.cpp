#include <iostream>
#include <vector>
using namespace std;


class Bidder;
class Owner;
struct Person;
struct Item;

struct Person
{
    string name;
    string phoneNumber;
    string email;
    
};

struct Item {
    
    string ItemName;
    string description;
    double TargetedPrice;
    Owner *owner;
    Item(string n, string desc, double TP, Owner *own): ItemName(n), description(desc), TargetedPrice(TP),owner(own){}
};

class Owner : private Person {
private:
    
    vector<Item*> ownedItems;    
    vector<Item*> soldItems;

public:
    // Constructor
    Owner( const string& n, const string& e, const string& phone)
        :Person{n, e, phone} {}

    // Getter methods
    string getName() const { return this->name; }
    string getEmail() const { return this->email; }
    string getPhoneNumber() const { return this->phoneNumber; }
    
    //setters methods
    void setName(const string& name) { this->name = name; }
    void setEmail(const string& email) { this->email = email; }
    void setPhoneNumber(const string& phoneNumber) { this->phoneNumber = phoneNumber; }

    // Add an item to the list of sold items
    void addOwnedItem(Item* item) {
        ownedItems.push_back(item);
    }
    // Add an item to the list of sold items
    void addSoldItem(Item* item) {
        soldItems.push_back(item);
    }

    // Display owned items
    void displayOwnedItems() const {
        cout << "Owned Items:" << endl;
        for (const auto& item : ownedItems) {
           cout<<"Item name: "<<item->ItemName<<endl;
            cout << "Description: " << item->description << endl;
            cout << "Current Bid Amount: " << item->TargetedPrice << endl;
            cout << endl;
        }

     }
     // Display sold items
    void displaySoldItems() const {
        cout << "Sold Items:" << endl;
        for (const auto& item : soldItems) {
           cout<<"Item name: "<<item->ItemName<<endl;
            cout << "Description: " << item->description << endl;
            cout << "Current Bid Amount: " << item->TargetedPrice << endl;
            cout << endl;}
    }

    

    // Friend function to access private members of Owner
    friend void displayOwnersInfo(const Owner& owner);
};
/**
class Bidder: public Person{
    private:
    int bidderId;
    double maxBidAmount;
    
    public:
     Bidder(string name, string address, string email, string phoneNumber, int bidderId, double maxBidAmount) {
        this->name = name;
        this->email = email;
        this->phoneNumber = phoneNumber;
        this->bidderId = bidderId;
        this->maxBidAmount = maxBidAmount;
    }

    // Getters
    string getName() const {return this->name;}
    string getEmail() const {return this->email;}
    string getPhoneNumber() const {return this->phoneNumber;}
    int getBidderId() const {return this->bidderId;}
    double getMaxBidAmount() const {return this->maxBidAmount;}

    // Setters
    void setName(const string& newName) { this->name = newName;}
    void setEmail(const string& newEmail) { this->email = newEmail;}
    void setPhoneNumber(const string& newPhoneNumber) {this->phoneNumber = newPhoneNumber;}
    void setBidderId(int newBidderId) {this->bidderId = newBidderId;}
    void setMaxBidAmount(double newMaxBidAmount) {this->maxBidAmount = newMaxBidAmount;}

     
    // Friend function to access private members of Owner
    friend void displayBidderInfo(const Bidder& bidder);
    
};


class Company {
private:
    string companyName;
    double targetFee;
    vector<Item*> items;
    vector<Owner*> ItemOwners;
    vector<Bidder*> Bidders;

public:
    // Constructor
    Company(const string& name) : companyName(name), targetFee(1.5) {}
    
    

     
    
};

class Auction {
private:
    Item item;
    

};

// Friend function implementation for Bidder&Owner
void displayBidderInfo(const Bidder& bidder) { 
        cout << "Bidder Name: " << bidder.name << endl;
        cout << "Bidder Email: " << bidder.email << endl;
        cout << "Bidder Phone Number: " << bidder.phoneNumber << endl;
        cout << "Bidder ID: " << bidder.bidderId << endl;
        cout << "Bidder Max Bid Amount: " << bidder.maxBidAmount << endl;
}
void displayOwnersInfo(const Owner& owner) { 
        cout << "Owner Name: " << owner.name << endl;
        cout << "Owner Email: " << owner.email << endl;
        cout << "Owner Phone Number: " << owner.phoneNumber << endl;
        cout << "Owner ID: " <<owner.ownerId << endl;
        
}


 

*/

int main(){
    Owner ow1("kk32","ddd","ddd");
    Item it("kkk","dddd",250,&ow1);
    Item it2("kkksdfdsf","dsdfdfdd",250,&ow1);
   

    cout<<it2.owner->getEmail()<<endl;
    cout<<it.owner->getEmail()<<endl;
    ow1.addOwnedItem(&it);
    ow1.addOwnedItem(&it);
    ow1.displayOwnedItems();
    ow1.addSoldItem(&it2);
    ow1.displaySoldItems();
    
    

    return 0;
};
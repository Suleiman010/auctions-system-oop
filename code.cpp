#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;


class AuctionSystem;
class Owner;
class Bidder;
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
    double soldPrice=0.0;
    Owner *owner;
    Bidder *newOwner;
    Item(string n, string desc, double TP, Owner *own): ItemName(n), description(desc), TargetedPrice(TP),owner(own), newOwner(nullptr){}
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
    // Add an item to the list of sold items
    void addSoldItem(Item* item) {
    // Remove item from ownedItems if it exists
        auto it = find(ownedItems.begin(), ownedItems.end(), item);
        if (it != ownedItems.end()) {
        ownedItems.erase(it);
        }
    // Add item to soldItems
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

    
    friend class AuctionSystem;
    // Friend function to access private members of Owner
    friend void displayOwnersInfo(const Owner& owner);
};


class Bidder: private Person{
    private:
    int bidderId;
    double maxBidAmount;
    vector<Item*> boughtItems;

    
    public:
     Bidder(string name, string address, string email, string phoneNumber, double maxBidAmount) {
        this->name = name;
        this->email = email;
        this->phoneNumber = phoneNumber;
        this->maxBidAmount = maxBidAmount;
    }

    // Getters
    string getName() const {return this->name;}
    string getEmail() const {return this->email;}
    string getPhoneNumber() const {return this->phoneNumber;}
    //int getBidderId() const {return this->bidderId;}
    double getMaxBidAmount() const {return this->maxBidAmount;}

    // Setters
    void setName(const string& newName) { this->name = newName;}
    void setEmail(const string& newEmail) { this->email = newEmail;}
    void setPhoneNumber(const string& newPhoneNumber) {this->phoneNumber = newPhoneNumber;}
    //void setBidderId(int newBidderId) {this->bidderId = newBidderId;}
    void setMaxBidAmount(double newMaxBidAmount) {this->maxBidAmount = newMaxBidAmount;}

    // Add an item to the list of sold items
    void addOwnedItem(Item* item) {
        boughtItems.push_back(item);
    }
    
    
    void placeBid(AuctionSystem& auctionSystem, Item* item, double amount);
    
};

class AuctionSystem {
private:
    vector<Item*> approvedItems;
    vector<Item*> itemsForAuction;
    unordered_map<Item*, Bidder*> currentBids;

public:

    void checkAndAddOwnedItems(Owner* owner) {
        cout << "Owned Items:" << endl;
        for (const auto& item : owner->ownedItems) {
            cout << "Item Name: " << item->ItemName << endl;
            cout << "Description: " << item->description << endl;
            cout << "Current Bid Amount: " << item->TargetedPrice << endl;
            cout << "Press 1 to add this item to auction, or any other key to skip: ";
            char choice;
            cin >> choice;
            if (choice == '1') {
                itemsForAuction.push_back(item);
            }
        }
    }
    void addItemToAuction(Item* item) {
        itemsForAuction.push_back(item);
    }

    void placeBid(Item* item, Bidder* bidder, double amount) {
        if (currentBids.find(item) == currentBids.end() || currentBids[item]->getMaxBidAmount() < amount) {
            currentBids[item] = bidder;
            item->newOwner = bidder;
            item->TargetedPrice = amount;
        } else {
            cout << "Bid amount must be higher than the current highest bid." << endl;
        }
    }

    void endAuction() {
        for (auto& pair : currentBids) {
            Item* item = pair.first;
            Bidder* winner = pair.second;
            item->owner->addSoldItem(item);
            winner->addOwnedItem(item);
            item->owner = nullptr;
            item->newOwner = winner;
        }
        currentBids.clear();
    }

    friend void displayItemsForAuction(const AuctionSystem& auctionSystem);
};

void displayItemsForAuction(const AuctionSystem& AS){
        cout << "Items for Auction:" << endl;
        for (const auto& item : AS.itemsForAuction) {
            cout << "Item Name: " << item->ItemName << endl;
            cout << "Description: " << item->description << endl;
            cout << "Current Highest Bid: " << item->TargetedPrice << endl;
            cout << endl;
        }
    }

void Bidder::placeBid(AuctionSystem& auctionSystem, Item* item, double amount) {
    if (amount < 0) {
        cout << "Bid amount cannot be negative." << endl;
        return;
    }
    this->maxBidAmount -= amount;
    auctionSystem.placeBid(item, this, amount);
}
    

/*

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
    
    AuctionSystem as;
    Owner ow1("suleiman", "sss@gmail.com","55525552");
    Item it("ss","xxxxxxxxx",250.0,&ow1);
    Item it1("sds","xxxxxdddxxxx",250.0,&ow1);
    ow1.addOwnedItem(&it);
    ow1.addOwnedItem(&it1);
    as.checkAndAddOwnedItems(&ow1);


    return 0;
};
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
    Bidder *newOwner = nullptr;
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
        if (item && winner && item->owner) {
            item->owner->addSoldItem(item);
            winner->addOwnedItem(item);
            item->newOwner = winner;
            item->owner = nullptr;
        }
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
    



int main(){
    
    AuctionSystem as;
    Owner ow1("suleiman", "sss@gmail.com","55525552");
    Item it("ss","xxxxxxxxx",250.0,&ow1);
    Item it1("sds","xxxxxdddxxxx",250.0,&ow1);
    ow1.addOwnedItem(&it);
    ow1.addOwnedItem(&it1);
    as.addItemToAuction(&it);
    displayItemsForAuction(as);
    Bidder b1 ("nnn","ddddd","dfkgkdfjg","5454454544",500);
    b1.placeBid(as,&it,300);
    cout<<""<<endl;
    displayItemsForAuction(as);



    cout<<it.owner->getName()<<endl;

    cout<<""<<endl;
    as.endAuction();

    cout<<it.newOwner->getName()<<endl;
    cout<<""<<endl;

    ow1.displayOwnedItems();
    
    


    /*while (true)
    {
       
    }*/
    


    return 0;
};
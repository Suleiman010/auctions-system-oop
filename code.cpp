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

    virtual void displayInfo() const {
        cout << "Name: " << name << endl;
        cout << "Phone Number: " << phoneNumber << endl;
        cout << "Email: " << email << endl;
    }
    
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
    double wallet = 0.0;
    vector<Item*> ownedItems;    
    vector<Item*> soldItems;
    static int ownerCount;

public:
    // Constructor
    Owner( string name,  string email,  string phoneNumber){
        this->name =name;
        this->email= email;
        this->phoneNumber = phoneNumber;
        ownerCount++;
    }
        

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

    // Override the displayInfo method
    void displayInfo() const override {
        cout << "Owner Information:" << endl;
        Person::displayInfo(); // Call base class displayInfo
        cout << "Wallet: $" << wallet << endl;
    }

    static int getOwnerCount() {
        return ownerCount;
    }

    
    friend class AuctionSystem;
    };

    int Owner::ownerCount = 0;


class Bidder: private Person{
    private:
    int bidderId;
    double maxBidAmount;
    vector<Item*> boughtItems;
    static int bidderCount;

    
    public:
     Bidder(string name, string address, string email, string phoneNumber, double maxBidAmount) {
        this->name = name;
        this->email = email;
        this->phoneNumber = phoneNumber;
        this->maxBidAmount = maxBidAmount;
        bidderCount++;
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

    void displayInfo() const override {
        cout << "Bidder Info:" << endl;
        Person::displayInfo();
        cout << "Wallet: $ " << maxBidAmount << endl;
        cout << endl;
    }

    // Add an item to the list of sold items
    void addOwnedItem(Item* item) {
        boughtItems.push_back(item);
    }
    
    
    void placeBid(AuctionSystem& auctionSystem, Item* item, double amount);

    static int getBidderCount() {
        return bidderCount;
    }
    
};
int Bidder::bidderCount = 0;

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
            item->soldPrice = amount;
        } else {
            cout << "Bid amount must be higher than the current highest bid." << endl;
        }
    }

    void endAuction() {
    for (auto& pair : currentBids) {
        Item* item = pair.first;
        Bidder* winner = pair.second;
        if (item && winner && item->owner) {
            item->owner->wallet = item->owner->wallet+item->soldPrice;
            item->owner->addSoldItem(item);
            winner->addOwnedItem(item);
            item->newOwner = winner;
            item->owner = nullptr;
        }
    }
    currentBids.clear();
}

    void endAuction(Item* item) {
    auto it = currentBids.find(item);
    if (it != currentBids.end()) {
        Bidder* winner = it->second;
        if (item && winner && item->owner) {
            item->owner->wallet += item->soldPrice;
            item->owner->addSoldItem(item);
            winner->addOwnedItem(item);
            item->newOwner = winner;
            item->owner = nullptr;
            currentBids.erase(it);
        }
    }
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
    }else if(amount>maxBidAmount){
        cout<<"The amount your willing to bid is more than you budget";
        return;
    }else if(amount<=item->soldPrice){
        cout << "Bid amount must be higher than the current highest bid." << endl;
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
    as.addItemToAuction(&it1);
    displayItemsForAuction(as);
    Bidder b1 ("n1","ddddd","dfkgkdfjg","5454454544",500);
    Bidder b2 ("n2","ddddd","dfkgkdfjg","5454454544",500);
    Bidder b3 ("n3","ddddd","dfkgkdfjg","5454454544",500);
    b1.placeBid(as,&it,300);
    b2.placeBid(as,&it,450);
    b3.placeBid(as,&it1,500);
    cout<<""<<endl;
    displayItemsForAuction(as);

   



    cout<<it.owner->getName()<<endl;

    cout<<""<<endl;
    as.endAuction(&it);

    cout<<it.newOwner->getName()<<endl;
    cout<<""<<endl;

    ow1.displayOwnedItems();
    
    cout<<Bidder::getBidderCount()<<endl;
    cout<<Owner::getOwnerCount()<<endl;

    as.endAuction();

    b3.displayInfo();
    ow1.displayInfo();
    


    /*while (true)
    {
       
    }*/
    


    return 0;
};
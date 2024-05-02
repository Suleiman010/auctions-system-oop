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

    virtual void displayInfo()  {
        cout << "Name: " << name << endl;
        cout << "Phone Number: " << phoneNumber << endl;
        cout << "Email: " << email << endl;
    }
    virtual void addOwnedItem(Item* item) {
        "This function will be used by both the owner and the bidder to add the items that is owned by them";
    }
    
};

struct Item {
    
    string ItemName;
    string description;
    double TargetedPrice;
    double soldPrice=0.0;
    Owner *owner;
    Bidder *newOwner = nullptr;
    //constructer
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
    void setName(string name) { this->name = name; }
    void setEmail(string email) { this->email = email; }
    void setPhoneNumber(string phoneNumber) { this->phoneNumber = phoneNumber; }

    // Add an item to the list of sold items
    void addOwnedItem(Item* item) override {
        ownedItems.push_back(item);
    }
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
            cout << "Target price: $" << item->TargetedPrice << endl;
            cout << endl;
        }

     }
     // Display sold items
    void displaySoldItems() const {
    cout << "Sold Items:" << endl;
    for (const auto& item : soldItems) {
        cout << "Item name: " << item->ItemName << endl;
        cout << "Description: " << item->description << endl;
        cout << "Sold Price: $" << item->soldPrice << endl;
        cout << endl;
    }
}

    // Override the displayInfo method
    void displayInfo()  override {
        cout << "Owner Information:" << endl;
        Person::displayInfo(); // Call base class displayInfo
        cout << "Wallet: $" << wallet << endl;
        cout << endl;
    }

    static int getOwnerCount() {
        return ownerCount;
    }

    friend class AuctionSystem;
    };

int Owner::ownerCount = 0;

class Bidder: private Person{
    private:

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
    string getName()  {return this->name;}
    string getEmail()  {return this->email;}
    string getPhoneNumber()  {return this->phoneNumber;}
    double getMaxBidAmount()  {return this->maxBidAmount;}

    // Setters
    void setName(string newName) { this->name = newName;}
    void setEmail(string newEmail) { this->email = newEmail;}
    void setPhoneNumber( string newPhoneNumber) {this->phoneNumber = newPhoneNumber;}
    void setMaxBidAmount(double newMaxBidAmount) {this->maxBidAmount = newMaxBidAmount;}

    void displayInfo() override {
        cout << "Bidder Info:" << endl;
        Person::displayInfo();
        cout << "Wallet: $ " << maxBidAmount << endl;
        cout << endl;
    }

    // Add the item the user bought to the bought_item list
    void addOwnedItem(Item* item) override{
        boughtItems.push_back(item);
    }
     // Display bought items
    void displayBoughtItems()  {
        cout << "bought Items:" << endl;
        for (const auto& item : boughtItems) {
           cout<<"Item name: "<<item->ItemName<<endl;
            cout << "Description: " << item->description << endl;
            cout << "bought for: $" << item->soldPrice << endl;
            cout << endl;}
    }
      
    void placeBid(AuctionSystem& auctionSystem, Item* item, double amount);
    
    static int getBidderCount() {
        return bidderCount;
    }
    friend class AuctionSystem;
};
int Bidder::bidderCount = 0;

class AuctionSystem {
private:
    vector<Item*>ItemForBidd;

public:

    void addItemToAuction(Item* item) {
        ItemForBidd.push_back(item);
    }

    //place a bid
    void placeBid(Item* item, Bidder* bidder, double amount){
        // search for the item in vectore ItemForBidd
        auto it = find(ItemForBidd.begin(), ItemForBidd.end(), item);
        //if the item doesn't exist in the list
        if (it == ItemForBidd.end()) {
            cout << "Item is not available for bidding." << endl;
            return;
        }
        //check if this is not the first bid if true return the money to the person who got outbitid
        if(item->newOwner!=nullptr){
                item->newOwner->maxBidAmount = item->newOwner->maxBidAmount + item->soldPrice;
            }
        item->newOwner = bidder;
        item->soldPrice = amount; }

// end auction for all items
    void endAuction() {
    for (auto& item : ItemForBidd) {
        if(item->newOwner!=nullptr){
        item->owner->wallet += item->soldPrice;
        item->owner->addSoldItem(item);
        item->newOwner->addOwnedItem(item);
        item->owner = nullptr;
    }
}
    //clear the array or the list
    ItemForBidd.clear();
}

// end auction for a spicefic item
    void endAuction(Item* item) {
    if(item->newOwner!=nullptr){
        item->owner->wallet += item->soldPrice;
        item->owner->addSoldItem(item);
        item->newOwner->addOwnedItem(item);
        item->owner = nullptr;
    }
}
    //friend function
    friend void displayItemsForAuction(const AuctionSystem& auctionSystem);
};

void displayItemsForAuction(const AuctionSystem& AS){
        cout << "***************************"<<endl;
        cout << "Items for Auction:" << endl;
        for (const auto& item : AS.ItemForBidd) {
            cout << "Item Name: " << item->ItemName << endl;
            cout << "Description: " << item->description << endl;
            cout << "Current Highest Bid:$ " << item->soldPrice << endl;
            cout << "***************************"<<endl;
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
        cout << "Bid amount must be higher than the current highest bid-------." << endl;
        return;
    }else if(item->newOwner ==this ){
        cout<<"You made the last bid"<<endl;

    }
    else{
        this->maxBidAmount -= amount;
    auctionSystem.placeBid(item, this, amount);
    }
}

    



int main(){
    //create auction class
    AuctionSystem as;
    
    // create owneres
    Owner ow1("suleiman", "sss@gmail.com","55525552");
    Owner ow2("ali", "ss225s@gmail.com","55525152");
    
    //show the owners informations
    ow1.displayInfo();
    ow2.displayInfo();

    //create items and specify owners
    Item it1("Iphone 2","an Old Iphone 2",25.0,&ow1);
    Item it2("caclulus book","thomas claculus book 2nd ed used for 3 years.",7.0,&ow1);
    Item it3("Ps4","Ps4 slim It has for games, I am selling it because I bought ps5",175.0,&ow2);
    
    // the Itmes will now be added to the owned list in the owner class
    ow1.addOwnedItem(&it1);
    ow1.addOwnedItem(&it2);
    ow2.addOwnedItem(&it3);

    ow1.displayOwnedItems();
    ow2.displayOwnedItems();

    //adding Items to auctions
    as.addItemToAuction(&it1);
    as.addItemToAuction(&it2);
    as.addItemToAuction(&it3);

    //check if the auction created
    displayItemsForAuction(as);

    //create Bidders
    Bidder b1 ("n1","ddddd","dfkgkdfjg","5454454544",500.0);
    Bidder b2 ("n2","ddddd","dfkgkdfjg","5454574",500.0);
    Bidder b3 ("n3","ddd","dkdfjg","5454564",500.0);
    
    //diplay bidders info
    b1.displayInfo();
    b2.displayInfo();
    b3.displayInfo();

    //place bids by bidders
    b1.placeBid(as,&it1,26.0);
    b2.placeBid(as,&it2,9.0);
    b3.placeBid(as,&it2,10.0);
    b1.placeBid(as,&it3,170);
    b1.placeBid(as,&it2,31);
    b2.placeBid(as,&it1,32.50);

    //show all bids
    displayItemsForAuction(as);

    // end auctions
    /*as.endAuction(&it1);
    as.endAuction(&it2);
    as.endAuction(&it3);*/
    as.endAuction();

    
    //show the bidders owned list
    b1.displayBoughtItems();
    b2.displayBoughtItems();
    b3.displayBoughtItems();

    //show number of bidder and owners
    cout<<"*********"<<endl;
    cout<<"num of bidders: "<<Bidder::getBidderCount()<<endl;
    cout<<"num of owners: "<<Owner::getOwnerCount()<<endl;

    

    //diplay bidders info
    b1.displayInfo();
    b2.displayInfo();
    b3.displayInfo();
    cout<<"*********"<<endl;

    //display owners info
    ow1.displayInfo();
    ow2.displayInfo();
    cout<<"*********"<<endl;

    ow1.displaySoldItems();
    ow2.displaySoldItems();
    cout<<"*********"<<endl;

    cout<<b1.getMaxBidAmount()<<endl;
    cout<<b2.getMaxBidAmount()<<endl;
    cout<<b3.getMaxBidAmount()<<endl;
    return 0;
};
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
    int age;
};

struct Item {
    int itemId;
    std::string description;
    double currentBidAmount;
    Owner* owner;  // Pointer to Owner object

    // Constructor
    Item(int id, const std::string& desc, double bidAmount, Owner* own)
        : itemId(id), description(desc), currentBidAmount(bidAmount), owner(own) {}
};

class Owner : public Person {
private:
    int ownerId;
    std::vector<Item*> ownedItems;    
    std::vector<Item*> soldItems;

public:
    // Constructor
    Owner(int id, const string& n, const string& e, const string& phone)
        : ownerId{id},Person{n, e, phone} {}

    // Getter method for ownerId
    int getOwnerId() const { return ownerId; }
    std::string getName() const { return name; }
    std::string getEmail() const { return email; }
    std::string getPhoneNumber() const { return phoneNumber; }

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
        std::cout << "Owned Items:" << std::endl;
        for (const auto& item : ownedItems) {
            std::cout << "Item ID: " << item->itemId << std::endl;
            std::cout << "Description: " << item->description << std::endl;
            std::cout << "Current Bid Amount: " << item->currentBidAmount << std::endl;
            std::cout << std::endl;
        }
    }

    // Display sold items
    void displaySoldItems() const {
        std::cout << "Sold Items:" << std::endl;
        for (const auto& item : soldItems) {
            std::cout << "Item ID: " << item->itemId << std::endl;
            std::cout << "Description: " << item->description << std::endl;
            std::cout << "Sold Price: " << item->currentBidAmount << std::endl;
            std::cout << std::endl;
        }
    }
};

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

    // Getter and setter for 'email'
    string getName() const {
        return name;
    }

    void setName(const string& newName) {
        name = newName;
    }

    // Getter and setter for 'email'
    std::string getEmail() const {
        return email;
    }

    void setEmail(const string& newEmail) {
        email = newEmail;
    }

    // Getter and setter for 'phoneNumber'
    std::string getPhoneNumber() const {
        return phoneNumber;
    }

    void setPhoneNumber(const string& newPhoneNumber) {
        phoneNumber = newPhoneNumber;
    }

    // Getter and setter for 'bidderId'
    int getBidderId() const {
        return bidderId;
    }

    void setBidderId(int newBidderId) {
        bidderId = newBidderId;
    }

    // Getter and setter for 'maxBidAmount'
    double getMaxBidAmount() const {
        return maxBidAmount;
    }

    void setMaxBidAmount(double newMaxBidAmount) {
        maxBidAmount = newMaxBidAmount;
    }
    
};

int main(){
    Bidder b1("ali", "skfjslkdf","email","465565",5, 555.2);
    cout<<b1.getName()<<endl;
    b1.setName("alia");
    cout<<b1.getName()<<endl;
    Owner owner1(1,"a","5555","444");
    Item it1(101,"shule",252,&owner1);
    Item it2(2102,"shule2",252,&owner1);

    owner1.addOwnedItem(&it1);
    owner1.addOwnedItem(&it2);
    owner1.displayOwnedItems();
    owner1.addSoldItem(&it2);
    owner1.displaySoldItems();





    return 0;
};
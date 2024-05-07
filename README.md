# What is an Auction?

## An auction is a system of buying and selling goods or services by offering 
##them for bidding—allowing people to bid and selling to the highest bidder.


## classess
a-Owner

b-Bidder

c-AuctionSystem

## structures
a-Person

b-Item

### Person is a superclass and Owner-Bidder are subclassess

## virtual functions:
a-virtual void displayInfo() line20

b-virtual void addOwnedItem(Item* item) line 24

## override functions 
a- void addOwnedItem(Item* item) override line 70

b- void addOwnedItem(Item* item) override  line 163

## overloaded functions
a- void endAuction() line 210

b- void endAuction() line 227



#### constructers are in class structure Item owner - bidder: line 40, line 53, line 133; 

## static functions
a- static int getOwnerCount() line 113

b- static int getBidderCount() line 170




#### pointers: every variable or objecct with * in  its decleration.

#### friend function: friend void displayItemsForAuction(const AuctionSystem& auctionSystem); line 245.

#### functions with default argument : void taxIfReachedTarget(Item* item, double tax = 0.08) line 236.

## Actors:
Owner: A person who owns items and can add items to the auction.
Bidder: A person who can place bids on items in the auction.
AuctionSystem: Manages the auction process and items.

## Use Cases:
Add Item to Auction: The Owner can add an item to the auction system.
Place Bid: The Bidder can place a bid on an item.
End Auction: The AuctionSystem can end the auction for all items or a specific item.
Display Items for Auction: Display the list of items available for bidding.
Display Owned Items: both the bidder and the owner can display the information of the items they own.

## Relationships:
Composition: The AuctionSystem owns the Item objects.
Aggregation: The Owner and Bidder have an aggregation relationship with Item objects they own or have bought.
Inheritance: The Owner and Bidder classes inherit from the Person class.

## classes variables:
class AuctionSystem: vector<Item*>ItemForBidd;
class Owner: double wallet = 0.0; vector<Item*> ownedItems; vector<Item*> soldItems; static int ownerCount;
class Bidder:double maxBidAmount; vector<Item*> boughtItems; static int bidderCount;

## structures variable:
struct person: string name; string phoneNumber; string email;
struct Item: string ItemName;string description;double TargetedPrice;double soldPrice=0.0;Owner *owner;Bidder *newOwner = nullptr;

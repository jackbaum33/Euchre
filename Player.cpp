#include "Player.hpp"
#include <iostream>
#include <cassert>
#include <algorithm>
using namespace std;



class SimplePlayer : public Player{
private:
string name;
vector<Card> hand;

public:
SimplePlayer(string name_in)
{
name=name_in;
}
const string &get_name() const override
{
return name;
}

void add_card(const Card &c) override
{
hand.push_back(c);
sort(hand.begin(),hand.end());
}

bool make_trump(const Card &upcard, bool is_dealer,
    int round, Suit &order_up_suit) const override
{
if(round==1)
{
    int goodCardCounter=0;
   for(size_t i=0; i<hand.size(); i++)
   {
    if(hand[i].is_trump(upcard.get_suit())
     && hand[i].is_face_or_ace())
    {
        goodCardCounter++;
    }
   } 
   if(goodCardCounter>=2)
   {
    order_up_suit=upcard.get_suit();
    return true;
   }
}
else if(round == 2)
{
    if(is_dealer)
    {
    order_up_suit=Suit_next(upcard.get_suit());
    return true;
    }
 int goodCardCounter=0;
   for(size_t i=0; i<hand.size(); i++)
   {
    if((hand[i].get_suit()==Suit_next(upcard.get_suit())) 
     && hand[i].is_face_or_ace())
    {
        goodCardCounter++;
    }
   }
   if(goodCardCounter>=1)
   {
    order_up_suit=Suit_next(upcard.get_suit());
    return true;
   }
}
return false;
}

void add_and_discard(const Card &upcard) override
{
Card lowestCard=upcard;
int indexOfLowestCard=0;
for(int i=0; i<5; i++)
{
    if(Card_less(hand[i],lowestCard,upcard.get_suit()))
    {
        lowestCard=hand[i];
        indexOfLowestCard=i;
    }
}
if(lowestCard!=upcard)
{
hand.erase(hand.begin()+indexOfLowestCard);
add_card(upcard);
}

}

Card lead_card(Suit trump) override
{
    bool onlyTrump;
    Card highestNonTrump=hand[0];
    Card highestTrump=hand[0];
    if(hand[0].get_suit(trump)==trump)
    {
        onlyTrump=true;
    }
    else onlyTrump=false;
    int indexOfHighestTrump=0;
    int indexOfHighestNonTrump=0;
  for(int i=0; i<(int)hand.size(); i++)
  {
    if(!hand[i].is_trump(trump))
    {
    if(hand[i]>=highestNonTrump)
    {
        highestNonTrump=hand[i];
        indexOfHighestNonTrump=i;
    }
    onlyTrump=false;
  }
  else
  {
    if(Card_less(highestTrump,hand[i],trump))
    {
        highestTrump=hand[i];
        indexOfHighestTrump=i;
    }
  }
}
if(onlyTrump)
 {
    Card c=highestTrump;
    hand.erase(hand.begin()+indexOfHighestTrump);
    return c;
 }
 else
{
   Card c=highestNonTrump;
    hand.erase(hand.begin()+indexOfHighestNonTrump);
    return c; 
}
}

Card play_card(const Card &led_card, Suit trump) override
{
Card highestThatFollowsSuit=hand[0]; 
int indexOfHighestCardThatFollowsSuit=0;  
bool cardThatFollowsSuit=false; 
Card lowestCard=hand[0];
if(lowestCard.get_suit(trump)==led_card.get_suit(trump)) 
{
    cardThatFollowsSuit=true;
}
int indexOfLowestCard=0;

for(int i=0; i<(int)hand.size(); i++)
{
    if(hand[i].get_suit(trump)==led_card.get_suit(trump))
    {
        cardThatFollowsSuit=true;
        if(Card_less(highestThatFollowsSuit,hand[i],trump) 
        || highestThatFollowsSuit.get_suit(trump)
         !=led_card.get_suit())
        {
            highestThatFollowsSuit=hand[i];
            indexOfHighestCardThatFollowsSuit=i;
        }
    }
    else
    {
        if(Card_less(hand[i],lowestCard,led_card,trump))
        {
            lowestCard=hand[i];
            indexOfLowestCard=i;
        }
    }
}
if(cardThatFollowsSuit)
{
Card c=hand[indexOfHighestCardThatFollowsSuit];
hand.erase(hand.begin()+indexOfHighestCardThatFollowsSuit);
return c;
}
else
{
    Card c=hand[indexOfLowestCard];
    hand.erase(hand.begin()+indexOfLowestCard);
    return c;
}
}


};

class HumanPlayer : public Player{
private:
string name;
vector<Card> hand;
void print_hand() const
{
for (size_t i=0; i < hand.size(); ++i)
cout << "Human player " << name << "'s hand: "
    << "[" << i << "] " << hand[i] << "\n";
}

public:
HumanPlayer(string name_in)
{
name=name_in;
}

const string &get_name() const override
{
return name;
}

void add_card(const Card &c) override
{
hand.push_back(c);
sort(hand.begin(),hand.end());
}

bool make_trump(const Card &upcard, bool is_dealer,
    int round, Suit &order_up_suit) const override
{
    print_hand();
cout << "Human player " << name << 
", please enter a suit, or \"pass\":\n";

string decision;
cin >> decision;

if (decision != "pass")
{
   order_up_suit= string_to_suit(decision);
   cout<<endl;
   return true;
}
else
{
cout<<endl;
return false;
}
}

void add_and_discard(const Card &upcard) override
{  
print_hand();
cout << "Discard upcard: [-1]\n";
cout << "Human player " << name << ", please select a card to discard:\n";
int decision;
cin>>decision;
if(decision!= -1)
{
hand.erase(hand.begin()+decision);
add_card(upcard);
}
cout<<endl;
}

Card lead_card(Suit trump) override
{
print_hand();
cout << "Human player " << name << ", please select a card:\n";
int decision;
cin>>decision;
Card c=hand[decision];
hand.erase(hand.begin()+decision);
cout<<endl;
return c;
}

Card play_card(const Card &led_card, Suit trump) override
{
    print_hand();
cout << "Human player " << name << ", please select a card:\n";
int decision;
cin>>decision;
Card c=hand[decision];
hand.erase(hand.begin()+decision);
cout<<endl;
return c;
}
};


Player* Player_factory(const string &name, const string &strategy)
{

 if (strategy == "Simple") {
return new SimplePlayer(name);
 }
if(strategy=="Human")
{
return new HumanPlayer(name);
}
assert(false);
return nullptr;
}

std::ostream & operator<<(std::ostream &os, const Player &p) {
  os<<p.get_name();
  return os;
}


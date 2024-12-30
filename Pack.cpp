#include "Pack.hpp"
#include <iostream>
using namespace std;

Pack::Pack()
{
next = 0;
int index=0;
 for(int s = SPADES; s <= DIAMONDS; s++)
 {
  for(int r = NINE; r <= ACE; r++)
  {
    Suit currentSuit = static_cast<Suit>(s);
    Rank currentRank = static_cast<Rank>(r);
    cards[index] = Card(currentRank,currentSuit);
    index++;
  }
 }
}

Pack::Pack(std::istream& pack_input)
{
  next=0;
for(int i=0; i<PACK_SIZE; i++)
{
Card c;
pack_input>>c;
cards[i]=c;
}
}

Card Pack::deal_one()
{
    Card cardToDeal=cards[next];
    next++;
    return cardToDeal;
}

void Pack::reset()
{
    next=0;
}

void Pack::shuffle()
{
  next=0;
array<Card, PACK_SIZE> cardsCopy=cards;
for(int j=0;j<7;j++){
for(int i=0; i<12; i++)
{
cards[i*2]=cardsCopy[i+12];
cards[(i*2)+1]=cardsCopy[i];
}
cardsCopy=cards;
}
}

bool Pack::empty() const
{
  if(next==24) return true;
  else return false;
}


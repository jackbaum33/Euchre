#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Player.hpp"
#include "Pack.hpp"
#include "Card.hpp"
using namespace std;

class Game
{
private: 
vector<Player*> players;
Pack pack;
Suit trumpSuit;
Card upcard;
int currentHand;
int positionOfDealer;
int pointsToWin;
int winningTeam;
int newIndexOfHighestCard;
int indexOfHighestCard;
int teamOneTricks;
int teamTwoTricks;
int teamOnePoints;
int teamTwoPoints;
bool shuffling;
bool ordersUp;
bool teamOneOrdersUp;
bool teamTwoOrdersUp;
bool teamOneWins;
bool teamTwoWins;
void determineShuffle(string shuffleType);
void shuffle(); 
void resetParameters();
void deal(Pack gamePack);
void make_trump();
void addUpcard();
void setTeamOrderUp(int index);
void playFirstTrick();
void playFourTricks();
void trickScore(int index);
void calcRoundScore(int teamOneTricks, int teamTwoTricks, 
      bool teamOneOrdersUp, bool teamTwoOrdersUp);
void doRound();
void updateDealer();
bool checkForGameEnd(int teamOnePoints,int teamTwopoints,int &winningTeam);
void printWinner(int winningTeam);
void deletePlayerPointers();

public:
Game(vector<Player*> gamePlayers, 
Pack openedPack, int points, string shuffleType);
void play();
};

Game::Game(vector<Player*> gamePlayers,
Pack openedPack, int points, string shuffleType)
{
currentHand=0;
positionOfDealer=0;
for(size_t i=0; i<gamePlayers.size(); i++)
{
  players.push_back(gamePlayers[i]);
}
pack=openedPack;
pointsToWin=points;
teamOneTricks=0;
teamTwoTricks=0;
teamOnePoints=0;
teamTwoPoints=0;
determineShuffle(shuffleType);
}

void Game::play()
{
  while(!checkForGameEnd(teamOnePoints,teamTwoPoints,winningTeam)){
  doRound();
  currentHand++;
  }
printWinner(winningTeam);
deletePlayerPointers();
}

void Game::determineShuffle(string shuffleType)
{
  if(shuffleType=="shuffle")
  {
    shuffling=true;
  }
  else shuffling=false;
}

void Game::shuffle()
{
if(shuffling)
{
  pack.shuffle();
}
else
{
  pack.reset();
}
}

void Game::resetParameters()
{
teamOneOrdersUp=false;
teamTwoOrdersUp=false;
teamOneWins=false;
teamTwoWins=false;
ordersUp=false;
}

void Game::deal(Pack gamePack)
{
cout<<players[positionOfDealer]->get_name()<<" deals"<<endl; 
for(int i=0; i<3; i++) 
    players[(positionOfDealer+1)%4]->add_card(gamePack.deal_one());
for(int i=0; i<2; i++) 
   players[(positionOfDealer+2)%4]->add_card(gamePack.deal_one());
for(int i=0; i<3; i++) 
  players[(positionOfDealer+3)%4]->add_card(gamePack.deal_one());
for(int i=0; i<2; i++) 
   players[(positionOfDealer)%4]->add_card(gamePack.deal_one());
for(int i=0; i<2; i++) 
   players[(positionOfDealer+1)%4]->add_card(gamePack.deal_one());
for(int i=0; i<3; i++) 
   players[(positionOfDealer+2)%4]->add_card(gamePack.deal_one());
for(int i=0; i<2; i++) 
   players[(positionOfDealer+3)%4]->add_card(gamePack.deal_one());
for(int i=0; i<3; i++) 
   players[(positionOfDealer)%4]->add_card(gamePack.deal_one());
upcard=gamePack.deal_one();
cout<<upcard<<" turned up"<<endl;
}

void Game::make_trump() {
 for(int i=1; i<=3; i++){
  ordersUp=players[(positionOfDealer+i)%4]->make_trump(upcard,false,1,trumpSuit);
    if(ordersUp){
       cout<<players[(positionOfDealer+i)%4]->get_name()
       <<" orders up "<<trumpSuit<<endl<<endl;
    setTeamOrderUp((positionOfDealer+i)%4);
     addUpcard();
       return; }
    cout<<players[(positionOfDealer+i)%4]->get_name()<<" passes"<<endl;
     }
   ordersUp=players[(positionOfDealer)]
   ->make_trump(upcard,true,1,trumpSuit);
  if(ordersUp){
      cout<<players[positionOfDealer]->get_name()
      <<" orders up "<<trumpSuit<<endl<<endl;
     setTeamOrderUp(positionOfDealer);
     addUpcard();
      return; 
      }
    cout<<players[positionOfDealer]->get_name()<<" passes"<<endl;
    for(int i=1; i<=3; i++){
  ordersUp=players[(positionOfDealer+i)%4]->make_trump(upcard,false,2,trumpSuit);
    if(ordersUp){
       cout<<players[(positionOfDealer+i)%4]->get_name()
       <<" orders up "<<trumpSuit<<endl<<endl;
    setTeamOrderUp((positionOfDealer+i)%4);
       return; }
    cout<<players[(positionOfDealer+i)%4]->get_name()<<" passes"<<endl; }
   ordersUp=players[(positionOfDealer)]->make_trump(upcard,true,2,trumpSuit);
      cout<<players[positionOfDealer]->get_name()
      <<" orders up "<<trumpSuit<<endl<<endl;
      setTeamOrderUp(positionOfDealer);
      return; 
}

void Game::addUpcard()
{
    players[positionOfDealer]->add_and_discard(upcard);
  
}

void Game::setTeamOrderUp(int index)
{
  if(index==0||index==2)teamOneOrdersUp=true;
  else teamTwoOrdersUp=true;
}

void Game::playFirstTrick()
{
teamOneTricks=0;
teamTwoTricks=0;
Card highestCardPlayed;
Card leadCard=players[(positionOfDealer+1)%4]->lead_card(trumpSuit);
cout<<leadCard<<" led by "
<<players[(positionOfDealer+1)%4]->get_name()<<endl;
highestCardPlayed=leadCard;
indexOfHighestCard=(positionOfDealer+1)%4;
for(int i=2; i<=4; i++)
{
 Card currentCard=players[(positionOfDealer+i)%4]
 ->play_card(leadCard,trumpSuit);
cout<<currentCard<<" played by "
 <<players[(positionOfDealer+i)%4]->get_name()<<endl;
if(Card_less(highestCardPlayed,currentCard,leadCard,trumpSuit))
{
  highestCardPlayed=currentCard;
  indexOfHighestCard=(positionOfDealer+i)%4;
}
}
trickScore(indexOfHighestCard);
cout<<endl;
}

void Game::playFourTricks()
{
  newIndexOfHighestCard=indexOfHighestCard;
  for(int j=0; j<4; j++)
  {
    Card leadCard= players[indexOfHighestCard]->lead_card(trumpSuit);
    Card highestCardPlayed=leadCard;
    cout<<leadCard<<" led by "
    <<players[indexOfHighestCard]->get_name()<<endl;
    for(int i=1; i<=3; i++)
    {
      Card currentCard=players[(indexOfHighestCard+i)%4]
      ->play_card(leadCard,trumpSuit);
      cout<<currentCard<<" played by "
      <<players[(indexOfHighestCard+i)%4]->get_name()<<endl;
      if(Card_less(highestCardPlayed,currentCard,leadCard,trumpSuit))
          {
            highestCardPlayed=currentCard;
            newIndexOfHighestCard=(indexOfHighestCard+i)%4;
            }
        }
        trickScore(newIndexOfHighestCard);
        indexOfHighestCard=newIndexOfHighestCard;
        cout<<endl;  
    }
  }

void Game::trickScore(int index)
{
if(index== 0 || index==2)
{
  cout<<players[index]->get_name()<<" takes the trick"<<endl;
  teamOneTricks++;
}
else
{
   cout<<players[index]->get_name()<<" takes the trick"<<endl;
  teamTwoTricks++;
}
}

void Game::calcRoundScore(int teamOneTricks, int teamTwoTricks, 
    bool teamOneOrdersUp, bool teamTwoOrdersUp)
    {
      if(teamOneTricks>teamTwoTricks)
      {
        cout<<players[0]->get_name()<<" and "
        <<players[2]->get_name()<<" win the hand"<<endl;
        if(teamOneOrdersUp && teamOneTricks==5) 
        {
          teamOnePoints+=2;
          cout<<"march!"<<endl;
        }
        else if(!teamOneOrdersUp)
        {
         teamOnePoints+=2;
          cout<<"euchred!"<<endl; 
        }
        else
        {
          teamOnePoints++;
        }
      }
      else
      {
        cout<<players[1]->get_name()<<" and "
        <<players[3]->get_name()<<" win the hand"<<endl;
        if(teamTwoOrdersUp && teamTwoTricks==5) 
        {
          teamTwoPoints+=2;
          cout<<"march!"<<endl;
        }
        else if(!teamTwoOrdersUp)
        {
         teamTwoPoints+=2;
          cout<<"euchred!"<<endl; 
        }
        else
        {
          teamTwoPoints++;
        }
      }
    cout<<players[0]->get_name()<<" and "
    <<players[2]->get_name()<<" have "
     <<teamOnePoints<<" points"<<endl;

    cout<<players[1]->get_name()<<" and "
    <<players[3]->get_name()<<" have "
      <<teamTwoPoints<<" points"<<endl;
    teamOneOrdersUp=false;
    teamTwoOrdersUp=false;
    cout<<endl;
    }

void Game::doRound()
{
cout<<"Hand "<<currentHand<<endl;
shuffle();
deal(pack);
resetParameters();
make_trump();
playFirstTrick();
playFourTricks();
calcRoundScore(teamOneTricks,teamTwoTricks,teamOneOrdersUp,teamTwoOrdersUp);
updateDealer();
}

void Game::updateDealer()
{
positionOfDealer++;
if(positionOfDealer==4) positionOfDealer=0; 
}

bool Game::checkForGameEnd(int teamOnePoints,
int teamTwopoints, int &winningTeam)
{
if(teamOnePoints>=pointsToWin)
{
  winningTeam=1;
  return true;
}
else if (teamTwoPoints>=pointsToWin)
{
  winningTeam=2;
  return true;
}
else return false;
}

void Game::printWinner(int winningTeam)
{
if(winningTeam==1)
{
  cout<<players[0]->get_name()<<
  " and "<<players[2]->get_name()<<" win!"<<endl;
}
else
{
 cout<<players[1]->get_name()<<
 " and "<<players[3]->get_name()<<" win!"<<endl;
}
}

void Game::deletePlayerPointers()
{
for (size_t i = 0; i < players.size(); ++i) {
  delete players[i];
}
}
  
int main(int argc, char* argv[]) {
  if(argc!= 12) {
   cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "<< "POINTS_TO_WIN " 
   << "NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 " << "NAME4 TYPE4" << endl; return 1; }
   string shuffleType=argv[2];
  if(!(shuffleType=="shuffle" || shuffleType=="noshuffle")){
cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "<< "POINTS_TO_WIN " 
   << "NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 " << "NAME4 TYPE4" << endl; return 1; }
if(atoi(argv[3])<1 || atoi(argv[3])>100){
cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "<< "POINTS_TO_WIN " 
   << "NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 " << "NAME4 TYPE4" << endl;
    return 1; }
for(int i=5; i<=11; i+=2)
{
  string currentArg=argv[i];
  if(currentArg!="Simple" && currentArg!="Human")
  {
 cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "<< "POINTS_TO_WIN "
   << "NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 " << "NAME4 TYPE4" << endl;
    return 1;
  }
}
 Player* playerOne=Player_factory(argv[4],argv[5]);
 Player* playerTwo=Player_factory(argv[6],argv[7]);
 Player* playerThree=Player_factory(argv[8],argv[9]);
 Player* playerFour=Player_factory(argv[10],argv[11]);
vector<Player*> gamePlayers;
gamePlayers.push_back(playerOne);
gamePlayers.push_back(playerTwo);
gamePlayers.push_back(playerThree);
gamePlayers.push_back(playerFour);
  ifstream packOpener;
  packOpener.open(argv[1]);
  if(!packOpener.is_open()){
    cout << "Error opening " << argv[1] << endl;
    return 1; }
Pack openedPack(packOpener);
for(int i=0; i<12; i++) cout<<argv[i]<<" ";
cout<<endl;
Game game(gamePlayers,openedPack,atoi(argv[3]),argv[2]);
game.play();
return 0; }
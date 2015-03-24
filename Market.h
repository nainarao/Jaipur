//Market.h

#ifndef MARKET_H
#define MARKET_H
#include <vector>
#include <map>
#include "Card.h"
#include "Deck.h"
#include "Token.h"

using std::ostream;
using std::string;
using std::vector;
using std::map;

class Market{
private:

    vector<Card> marketCards;
    vector<Card> takenCards;

public:
    //Constructor
    Market(); //default constructor

    //Methods
    void setUpMarket(Deck * deck); //fills market at start of game
    void fillMarket(Deck * deck); //fills all empty spaces in market
    vector<Card> * getMarket() { return &marketCards; };
    int getCamels();
    bool existsInMarket(Card x);
    bool existsInMarket(vector<Card> *);
    int makeSale(Token * tokens, vector<Card> * hand, Card x);
    int makeSale(Token * tokens, vector<Card> * hand, Card x, int number);
    void makeTake(vector<Card> * herd, vector<Card> * hand, vector<Card> * exchangeCards, vector<Card> * marketCards, int moveID);
    void refreshPage();
    void printMarket(Token * tokens);
};

#endif // Market_H

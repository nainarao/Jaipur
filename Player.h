#ifndef _PLAYER_H
#define _PLAYER_H


#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Card.h"
#include "Market.h"
#include "Move.h"
#include "Token.h"

using std::ostream;
using std::string;
using std::vector;
using std::map;


class Player   // abstract base class
{
protected:
    string name; //Player name
    int numSeals; //number of Seals of Excellence
    int herdCount; //number of camels
    vector<Card> herd; //contains all of Player's camels -- MAY NOT BE NECESSARY
    vector<Card> hand; //Player's hand
    int tokenPoints; //contains all of Player's tokens

public:
    //Constructor
    Player() { name = ""; };
    Player(string n); //initializes name with n, all other variables to 0 or nullptr

    //Destructor
    ~Player();

    //Methods
    vector<Card> * getHand() { return &hand; };
    vector<Card> * getHerd() { return &herd; };

    int sealCount() { return numSeals; };
    int getPoints();
    void addPoints(int x) { tokenPoints += x; };
    void addCard(Card x);
    void addHerdCard(Card x);
    void addSeal() { numSeals++; };
    void resetPoints() { tokenPoints = 0; };
    void fillHand(Deck * deck);
    bool existsInHand(vector<Card> *);
    string getName() {return name;};

    virtual void movePlay(Market * market, Token *tokens, Player * player) = 0; // Virtual move function, must be overridden
    virtual void sellCards(Market *market, Token *tokens, Move * move, Player * player) = 0; //pure virtual function, must be overridden
    virtual void takeCards(Market *market, Token *tokens, Move * move, Player * player) = 0; //pure virtual function, must be overridden

    void printPlayer();
} ;

#endif

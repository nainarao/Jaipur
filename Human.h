#ifndef _HUMAN_H
#define _HUMAN_H


#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Card.h"
#include "Player.h"
#include "Move.h"

using std::ostream;
using std::string;
using std::vector;
using std::map;


class Human : public Player
{
public:
    //Constructor
    Human(string n); //initializes name with n, all other variables to 0 or nullptr

    //Destructor
     ~Human();

    //Methods
    void movePlay(Market * market, Token *tokens, Player * player); //allows Human Player to choose move
    void sellCards(Market *market, Token *tokens, Move * move, Player * player); //helper method for move() when selling cards
    void takeCards(Market *market, Token *tokens, Move * move, Player * player); //helper method for move() when taking cards

    void refreshWin();
    void turnOver();
    void takeOneCard(Market * market, Card card, Move * curr, Token * tokens, Player * player);
    void takeMultipleCards(Market * market, Move * curr, Token * tokens, Player * player);
    void takeCamels(Market * market, Move * curr, Token * tokens, Player * player);
    void clearBoard(Market * market, Token *tokens, Player * player);
};

#endif



#ifndef __IntermediateProject__Computer__
#define __IntermediateProject__Computer__

#include <stdio.h>
#include "Market.h"
#include "Player.h"
#include "Deck.h"
#include "Move.h"

class Computer: public Player
{
private:
    bool fullRound;
    char takeChoice;
public:
    Computer() : Player() { fullRound = false;};
    Computer(string n) : Player(n) {};
    ~Computer();

    // General move methods
    void movePlay(Market * market, Token * tokens, Player * player);
    void sellCards(Market * market, Token * tokens, Move * move, Player * player);
    void takeCards(Market * market, Token * tokens, Move * move, Player * player);

    // Specific methods for take
    void takeManyCards(Market * market, Token * tokens, Move * move);
    void takeOneCard(Market * market, Token * tokens, Move * move);
    void takeOneCard(Market * market, Token * tokens, Move * move, Card x);
    void takeCamels(Market * market, Token * tokens, Move * move);
    void takeOneCard(Market * market, Token * tokens, Move * curr, Card * need);

    // Specific logic-needed methods
    Card valuableNeedsCompletion(Market * market);
    Card returnBest(vector<Card>invalidCards, Token * tokens);
    vector<Card> hasBadCards(Token * tokens);
    bool goodSale(Token * tokens, Move * move);
    bool hasValidSale(Token * tokens, Move * move);
    bool hasThreeCards();
};

#endif /* defined(__IntermediateProject__Computer__) */

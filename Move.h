

#ifndef __IntermediateProject__Move__
#define __IntermediateProject__Move__

#include <stdio.h>
#include "Market.h"
#include "Card.h"
#include <stdlib.h>
#include "Token.h"

class Move
{
private:

public:
    Move();

    bool validSale(vector<Card> * hand, Card x);
    bool validTakeMany(vector<Card> * exchangeHand, vector<Card> * exchangeMarket);
    bool validTakeOne(vector<Card> * hand, Card x);
    bool validTakeCamels(Market * market);

};

#endif /* defined(__IntermediateProject__Move__) */

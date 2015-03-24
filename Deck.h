
#ifndef __IntermediateProject__Deck__
#define __IntermediateProject__Deck__

#include <stdio.h>
#include <vector>
#include "Card.h"

class Deck
{
private:
    vector<Card> cVector;
public:
    Deck();
    vector<Card> * getVector() { return &cVector; } ;
    void fill();
    void printDeck();
};

#endif /* defined(__IntermediateProject__Deck__) */

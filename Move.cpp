
#include "Move.h"

bool Move:: validSale(vector<Card> * hand, Card x)
{
    bool ans = true;
    int valuableCount = 0;
    int regularCount = 0;
    /*
     If it is a valuable card that the player is trying to sell,
     make sure that there is AT LEAST 2 of that card in the player's
     hand.
     */
    if (x.isValuable())
    {
        for (unsigned int i = 0; i < hand->size(); i++)
        {
            if (hand->at(i).returnTypeNum() == x.returnTypeNum())
            {

                valuableCount++;
            }
        }
        if (valuableCount < 2)
        {
            return false;
        }

        else
            ans = true;
    }
    /*
     If the card is not valuable, make sure that they have that card
     in their hand and are not trying to sell a card that doesn't exist.
     */
    else
    {
        for (unsigned int i = 0; i < hand->size(); i++)
        {
            if (hand->at(i).returnTypeNum() == x.returnTypeNum())
            {
                regularCount++;
            }
        }
        if (regularCount == 0)
        {
            return false;
        }
        else
        {
            ans = true;
        }
    }
    return ans;
}



bool Move:: validTakeMany(vector<Card> * exchangeHand, vector<Card> * exchangeMarket)
{
    bool ans = true;
    for (unsigned int i = 0; i < exchangeHand->size(); i++)
    {
        for (unsigned int j = 0; j < exchangeMarket->size(); j++)
        {
            if (exchangeHand->at(i).returnTypeNum() == exchangeMarket->at(j).returnTypeNum())
            {
                return false;
            }
            else if (exchangeMarket->at(i).returnTypeNum() == 1)
            {
                return false;
            }
            else
            {
                ans = true;
            }
        }
    }
    return ans;
}

bool Move:: validTakeOne(vector<Card> * hand, Card x)
{
    bool ans;
    if (hand->size() > 6)
    {
        ans = false;
    }
    else if (x.returnTypeNum() == 1)
    {
        ans = false;
    }
    else
        ans = true;
    return ans;
}


bool Move:: validTakeCamels(Market * market)
{
    if (market->getCamels() == 0)
    {
        return false;
    }
    else
        return true;
}




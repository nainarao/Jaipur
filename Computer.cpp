#include "Computer.h"
#include "Card.h"
#include "Move.h"
#include <ctime>
#include <cstdlib>

/*
    Randomly decides whether to sell cards or take cards
 */
void Computer:: movePlay(Market * market, Token * tokens, Player * otherPlayer)
{
    Move * curr;
    Card valInNeed = valuableNeedsCompletion(market); // Holds any valuables that need completion
    vector<Card> badCards = hasBadCards(tokens);
    /*
        Reasons for choosing to sell:
        1) If the other player has >15 points than you
        2) If the other player's hand is at 2 or less cards (good opportunity to catch up)
        3) If you have 7 cards in your hand

        Reasons to take cards:
        1) You have < 3 cards (you don't want that)
        2) If there's one particularly valuable card that you need to make a sale (Silver, Gold, Diamond)
        3) If you have two cards of one type and need three to get a bonus
        4) If your cards are mostly terrible and you want to switch them with better cards
        5) If there is a solid match of three in the market already
     */
    if (market->existsInMarket(valInNeed) == true)
    {
        takeChoice = 'a';
        takeOneCard(market, tokens, curr, valInNeed);
    }
    else if (this->getHand()->size() == 7)
    {
        sellCards(market, tokens, curr, otherPlayer);
    }
    else if (this->getHerd()->size() > 4 && getHand()->size() < 6)
    {
        takeManyCards(market, tokens, curr);
    }
    else if (this->getHand()->size() < 3)
    {
        takeChoice = 'a';
        takeCards(market, tokens, curr, otherPlayer);
    }
    else if(market->getCamels() > 2)
    {
        takeChoice = 'c';
        takeCards(market, tokens, curr, otherPlayer);
    }
    else if ( hasValidSale(tokens, curr) && ((otherPlayer->getPoints() > (this->getPoints()+10)) || (otherPlayer->getHand()->size() <= 3)
        || this->getHand()->size() == 7 || goodSale(tokens, curr) == true || hasThreeCards()))
    {
        sellCards(market, tokens, curr, otherPlayer);
    }
    else if (badCards.size() > 1)
    {
        takeChoice = 'b';
        takeCards(market, tokens, curr, otherPlayer);
    }
    else if (this->getHerd()->size() < 2 && market->getCamels() > 3)
    {
        takeChoice = 'c';
        takeCards(market, tokens, curr, otherPlayer);
    }
    else
    {
        takeChoice = 'a';
        takeCards(market, tokens, curr, otherPlayer);
    }
}


/*
    Sells all of the computer's best cards
 */
void Computer:: sellCards(Market * market, Token * tokens, Move * move, Player * player)
{
    vector<Card>invalidCards; // Used to hold the cards that are deemed invalid, and therefore should be neglected when deciding a move
    Card best;

    // Makes the sale based on which tokens will give the most points
    while (!move->validSale(this->getHand(), best))
    {
        invalidCards.push_back(best);
        best = returnBest(invalidCards, tokens);
    }


    // Make the sale
    int points = market->makeSale(tokens, this->getHand(), best);

    this->addPoints(points);
    return;
}






void Computer:: takeCards(Market * market, Token * tokens, Move * curr, Player * player)
{
    /*
        If x is greater than the threshold, take many cards
     */
    if (takeChoice == 'b')
    {
        takeManyCards(market, tokens, curr);
    }
    /*
        If x is less than or equal to the threshold, the computer will choose whether to take the camels or take one card
     */
    else if (takeChoice == 'a')
    {
        takeOneCard(market, tokens, curr);
    }

    else if (takeChoice == 'c')
    {
        takeCamels(market, tokens, curr);
    }

    return;
}


void Computer:: takeManyCards(Market * market, Token * tokens, Move * curr)
{
    vector<Card> marketExchange;
    vector<Card> handExchange;
    if (getHerd()->size() > 4)
    {
        int count = 0;
        for (auto it = market->getMarket()->begin(); it != market->getMarket()->end(); it++)
        {
            if (it->returnTypeNum() > 3)
            {
                marketExchange.push_back(*it);
                handExchange.push_back(this->getHerd()->at(count));
                count++;
            }
            if (count == 2)
            {
                break;
            }
        }
    }
    else
    {
        for (auto it = market->getMarket()->begin(); it != market->getMarket()->end(); it++)
        {
            for (unsigned int k = 0; k < this->getHand()->size(); k++)
            {
                if (it->returnTypeNum() > this->getHand()->at(k).returnTypeNum())
                {
                    marketExchange.push_back(*it);
                    handExchange.push_back(this->getHand()->at(k));
                }
            }
        }
    }
    if (curr->validTakeMany(&handExchange, &marketExchange))
    {
        market->makeTake(this->getHerd(), this->getHand(), &handExchange, &marketExchange, 1);
    }
    return;
}


void Computer:: takeCamels(Market * market, Token * tokens, Move * curr)
{
    vector<Card> marketExchange;
    vector<Card> handExchange;
    /*
     If the market has >2 camels, the computer will take the camels
     */
    if (market->getCamels() > 2)
    {
        if (curr->validTakeCamels(market))
        {
            market->makeTake(this->getHerd(), this->getHand(), &handExchange, &marketExchange, 3);
            return;
        }
        else
        {
            takeManyCards(market, tokens, curr);
        }
    }
}


void Computer:: takeOneCard(Market * market, Token * tokens, Move * curr, Card * need)
{
    vector<Card> marketExchange;
    vector<Card> handExchange;
    Card best = *market->getMarket()->data();
    unsigned long i;
    for (i = 0; i < market->getMarket()->size(); i++)
    {
        if (market->getMarket()->at(i).returnTypeNum() == need->returnTypeNum())
        {
            best = market->getMarket()->at(i);
        }
        else
        {
            takeManyCards(market, tokens, curr);
        }
    }
    handExchange.push_back(best);
    if (curr->validTakeOne(this->getHand(), best))
    {
        market->makeTake(this->getHerd(), this->getHand(), &handExchange, &marketExchange, 2);
    }
    return;
}


void Computer:: takeOneCard(Market * market, Token * tokens, Move * curr)
{
    vector<Card> marketExchange;
    vector<Card> handExchange;
    Card best = *market->getMarket()->data();
    unsigned long i;
    for (i = 0; i < market->getMarket()->size(); i++)
    {
        if (market->getMarket()->at(i).returnTypeNum() > best.returnTypeNum())
        {
            best = market->getMarket()->at(i);
        }
    }
    marketExchange.push_back(best);
    if (curr->validTakeOne(this->getHand(), best))
    {
        market->makeTake(this->getHerd(), this->getHand(), &handExchange, &marketExchange, 2);
    }
    return;
}

void Computer:: takeOneCard(Market * market, Token * tokens, Move * curr, Card x)
{
    vector<Card> marketExchange;
    vector<Card> handExchange;
    marketExchange.push_back(x);
    if(curr->validTakeOne(this->getHand(), x))
    {
        market->makeTake(this->getHerd(), this->getHand(), &handExchange, &marketExchange, 2);
    }
}


/*
    Using the cards that have already been deemed invalid, it looks for the next best card
 */
Card Computer:: returnBest(vector<Card> invalidCards, Token * tokens)
{
    Card best = Card(1);
    int currPoints = 0;
    int bestPoints = 0;
    for (unsigned int i = 0; i < this->getHand()->size(); i++)
    {
        bool invalid = false;
        for (unsigned int j = 0; j < invalidCards.size(); j++)
        {

            if (this->getHand()->at(i).returnTypeNum() == invalidCards.at(j).returnTypeNum())
            {
                invalid = true;
                break;
            }
            else
            {
                invalid = false;
            }
        }
        auto it = tokens->getTok().find(this->getHand()->at(i).returnType());
        vector<int> v = it->second;
        if (v.size() > 0)
        {
            currPoints = v.at(0);
            if (invalid == false && best.returnTypeNum()!=1)
            {
                auto bestIt = tokens->getTok().find(best.returnType());
                vector<int> bestV = bestIt->second;
                bestPoints = bestV.at(0);
            }

            if (invalid == false &&  currPoints > bestPoints)
            {
                best = this->getHand()->at(i);
            }
            invalid = false;
        }
    }
    bool invalid = false;
    if (best.returnTypeNum() == 1)
    {
        for (unsigned int i = 0; i < this->getHand()->size(); i++)
        {
            for (unsigned int j = 0; j < invalidCards.size(); j++)
            {
                if (this->getHand()->at(i).returnTypeNum() == invalidCards.at(j).returnTypeNum())
                {
                    invalid = true;
                    break;
                }
                else
                {
                    invalid = false;
                }
        }
        if (invalid == false)
        {
            best = this->getHand()->at(i);
            break;
        }
    }
    }
    return best;
}


/*
    Checks to see if any valuable cards need completion for sale
 */
Card Computer:: valuableNeedsCompletion(Market * market)
{
    Card val;
    int silverCount = 0;
    int goldCount = 0;
    int diamondCount = 0;
    for (unsigned int i = 0; i < this->getHand()->size(); i++)
    {
        if (this->getHand()->at(i).returnTypeNum() == 5)
        {
            silverCount++;
        }
        else if (this->getHand()->at(i).returnTypeNum() == 6)
        {
            goldCount++;
        }
        else if (this->getHand()->at(i).returnTypeNum() == 7)
        {
            diamondCount++;
        }
    }
    if (market->existsInMarket(Card(7)) && diamondCount == 1)
    {
        val = Card(7);
    }
    if (market->existsInMarket(Card(6)) &&goldCount == 1)
    {
        val = Card(6);
    }
    else if  (market->existsInMarket(Card(5)) &&silverCount == 1)
    {
        val = Card(5);
    }
    return val;
}


/*
    Checks if part of the hand of the person is full of bad cards.
    It decides if it is a bad card if:
    a) There are no more tokens for that card
    b) You have too many camels (greater than 5)
 */
vector<Card> Computer:: hasBadCards(Token * tokens)
{

    vector<Card> badCards;
    for (unsigned int i = 0; i < this->getHand()->size(); i++)
    {
        auto it = tokens->getTok().find(this->getHand()->at(i).returnType());
        vector<int> v = it->second;
        if (v.size() > 0)
        {
            int currPoints = v.at(0);
            if (currPoints == 0)
            {
                badCards.push_back(this->getHand()->at(i));
            }
            else if(this->getHerd()->size() > 5)
            {
                badCards.push_back(Card(1));
            }
        }
    }
    return badCards;
}


bool Computer:: goodSale(Token * tokens, Move * move)
{
    bool ans = false;
    vector<Card> invalidCards;
    Card best;
    int count = 0;
    int potentialPoints = 0;

    while (!move->validSale(this->getHand(), best))
    {
        invalidCards.push_back(best);
        best = returnBest(invalidCards, tokens);
    }
    for (unsigned int i = 0; i < this->getHand()->size(); i++)
    {
        if (getHand()->at(i).returnTypeNum() == best.returnTypeNum())
        {
            count++;
        }
    }

    auto it = tokens->getTok().find(best.returnType());
    vector<int> v = it->second;
    for (unsigned int k = 0; k < v.size(); k++)
    {
        potentialPoints += v.at(k);
    }

    if (potentialPoints > 5|| count > 2)
    {
        ans = true;
    }
    else
        ans = false;

    return ans;
}


bool Computer:: hasValidSale(Token * tokens, Move * move)
{
    bool ans = false;
    vector<Card>invalidCards;
    Card best = Card(1);
    while (!move->validSale(this->getHand(), best))
    {
        if (this->getHand()->size() + 1 == invalidCards.size())
        {
            break;
        }
        invalidCards.push_back(best);
        best = returnBest(invalidCards, tokens);
    }
    if (best.returnTypeNum() == 1)
    {
        ans = false;
    }
    else
        ans = true;
    return ans;
}


bool Computer:: hasThreeCards()
{
    bool ans = false;
    int count = 0;
    for (unsigned int i = 0; i < getHand()->size(); i++)
    {
        for (int k = 1; k < 8; k++)
        {
            if (getHand()->at(i).returnTypeNum() == k)
            {
                count++;
            }
        }

        if (count == 3)
        {
            return true;
        }

    }
    return ans;
}


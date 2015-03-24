
#include <cstdlib>
#include <iostream>
#include <vector>
#include "Deck.h"
#include "Card.h"

using namespace std;
Deck::Deck()
{
}

void Deck:: fill()
{
    for (int i = 0 ; i < 8; i++)
    {
        cVector.push_back(Card(1));
    }
    for (int i = 0 ; i < 10; i++)
    {
        cVector.push_back(Card(2));
    }
    for (int i = 0 ; i < 8; i++)
    {
        cVector.push_back(Card(3));
    }
    for (int i = 0 ; i < 8; i++)
    {
        cVector.push_back(Card(4));
    }
    for (int i = 0 ; i < 6; i++)
    {
        cVector.push_back(Card(5));
    }
    for (int i = 0 ; i < 6; i++)
    {
        cVector.push_back(Card(6));
    }
    for (int i = 0 ; i < 6; i++)
    {
        cVector.push_back(Card(7));
    }

}



void Deck::printDeck()
{
    if (this->getVector()->size() != 0)
    {
        cout << "Deck: " << getVector()->size() << ": \u25AE";
    }
}

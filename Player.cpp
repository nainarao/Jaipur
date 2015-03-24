
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include "Player.h"
#include "Card.h"
#include <time.h>

using std::ostream;
using std::string;
using std::vector;
using std::map;

//initializes name with n, all other variables to 0 or nullptr
Player::Player(string n)
{
    name = n;
    numSeals = 0;
    herdCount = 0;
    tokenPoints = 0;
}

Player::~Player(){}

void Player::addCard(Card x)
{
    this->hand.push_back(x);
}

void Player:: addHerdCard(Card x)
{
    this->herd.push_back(x);
}

int Player:: getPoints()
{
    return tokenPoints;
}

void Player::fillHand(Deck * deck)
{
    for (int i = 0; i < 5; i++)
    {
        int x = rand() % (deck->getVector()->size());
        if (deck->getVector()->at(x).returnTypeNum() == 1)
        {
            this->herd.push_back(deck->getVector()->at(x));
        }
        else
            this->hand.push_back(deck->getVector()->at(x));
        deck->getVector()->erase(deck->getVector()->begin()+x);
    }
}


void Player::printPlayer()
{
    const int typeWidth = 13;
    const char separator = ' ';

    cout << name << ": ";
    cout << tokenPoints << " Points" << endl;
    cout << "Seal Count: " << numSeals << endl;
    cout << left << setw(typeWidth)<< "Hand:";
    for (unsigned int i = 0; i < hand.size(); i++)
    {
        cout << left << setw(typeWidth) << setfill(separator) << hand.at(i).returnType();
    }
    cout << endl;
    cout << left << setw(typeWidth) << " ";
    for (unsigned int i = 0; i < hand.size(); i++)
    {
        cout << left << setw(15) << setfill(' ') << "\u25AE";
    }
    cout <<endl;
    cout << "Herd: " << herd.size() << " ";
    for (unsigned int i = 0; i < herd.size(); i++)
    {
        cout << left << setw(5) << setfill(' ') << "\u25AE";
    }
}


bool Player:: existsInHand(vector<Card> * exchange)
{
    bool ans = false;
    for (unsigned int i = 0; i < exchange->size(); i++)
    {
        for (unsigned int j = 0; j < hand.size(); j++)
        {
            if (hand.at(j).returnTypeNum() == exchange->at(i).returnTypeNum())
            {
                ans = true;
                break;
            }
            else
                ans = false;
        }
    }
    return ans;
}


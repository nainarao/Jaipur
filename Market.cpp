#include "Market.h"
#include "Deck.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "UI.h"
#include <curses.h>

WINDOW * mark;

Market:: Market(){}

void Market :: setUpMarket(Deck * deck)
{
    int max_x = getmaxx(stdscr);
    int max_y = getmaxy(stdscr);
    mark = newwin(max_y*(.15), max_x*(.20)-1, max_y*(.80), max_x*(.80));
    refreshPage();
    wborder(mark, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(mark);

    for (int i = 0; i < 3; i++)
    {
        marketCards.push_back(Card(1));
    }
    for (int j = 0; j < 2; j++)
    {
        int x = rand() % (deck->getVector()->size());
        Card c = deck->getVector()->at(x);
        marketCards.push_back(c);
        deck->getVector()->erase(deck->getVector()->begin() + x);
    }
}

void Market :: fillMarket(Deck * deck)
{
    //refreshPage();
    if (this->getMarket()->size() < 5)
    {
        unsigned long count = 0;
        count = 5 - this->getMarket()->size();
        for (unsigned int j = 0; j < count; j++)
        {
            if (deck->getVector()->size() == 0)
            {
                return;
            }
            int x = rand() % (deck->getVector()->size());
            Card c = deck->getVector()->at(x);
            marketCards.push_back(c);
            deck->getVector()->erase(deck->getVector()->begin()+x);
        }
    }
    return;
}


bool Market:: existsInMarket(Card x)
{
    bool ans = false;
    for (unsigned int i = 0; i < this->getMarket()->size(); i++)
    {
        if (this->getMarket()->at(i).returnTypeNum() == x.returnTypeNum())
        {
            ans = true;
            break;
        }
    }
    return ans;
}


bool Market:: existsInMarket(vector<Card> * exchange)
{
    bool ans = false;
    for (unsigned int i = 0; i < exchange->size(); i++)
    {
        for (unsigned int j = 0; j < marketCards.size(); j++)
        {
            if (marketCards.at(j).returnTypeNum() == exchange->at(i).returnTypeNum())
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


int Market :: makeSale(Token * tokens, vector<Card> * hand, Card x)
{
    refreshPage();
    int points = 0;
    /*
        Counts how many tokens they will be getting and erases the cards from the players hand.
     */
    int count = 0;
    for (unsigned int i = 0; i < hand->size(); i++)
    {
        if (hand->at(i).returnTypeNum() == x.returnTypeNum())
        {
            hand->erase(hand->begin()+i);
            count++;
            i--;
        }
    }
    if (count >= 3)
    {
        points += tokens->bonusPoints(count);
    }
    points += tokens->salePoints(count, x.returnTypeNum());
    mvwprintw(mark, 2, 2, "Last move:");
    mvwprintw(mark, 4, 2, "Player sold %d %ss for %d points", count, x.returnType().c_str(), points);
    wrefresh(mark);
    points += tokens->salePoints(count, x.returnTypeNum());
    return points;
}

int Market::makeSale(Token * tokens, vector<Card> * hand, Card x, int number)
{
    refreshPage();
    int points =0;
    int count = 0;
    for (unsigned int i = 0; i < hand->size(); i++)
    {
        if (hand->at(i).returnTypeNum() == x.returnTypeNum())
        {
            hand->erase(hand->begin()+i);
            count++;
            i--;
        }
        if (count == number)
        {
            break;
        }
    }
    if (count >= 3)
    {
        points += tokens->bonusPoints(count);
    }
    points += tokens->salePoints(count, x.returnTypeNum());
    mvwprintw(mark, 2, 2, "Last move:");
    mvwprintw(mark, 4, 2, "Player sold %d %ss for %d points", count, x.returnType().c_str(), points);
    wrefresh(mark);
    return points;
}

void Market:: makeTake(vector<Card> * herd, vector<Card> * hand, vector<Card> * exchangeCards, vector<Card> * marketCards, int moveID)
{
    // Take several cards logic
    if (moveID == 1)
    {
        // Erases the cards from the hand/herd and adds them to the market
        for (unsigned int i = 0; i < exchangeCards->size(); i++)
        {
            if( exchangeCards->at(i).returnTypeNum() == 1)
            {
                this->getMarket()->push_back(Card(1));
                herd->pop_back();
            }
            else
            {
                for (unsigned int j = 0; j < hand->size(); j++)
                {
                    if (hand->at(j).returnTypeNum() == exchangeCards->at(i).returnTypeNum())
                    {
                        this->getMarket()->push_back(hand->at(j));
                        hand->erase(hand->begin()+j);
                        break;
                    }
                }
            }
        }
        // Erases the cards from the market and adds them to the hand
        for (unsigned int i = 0; i < marketCards->size(); i++)
        {
            for (unsigned int j = 0; j < this->getMarket()->size(); j++)
            {
                if (this->getMarket()->at(j).returnTypeNum() == marketCards->at(i).returnTypeNum())
                {
                    hand->push_back(this->getMarket()->at(j));
                    this->getMarket()->erase(this->getMarket()->begin()+j);
                    break;
                }
            }
        }
    refreshPage();
    mvwprintw(mark, 2, 2, "Last move:");
    mvwprintw(mark, 4, 2, "Player exchanged %d cards", exchangeCards->size());
    wrefresh(mark);
    }

    // Take one card logic
    else if (moveID == 2)
    {
        for (unsigned int i = 0; i < this->getMarket()->size(); i++)
        {
            if (this->getMarket()->at(i).returnTypeNum() == marketCards->at(0).returnTypeNum())
            {
                string took = this->getMarket()->at(i).returnType();
                hand->push_back(this->getMarket()->at(i));
                this->getMarket()->erase(getMarket()->begin() + i);
                    refreshPage();
                    mvwprintw(mark, 2, 2, "Last move:");
                    mvwprintw(mark, 4, 2, "Player took 1 %s from market", took.c_str());
                    wrefresh(mark);
                break;
            }
        }
    }

    // Take camels logic
    else if (moveID == 3)
    {
        for (unsigned int i = 0; i < this->getMarket()->size(); i++)
        {
            if (this->getMarket()->at(i).returnTypeNum() == 1)
            {
                herd->push_back(Card(1));
                this->getMarket()->erase(this->getMarket()->begin()+i);
                i--;
            }
        }
        refreshPage();
        mvwprintw(mark, 2, 2, "Last move:");
        mvwprintw(mark, 4, 2, "Player took all camels from market");
        wrefresh(mark);
    }
}

int Market:: getCamels()
{
    int count = 0;
    for(vector<Card>::const_iterator i = marketCards.begin(); i != marketCards.end(); ++i)
    {
        if((i->returnTypeNum()) == 1)
        {
            count++;
        }
    }
    return count;
}

void Market::refreshPage()
{
    wclear(mark);
    wborder(mark, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(mark);
}



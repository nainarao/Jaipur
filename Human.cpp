#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <exception>
#include "Card.h"
#include "Human.h"
#include "Market.h"
#include "Token.h"
#include "Move.h"
#include "UI.h"
#include <curses.h>


using std::ostream;
using std::string;
using std::vector;
using std::map;

using std::cout;
using std::cin;
using std::endl;

WINDOW * moves;

//Constructor using Player constructor
Human::Human(string n) : Player(n)
{
}


//allows Human Player to choose move
void Human:: movePlay(Market* market, Token *tokens, Player * player)
{
    Move * curr;
    int option;
    //intrflush(moves, TRUE);
    int max_x = getmaxx(stdscr);
    int max_y = getmaxy(stdscr);
    moves = newwin(max_y*(.20), max_x*(.50), max_y*(.80), 0);
    refreshWin();
    mvwprintw(moves, 2, 2,"===%s's Turn===", getName().c_str());
    mvwprintw(moves, 3, 2, "1) Take cards");
    mvwprintw(moves, 4, 2, "2) Sell cards");
    mvwprintw(moves, 5, 2, "Enter option: ");
    echo();
    wrefresh(moves);
    move(max_y*(.80) + 5, 16);
    flushinp();
    scanw("%d", &option);
    if(option == 1)
    {
        takeCards(market, tokens, curr, player);
    }

    else if(option == 2)
    {
        sellCards(market, tokens, curr, player);
    }
    else
    {
        refreshWin();
        mvwprintw(moves, 2, 2, "Error: Invalid Option. Press any key to continue");
        wrefresh(moves);
        getch();
        movePlay(market, tokens, player);
    }
}

//helper method for chooseMove() when selling cards
void Human:: sellCards(Market * market, Token *tokens, Move * curr, Player * player)
{
    int max_y = getmaxy(stdscr);
    refreshWin();
    mvwprintw(moves, 2, 2, "Which type of cards would you like to sell? Type '0' to return back.");
    mvwprintw(moves, 3, 2, "Type: ");
    move(max_y*(.80)+3, 8);
    wrefresh(moves);
    char typ[10]; //type of card to remove
    getstr(typ);
    string type(typ);

    if (type == "0")
    {
        movePlay(market, tokens, player);
        return;
    }


    Card sale(type);
    vector<Card> handSale;
    handSale.push_back(sale);
   try {
        handSale.push_back(sale);
        if (existsInHand(&handSale) == false)
        {
            throw 2;
        }
    } catch (int x) {
        handSale.pop_back();
        refreshWin();
        mvwprintw(moves, 2, 2, "Error! That card does not exist in your hand!");
        mvwprintw(moves, 3, 2, "Redoing Sale. Press Space to continue");
        wrefresh(moves);
        getchar();
        sellCards(market, tokens, curr, player);
    }

    if (sale.returnTypeNum() == -1)
    {
        sellCards(market, tokens, curr, player);
    }
    if(curr->validSale(this->getHand(), sale))
    {
        int number;
        int count = 0;
        mvwprintw(moves, 4, 2,"How many would you like to sell?");
        mvwprintw(moves, 5, 2, "Number: ");
        move(max_y*(.80)+5, 11);
        wrefresh(moves);
        scanw("%d", &number);
        wrefresh(moves);

        for (unsigned int i = 0; i < this->getHand()->size(); i++)
        {
            if(getHand()->at(i).returnTypeNum() == sale.returnTypeNum())
            {
                count++;
            }
        }
        if (count < number)
        {
            refreshWin();
            mvwprintw(moves, 2, 2, "Error! You don't have enough of those cards! Press Space to continue");
            wrefresh(moves);
            getchar();
            movePlay(market, tokens, player);
            return;
        }
        tokenPoints += market->makeSale(tokens, this->getHand(), sale, number);
        turnOver();
    }
    else
    {
        refreshWin();
        mvwaddstr(moves, 2, 2, "Error: Invalid move! Press space to continue");
        wrefresh(moves);
        getchar();
        movePlay(market, tokens, player);
    }
    return;
}

void Human:: takeCards(Market * market, Token *tokens, Move * curr, Player * player)
{
    refreshWin();
    mvwprintw(moves, 2, 2, "How would you like to take cards?");
    int max_y = getmaxy(stdscr);

    int option;
    mvwprintw(moves, 3, 2, "1) Exchange several goods ");
    mvwprintw(moves, 4, 2, "2) Take one good ");
    mvwprintw(moves, 5, 2, "3) Take all camels");
    mvwprintw(moves, 6, 2, "Enter option: ");

    move(max_y*(.80)+6, 16);
    wrefresh(moves);
    scanw("%d", &option);

    if(option == 1)
    {
        takeMultipleCards(market, curr, tokens, player);
    }

    else if(option == 2)
    {

        refreshWin();
        mvwprintw(moves, 2, 2, "Which good would you like to take?");
        mvwprintw(moves, 3, 2, "Card: ");
        move(max_y*(.80)+3, 7);
        wrefresh(moves);
        char card[10];
        getstr(card);
        Card take(card);
        takeOneCard(market, take, curr, tokens, player);
    }

    else if(option == 3)
    {
        refreshWin();
        mvwprintw(moves, 2, 2, "Attempting to take all camels..... (press Space to continue)");
        wrefresh(moves);
        getchar();
        takeCamels(market, curr, tokens, player);
    }

    else if (option == 0)
    {
        movePlay(market, tokens, player);
    }

    else
    {
        refreshWin();
        mvwprintw(moves, 5, 2, "Invalid option. Press Space to continue");
        wrefresh(moves);
        getchar();
        takeCards(market, tokens, curr, player);
    }

}


void Human:: takeOneCard(Market * market, Card card, Move * curr, Token * tokens, Player * player)
{
    refreshWin();
    vector<Card> exchangeCards;
    vector<Card> marketCards;
    marketCards.push_back(card);
    if(curr->validTakeOne(this->getHand(), Card(card)) && market->existsInMarket(card))
    {
        market->makeTake(this->getHerd(), this->getHand(), &exchangeCards, &marketCards, 2);
        turnOver();
    }
    else
    {
        mvwprintw(moves, 5, 2, "Error! Invalid option. Press Space to continue");
        wrefresh(moves);
        getchar();
        this->movePlay(market, tokens, player);
    }
}



void Human:: takeMultipleCards(Market * market, Move * curr, Token * tokens, Player * player)
{
    int max_y = getmaxy(stdscr);
    refreshWin();
    bool stop = false;
    vector<Card> handExchange;
    vector<Card> marketExchange;

    while(stop==false)
    {
        int ans = 0;
        mvwprintw(moves, 2, 2, "How many goods would you like to take?");
        mvwprintw(moves, 3, 2, "Number: ");
        move(max_y*(.80)+3, 10);
        wrefresh(moves);
        scanw("%d", &ans);
        char card[10];
        unsigned int camelCount = 0;
        try
        {
            refreshWin();
            mvwprintw(moves, 2, 2, "What goods would you like to take?");
            for (int i = 0; i < ans; i++)
            {
                mvwprintw(moves, i+3, 2, "%d) ", i+1);
                move((max_y*(.80))+ i+3, 6);
                wrefresh(moves);
                getstr(card);
                marketExchange.push_back(Card(card));
                if (market->existsInMarket(&marketExchange) == false)
                {
                    throw 1;
                }
            }
        }
        catch (int x)
        {
            refreshWin();
            mvwprintw(moves, 2, 2, "Error! %s does not exist in the Market!", Card(card).returnType().c_str());
            mvwprintw(moves, 3, 2, "Redo taking cards! Press Space to continue");
            wrefresh(moves);
            getchar();
            marketExchange.pop_back();
            takeMultipleCards(market, curr, tokens, player);
        }

        refreshWin();
        mvwprintw(moves, 2, 2, "Which goods would you like exchange: ");
        for (int i = 0; i < ans; i++)
        {
            mvwprintw(moves, i+3, 2, "%d) ", i+1);
            move((max_y*(.80)+i+3), 6);
            wrefresh(moves);
            getstr(card);
            Card x(card);
            if (x.returnTypeNum() == 1)
            {
                camelCount++;
            }
            try
            {
                unsigned long roomLeft = (7 - getHand()->size()) - camelCount;
                handExchange.push_back(x);
                if ((x.returnTypeNum() == 1) && camelCount > getHerd()->size())
                {
                    throw 1;
                }
                else if (x.returnTypeNum() != 1 && existsInHand(&handExchange) == false)
                {
                    throw 1;
                }
                else if (roomLeft == 0)
                {
                    throw 2;
                }
            }
            catch (int y)
            {
                if ( y == 1 )
                {
                    refreshWin();
                    mvwprintw(moves, 2, 2, "Error! %s does not exist in your hand/herd!", x.returnType().c_str());
                }
                else if (y == 2)
                {
                    refreshWin();
                    mvwprintw(moves, 2, 2, "Error! You cannot exchange camels! Hand will be > 7!");
                }
                mvwprintw(moves, 3, 2, "Redo taking cards! Press Space to continue");
                wrefresh(moves);
                handExchange.pop_back();
                getchar();
                takeMultipleCards(market, curr, tokens, player);
            }
            if (marketExchange.size() == 5)
            {
                refreshWin();
                mvwprintw(moves, 2, 2, "You have reached the limit of cards that you can take!");
                mvwprintw(moves, 3, 2, "Press space to continue");
                wrefresh(moves);
                getchar();
                stop = true;
            }
        stop = true;
        }
    }

    if (curr->validTakeMany(&handExchange, &marketExchange))
    {
        market->makeTake(this->getHerd(), this->getHand(), &handExchange, &marketExchange, 1);
    }
    else
    {
        refreshWin();
        mvwprintw(moves, 2, 2, "Error! Invalid move! Press anywhere continue");
        wrefresh(moves);
        getch();
        this->movePlay(market, tokens, player);
    }
}

void Human:: takeCamels(Market * market, Move * curr, Token * tokens, Player * player)
{
    vector<Card> exchangeCards;
    vector<Card> marketCards;
    if (curr->validTakeCamels(market))
    {
        mvwprintw(moves, 3, 2, "All camels taken! Press Space to end turn");
        wrefresh(moves);
        getchar();
        turnOver();
        market->makeTake(this->getHerd(), this->getHand(), &exchangeCards, &marketCards, 3);
    }
    else
    {
        mvwprintw(moves, 3, 2, "Error! Move not valid. Press Space to continue");
        wrefresh(moves);
        getchar();
        this->movePlay(market, tokens, player);
    }
}

void Human::refreshWin()
{
    wclear(moves);
    wborder(moves, '|', '|', '-', '-', '+', '+', '+', '+');
}

void Human::turnOver()
{
    refreshWin();
    mvwprintw(moves, 2, 2, "Turn over!");
    mvwprintw(moves, 4, 2, "Press space bar to continue");
    wrefresh(moves);
}

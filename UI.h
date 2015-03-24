#ifndef UI_H
#define UI_H

#include "Card.h"
#include <stdlib.h>
#include <curses.h>
#include "Player.h"
#include "Computer.h"
#include "Human.h"
#include "Market.h"
#include "Deck.h"
#include "Token.h"

using namespace std;

const string player1 = "P1 Hand";
const string player2 = "P2 Hand";
#define cspace 12

class UI{

    friend class Game;
    int p1x, p2x, p1y;
    int cx, cy,len;
    int cpos;
    void blankMarket();
    int turn;
    Market market;

public:
    UI(int);
    UI();
    void setBoard();
    void drawCard(int x, int y, int z);
    void showHand(int play, vector<Card>hand);
    void drawHand(int play);
    void drawMarket(vector<Card> *market);
    void clearBoard();
    void permBoard();
    void drawAllTokens(Token tokens);
    void drawTokens(map<string, vector<int> > tokens);
    void drawBonusTok(map<string, vector<int> > bonus);
    void drawTok(int type, int x, int y, char val);
    void assignColor(string type);
    void printMessage(string);
    void printPlayer(Player * p1, Player * p2);
    void assignColor(int type);
    void assignColor();
};

#endif // UI_H

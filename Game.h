//
//  Game.h
//  IntermediateProject
//
//  Created by Matthew Kosarek on 11/17/14.
//  Copyright (c) 2014 Matthew Kosarek. All rights reserved.
//
#ifndef IntermediateProject_Game_h
#define IntermediateProject_Game_h

#include "UI.h"
#include "Player.h"
#include "Computer.h"
#include "Human.h"
#include "Market.h"
#include "Deck.h"
#include "Token.h"

/*
 Game.h
 The Game class will contain two players, a deck,
 60 tokens, and a market.

 When initialize is called, the two
 players will be prompted for their names, the deck will be
 randomly filled with the correct amount of cards, the array
 of tokens will be filled with the correct number of each
 token type, and the market will be initialized.

 printUI will print how the game currently looks when it is
 called.
 */

class Game
{
private:
    Player * p1;
    Player * p2;
    Deck deck;
    Token tokens;
    Market market;
    int turn;
    UI ui;

public:
    Game();
    Player* getPlayer(int turn) {if(turn ==1) {return p1;} else {return p2;}}
    Token getTokens() {return tokens;}
    Market getMarket() {return market;}
    void initialize();
    void setPlayers();
    void play();
    bool EndRound();
    bool EndGame();
    void printUI();
    void printUI(int turn, vector<Card>*hand, Token tokens);
    void clearUI();
    void refreshPage();
    void clearWindow();
    void endRound(string message);
};

#endif


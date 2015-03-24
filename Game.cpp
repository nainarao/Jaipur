//
//  Game.cpp
//  IntermediateProject
//
//  Created by Matthew Kosarek on 11/17/14.
//  Copyright (c) 2014 Matthew Kosarek. All rights reserved.
//
#include <cstdlib>
#include <iostream>
#include <exception>
#include "Game.h"
#include "Player.h"
#include "Computer.h"
#include "UI.h"
#include <curses.h>

using namespace std;

WINDOW *welcome;

Game::Game()
{
    srand(1);
    initialize();
}

void Game::initialize()
{
    setPlayers();
    turn = 0;
    play();
}

void Game::setPlayers(){

    int option;
    int max_x = getmaxx(stdscr);
    int max_y = getmaxy(stdscr);

    welcome = newwin(max_y*(.20), max_x, max_y*(.80), 0);
    scrollok(welcome, TRUE);
    getch();
    raw();
    echo();
    wborder(welcome, '|', '|', '-', '-', '+', '+', '+', '+');
    mvwprintw(welcome, 1, 2, "------- WELCOME TO JAIPUR ------");
    mvwprintw(welcome, 2, 2, "Choose player settings:" );
    mvwprintw(welcome, 3, 2, "1) Play Computer vs. Computer");
    mvwprintw(welcome, 4, 2, "2) Play Human vs. Computer ");
    mvwprintw(welcome, 5, 2, "3) Play Human vs. Human ");
    mvwaddstr(welcome, 7, 2, "Choice: ");
    move(max_y*(.80)+7, 10);
    wrefresh(welcome);
    scanw("%d", &option);

    if(option == 1) {
        p1 = new Computer("Computer 1");
        p2 = new Computer("Computer 2");
        refreshPage();
        wrefresh(welcome);
    }
    else if(option == 2) {
        refreshPage();
        char name[20];
        mvwaddstr(welcome, 1, 2, "Enter your name: ");
        move(max_y*(.80)+1, 20);
        wrefresh(welcome);
        getstr(name);

        p1 = new Human(name);
        p2 = new Computer("Computer");
    }

    else if(option == 3) {
        refreshPage();
        //string name1;
        char name1[20];
        mvwaddstr(welcome, 1, 2, "Enter Player 1's name: ");
        move(max_y*(.80)+1, 25);
        wrefresh(welcome);
        getstr(name1);

        char name2[20];
        mvwaddstr(welcome, 2, 2, "Enter Player 2's name: ");
        move(max_y*(.8)+2, 25);
        wrefresh(welcome);
        getstr(name2);

        p1 = new Human(name1);
        p2 = new Human(name2);
    }
    else{
        refreshPage();
        mvwaddstr(welcome, 1, 2, "Invalid option.");
        setPlayers();
    }
    refreshPage();
    mvwprintw(welcome, 5, 2, "Players %s and %s created!!", p1->getName().c_str(), p2->getName().c_str());
}

void Game::printUI()
{
    if((turn % 2) == 0) {turn = 2;}
    else{turn = 1;}
    UI ui;
    ui.permBoard();
    ui.drawHand(turn);
    ui.showHand(turn, *getPlayer(turn)->getHand());
    ui.drawMarket(market.getMarket());
    ui.drawAllTokens(tokens);
    ui.printPlayer(p1, p2);
}

void Game::clearUI() {
    ui.clearBoard();
}

void Game::endRound(string message)
{
    ui.printMessage(message);
}

void Game::play()
{
    while(!EndGame())
    {
        deck.getVector()->erase(deck.getVector()->begin(), deck.getVector()->end());
        tokens.deleteAllToks();
        tokens.fillTokens();
        tokens.fillbonusTok();
        deck.fill();
        market.getMarket()->erase(market.getMarket()->begin(), market.getMarket()->end());
        market.setUpMarket(&deck);
        p1->getHand()->erase(p1->getHand()->begin(), p1->getHand()->end());
        p2->getHand()->erase(p2->getHand()->begin(), p2->getHand()->end());
        p1->getHerd()->erase(p1->getHerd()->begin(), p1->getHerd()->end());
        p2->getHerd()->erase(p2->getHerd()->begin(), p2->getHerd()->end());
        p1->fillHand(&deck);
        p2->fillHand(&deck);
        while(!EndRound())
        {
            clearWindow();
            turn++;
            printUI();
            p1->movePlay(&market, &tokens, p2);
            clearUI();
            market.fillMarket(&deck);

            turn++;
            printUI();
            p2->movePlay(&market, &tokens, p1);
            clearUI();
            market.fillMarket(&deck);
        }
        endRound("The round has ended!");
        if (p1->getHerd()->size() > p2->getHerd()->size())
        {
            p1->addPoints(5);
        }
        else if (p1->getHerd()->size() < p2->getHerd()->size())
        {
            p2->addPoints(5);
        }
        if (p1->getPoints() > p2->getPoints())
        {
            p1->addSeal();
        }
        else
        {
            p2->addSeal();
        }
        p1->resetPoints();
        p2->resetPoints();
    }
    clearUI();
    endRound("The game is over!");
}

bool Game::EndRound()
{
    if (deck.getVector()->size() == 0)
    {
        return true;
    }
    else if( tokens.getEmptyTok() == 3 )
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool Game::EndGame()
{
    if (p1->sealCount() == 2 || p2->sealCount() == 2)
    {
        cout << p1->sealCount() << endl;
        cout << p2->sealCount() << endl;
        return true;
    }
    else
        return false;
}

void Game::refreshPage()
{
    wclear(welcome);
    wborder(welcome, '|', '|', '-', '-', '+', '+', '+', '+');
}

void Game::clearWindow()
{
    wrefresh(welcome);
    wclear(welcome);
    wrefresh(welcome);
    delwin(welcome);
}


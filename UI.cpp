
#include <iostream>
#include <string.h>
#include <string>
#include "UI.h"
#include <stdlib.h>
#include <curses.h>
#include "Card.h"
#include "Player.h"
#include "Computer.h"
#include "Human.h"
#include "Market.h"
#include "Deck.h"
#include "Token.h"
#include "Game.h"

using namespace std;

WINDOW *win;
WINDOW *sub;


UI::UI()
{
    int max_x = getmaxx(stdscr);
    int max_y = getmaxy(stdscr);
    win = newwin(max_y*(.80), max_x, 0, 0);
    turn = 1;
    p1x = 3, p2x = 25;
    p1y = 120;
    cx = 14, cy = 65;
    cpos = 70;
    len = 9;
}

void UI::showHand(int play, vector<Card> hand)
{
    int tempy =0, pcx =0;;
    int tempx = 0;
    string turn;
    start_color();
    init_pair(3, COLOR_RED, COLOR_BLACK);
    int numCard = 49;
    if(play == 1)
	{
	  tempy = p1y;
	  tempx = p1x, pcx = p1x;
	  turn = player1;
	  init_pair(1, COLOR_BLACK, COLOR_RED);
	}
    else if (play == 2)
	{
	  tempy = p1y;
	  tempx = p2x, pcx = p2x;
	  turn = player2;
	  init_pair(2, COLOR_BLACK, COLOR_BLUE);
	}
    for(unsigned int i = 0; i < hand.size(); i++)
	{
       wattron(win, COLOR_PAIR(play));
       wattron(win, A_BOLD);
	   int j = 0;
	   int lon = hand[i].returnType().length();
       string mcard = hand[i].returnType();

       if(!(mcard.compare("Camel")== 0)){
        drawCard(tempx, tempy, len);
        wattroff(win, COLOR_PAIR(play));
       while(j <= 7 && j<lon)
        {
            wmove(win, tempx+1, tempy+5);
            if(j==0) {
                wmove(win, tempx+1, tempy+2);
                wattron(win, COLOR_PAIR(3));
                char c = numCard++;
                waddch(win, c);
                tempx++;
                wattroff(win, COLOR_PAIR(3));
                wmove(win, tempx+1, tempy+5);
            }
            waddch(win, mcard[j]);
            j++;
            tempx++;
        }
	    wrefresh(win);
        tempx = pcx;
        tempy -= cspace;
       }
	}
	wrefresh(win);
    touchwin(win);
}


void UI::drawHand(int play)
{
    start_color();
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    wattron(win, COLOR_PAIR(3));
    int pcx = 0;
    int pcy = 0;
    string card;
    if(play == 2)
    {
      pcx = p1x;
      pcy = p1y;
      card = player1;
    }
    else if(play == 1)
    {
      pcx = p2x;
      pcy = p1y;
      card = player2;
    }
    drawCard(pcx, pcy, len);
    touchwin(win);

    int tempy = pcy+5,x = 1;
    int tempx = pcx+1;
    int lon = card.length();
    while(lon > 0)
    {
      wmove(win, tempx, tempy);
      waddch(win, card[x-1]);
      lon--;
      x++;
      tempx++;
    }
    wattroff(win, COLOR_PAIR(3));
    wrefresh(win);
    touchwin(win);

}

void UI::drawMarket(vector<Card>* market)
{
    start_color();
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK);//added
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    int tempy = cy, tempx = cx;
    int ln = market->size();
    int numCard = 49;
    for(int i = 0; i < ln; i++)
      {
        wattron(win, COLOR_PAIR(4));
        drawCard(tempx, tempy, len);
        int j = 0;
        int lon = (*market)[i].returnType().length();
        string mcard = (*market)[i].returnType();
        wattroff(win, COLOR_PAIR(4));
        while(j <= 7 && j<lon)
        {
            wattron(win, A_BOLD);
            wmove(win, tempx+1, tempy+5);
            ////
            if(j==0) {
                wmove(win, tempx+1, tempy+2);
                wattron(win, COLOR_PAIR(3));
                char c = numCard++;
                waddch(win, c);
                tempx++;
                wattroff(win, COLOR_PAIR(3));
                wmove(win, tempx+1, tempy+5);
            }
            ////
            wattron(win, COLOR_PAIR(5));
            waddch(win, mcard[j]);
            j++;
            tempx++;
            wattroff(win, COLOR_PAIR(5));
        }
        wrefresh(win);
        tempx = cx;
        tempy+= 12;
      }
}

void UI::drawAllTokens(Token tokens)
{
    drawTokens(tokens.getTok());
    drawBonusTok(tokens.getBonTok());
}

void UI::assignColor(string type)
{
    start_color();
    if(type.compare("Diamond") == 0){init_pair(8, COLOR_RED, COLOR_BLACK);}
    if(type.compare("Gold")== 0){init_pair(9, COLOR_YELLOW, COLOR_BLACK);}
    if(type.compare("Silver")== 0){init_pair(11, COLOR_CYAN, COLOR_BLUE);}
    if(type.compare("Cloth")== 0){init_pair(7, COLOR_MAGENTA, COLOR_BLACK);}
    if(type.compare("Spice")== 0){init_pair(12, COLOR_GREEN, COLOR_BLACK);}
    if(type.compare("Leather")== 0){init_pair(10, COLOR_BLUE, COLOR_BLACK);}

}

void UI::drawTok(int i, int x, int y, char val)
{
    wattron(win, COLOR_PAIR(i + 6));
    mvwprintw(win, x, y, "*-*");
    mvwvline(win, x+1, y, '|', 2);
    mvwvline(win,x+1, y+2, '|', 2);
    mvwprintw(win, x+2, y, "*-*");

    wattroff(win, COLOR_PAIR(i + 6));
    wmove(win, x+1, y+1);
    waddch(win, val);

    wrefresh(win);
}

void UI::drawTokens(map<string, vector<int> > tokens)
{
    int tx = cx-10, ty = p1y+28;
    int tempx = tx, tempy = ty;
    int x = 1;
    for(auto it = tokens.begin(); it != tokens.end(); it++)
    {
        string type = it->first;
        assignColor(type);
        wattron(win, COLOR_PAIR(x+6));
        mvwprintw(win, tempx, tempy, type.c_str());
        tempx++;
        wrefresh(win);
        vector<int> &v = it->second;
        if(v.size() <= 0) {drawTok(x, tempx, tempy, (0+'0'));}
        else{
            for(unsigned int i = 0; i < v.size(); i++)
            {
                drawTok(x, tempx, tempy, (v[i]+'0'));
                tempy += 4;
            }
        }
        wrefresh(win);
        tempx += 4;
        tempy = ty;
        x++;
    }
}

void UI::drawBonusTok(map<string, vector<int> > bonus)
{
    int tx = p2x+10, ty = p1y+28;
    int tempx = tx, tempy = ty;
    mvwprintw(win, tempx-1, tempy, "BONUS TOKENS");
    int i = 7;
    for(auto it = bonus.begin(); it != bonus.end(); it++)
    {
        start_color();
        init_pair(13, COLOR_WHITE, COLOR_BLACK);
        wattron(win, COLOR_PAIR(i+6));
        vector<int> &v = it->second;
        if(v.size() <= 0) {drawTok(i, tempx, tempy, '-');}
        else{
        drawTok(i, tempx, tempy, '?');
        }
        wrefresh(win);
        tempx = tx;
        tempy += 4;
    }

    wattroff(win, COLOR_PAIR(6));
}

void UI:: drawCard(int x, int y, int z)
{;
    mvwprintw(win, x, y, "*---------*");

    wmove(win, x+1, y);
    mvwvline(win, x+1, y, '|', z);
    wmove(win, x+1, y+10);
    mvwvline(win, x+1, y+10, '|', z);
    touchwin(win);
    mvwprintw(win, x+z, y, "*---------*");
    wrefresh(win);
}

void UI::permBoard()
{
    mvwprintw(win, p1x+2, p1y+15, "*---------*");
    mvwvline(win, p1x+3, p1y+15, '|', 4);
    mvwvline(win, p1x+3, p1y + 25, '|', 4);
    mvwprintw(win, p1x+6, p1y+15, "*---------*");
    mvwprintw(win, p1x+4, p1y+18, "HERD");

    mvwprintw(win, p1x+13, p1y+12, "*------------*");
    mvwvline(win, p1x+14, p1y+12, '|', 5);
    mvwvline(win, p1x+14, p1y + 25, '|', 5);
    mvwprintw(win, p1x+19, p1y+12, "*------------*");
    mvwprintw(win, p1x+16, p1y+15, "DISCARD");

    mvwprintw(win, p2x+2, p1y+15, "*---------*");
    mvwvline(win,p2x+3, p1y+15, '|', 4);
    mvwvline(win, p2x+3, p1y+25, '|', 4);
    mvwprintw(win, p2x+6, p1y+15, "*---------*");
    mvwprintw(win, p2x+4, p1y+18, "HERD");
}

void UI::setBoard()
{
    mvwprintw(win, 0,0, "Game 1");
    drawHand(1);
    drawHand(2);
}

void UI::printMessage(string mess)
{
    wclear(sub);
    mvwprintw(sub, 2, 2, mess.c_str());
    wrefresh(sub);
    touchwin(win);
    getchar();
}


void UI::clearBoard()
{
  mvwprintw(win, 70, 2, "Press any key to continue... ");
  getchar();
  wclear(win);
  wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
  wmove(win, 70, 0);
}


void UI::printPlayer(Player * p1, Player * p2)
{
    int x = getmaxx(win);
    int y = getmaxy(win);
    sub = derwin(win, y*(.4), x*(.20), 0, 0);
    wborder(sub, '|', '|', '-', '-', '*', '*', '*', '*' );
    wrefresh(sub);
    touchwin(win);

    mvwprintw(sub, 2, 2, "%s Stats", p1->getName().c_str());
    mvwprintw(sub, 4, 2, "Points: %d", p1->getPoints());
    mvwprintw(sub, 5, 2, "Seals: %d", p1->sealCount());
    mvwprintw(sub, 6, 2, "Hand Size: %d", p1->getHand()->size());
    mvwprintw(sub, 7, 2, "Herd Size: %d", p1->getHerd()->size());

    mvwprintw(sub, 9, 2, "%s Stats", p2->getName().c_str());
    mvwprintw(sub, 11, 2, "Points: %d", p2->getPoints());
    mvwprintw(sub, 12, 2, "Seals: %d", p2->sealCount());
    mvwprintw(sub, 13, 2, "Hand Size: %d", p2->getHand()->size());
    mvwprintw(sub, 14, 2, "Herd Size: %d", p2->getHerd()->size());

    wrefresh(sub);
    touchwin(win);
}

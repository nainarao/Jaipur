#include <iostream>
#include <assert.h>
#include "Game.h"
#include "UI.h"
#include "Deck.h"
#include "Market.h"
#include "Token.h"
#include "Player.h"
#include "Human.h"
#include "Computer.h"

int main()
{
    initscr();

    raw();
    echo();

    attron(A_BOLD);
    printw("\nDevelopers of this adapted game: \n Matt Kosarek \n Naina Rao \n Hannah Kim \n Marshall\n");
    attroff(A_BOLD);
    printw(" Press the space bar to continue to ");
    attron(A_UNDERLINE);
    attron(A_BOLD);
    attron(A_STANDOUT);
    attroff(A_BLINK);
    printw("JAIPUR!!\n");
    attroff(A_UNDERLINE);
    attroff(A_BOLD);
    attroff(A_BLINK);
    attroff(A_STANDOUT);
    printw("*Cue music and applause*\n");
    wrefresh(stdscr);
    Game game;

    endwin();
    getchar();
    cout<<"THANKS FOR PLAYING"<<endl;
    cout<<"***Disclaimer***"<<endl;
    cout<<"THE RUPEE IS CURRENTLY WORTH .02 DOLLARS. BEING GOOD AT THIS GAME DOES NOT MEAN YOU WILL BE RICH"<<endl;
    cout<<"IN FACT YOU'LL ACTUALLY STILL BE REALLY POOR"<<endl;

}

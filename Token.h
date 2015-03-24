
#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

using std::ostream;
using std::vector;
using std::string;
using std::cout;
using std::endl;
using std:: map;

const string cloth = "Cloth";
const string spice = "Spice";
const string leather = "Leather";
const string silver = "Silver";
const string gold = "Gold";
const string diamond = "Diamond";

const string bonus3 = "Bonus Token (3)";
const string bonus4 = "Bonus Token (4)";
const string bonus5 = "Bonus Token (5+)";

typedef std::string type;
typedef std::vector<int> vals;

class Token{
private:
    map<type, vals> tokens;
    map<type, vals> bonusTok;

public:
    //Constructor
    Token();
    Token(int v, string t); //initializes Token value and type
    void printTok(int x); // prints what tokens are in the game
    void printBonusTok(int x); // prints what bonus tokens are left
    void fillTokens(); // works with constructor. Creates all normal tokens
    void deleteTokens();
    void fillbonusTok(); // works with constructor. Creates bonus tokens and shuffles them
    void deleteBonusToks();
    void deleteAllToks();
    string getGoods(int); //gets string of type of card being sold
    int tokenPoints(unsigned int numcards, string goods); // adds up points gained from normal tokens
    int bonusPoints(int numCards); // calculates any points from bonus tokens
    string getBonusTok(int numCards); //
    int getEmptyTok();
    bool isEmpty(int card);
    int salePoints(int numCards, int card);
    const map<type, vals> & getTok()const {return tokens;}
    const map<type, vals> & getBonTok()const {return bonusTok;}


    //friend ostream& operator<<(ostream& os, const Card& cd);
};

#endif // TOKEN_H

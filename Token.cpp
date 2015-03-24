#include <string>
#include <algorithm>
#include <cstring>
#include "Token.h"
#include <iostream>
#include <ostream>
#include <vector>
#include <map>
#include <algorithm>
#include <list>
#include <cstdlib>
#include <cstdio>


using std::string;
using std::vector;
using std::endl;
using std::cout;
using std::pair;

// Member functions definitions including constructor
Token::Token()
{

}

void Token::printTok(int x)
{
    auto it = tokens.begin();
    for (int i = 0; i < x; i++)
    {
        it++;
    }
    cout<<it->first<< ": ";
    for(auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
    {
        cout<<*it2<<" ";
    }
}

void Token::printBonusTok(int x)
{
    auto it = bonusTok.begin();
    for (int i = 0; i < x; i++)
    {
        it ++;
    }
    cout<<it->first<< " ";
}

void Token::fillTokens()
{
    vector<int> gol = {6, 6, 5, 5, 5};
    tokens.insert(pair<type,vals>(gold, gol));

    vector<int> sil (5, 5);
    tokens.insert(pair<type,vals>(silver, sil));

    vector<int> cloths = {5, 3, 3, 2, 2, 1, 1};
    tokens.insert(pair<type,vals>(cloth, cloths));

    vector<int> lea = {4, 3, 2, 1, 1, 1, 1, 1, 1};
    tokens.insert(pair<type,vals>(leather, lea));

    vector<int> spices = {5, 3, 3, 2, 2, 1, 1};
    tokens.insert(pair<type,vals>(spice, spices));

    vector<int> dia = {7, 7, 5, 5, 5};
    tokens.insert(pair<type,vals>(diamond, dia));
}

void Token::deleteAllToks()
{
    deleteTokens();
    deleteBonusToks();
}

void Token::deleteTokens()
{
    tokens.erase(tokens.begin(), tokens.end());
}

void Token::deleteBonusToks()
{
    bonusTok.erase(bonusTok.begin(), bonusTok.end());
}

void Token::fillbonusTok()
{
    vector<int> cards3 = {1, 1, 2, 2, 3, 3};
    random_shuffle(cards3.begin(), cards3.end());
    bonusTok.insert(pair<type, vals>(bonus3, cards3));

    vector<int> cards4 = {4, 4 , 5, 5, 6, 6};
    random_shuffle(cards4.begin(), cards4.end());
    bonusTok.insert(pair<type, vals>(bonus4, cards4));

    vector<int> cards5 = {8, 8, 9, 9, 10, 10};
    random_shuffle(cards5.begin(), cards5.end());
    bonusTok.insert(pair<type, vals>(bonus5, cards5));
}

int Token::getEmptyTok()
{
    int emptyTok = 0;

    for(auto it = tokens.begin(); it!=tokens.end(); it++)
    {
        vector<int> &v = it->second;
        if(v.size() == 0)
        {
            emptyTok++;
        }
    }
    return emptyTok;
}

bool Token::isEmpty(int card)
{
    string goods = getGoods(card);
    auto it = tokens.find(goods);
    if(it != tokens.end())
    {
        vector<int> &v = it->second;
        if (v.size() == 0)
            return true;
    }

    return false;
}

int Token::salePoints(int numCards, int card)
{
    int points = 0;
    unsigned int numcards = numCards;
    string goods = getGoods(card);

    //cout<<"Goods: "<<goods<<endl;
    points += tokenPoints(numcards, goods) + bonusPoints(numCards);

    //cout<<"Points: "<< points<<endl;
    return points;
}

int Token::bonusPoints(int numCards)
{
    int points = 0;
    string bonus;

    if(numCards < 3){
        return points;
    }
    else{
        bonus = getBonusTok(numCards);
    }

    auto it = bonusTok.find(bonus);
    if(it != bonusTok.end())
    {
        vector<int> &v = it->second;
        if(v.size() == 0) {return 0;}
        points += v.at(0);
        v.erase(v.begin());
    }
    return points;

}

string Token::getBonusTok(int numCards)
{
    string bonus;
    if(numCards == 3)
        bonus = bonus3;
    if(numCards == 4)
        bonus =  bonus4;
    if(numCards >= 5)
        bonus = bonus5;

    return bonus;
}

int Token::tokenPoints(unsigned int numcards, string goods)
{
    int points = 0;
    auto it = tokens.find(goods);
    if(it != tokens.end())
    {
        vector<int> &v = it->second;
        if(v.size() < numcards)
        {
            numcards = (unsigned int)v.size();
        }
        for(unsigned int i = 0; i < numcards; i++)
        {
            points += v.at(0);
            v.erase(v.begin());
        }
    }
    return points;
}

string Token::getGoods(int card)
{
    string goods;
    switch(card){
        case 2: goods = leather; break;
        case 3: goods = spice; break;
        case 4: goods = cloth; break;
        case 5: goods = silver; break;
        case 6: goods = gold; break;
        case 7: goods = diamond; break;
    }
    return goods;
}

/*
 Card::Card(string suit, int num): suits(suit), faceval(num)
 {
 if(strcasecmp(suits.c_str(), tri.c_str()) == 0){
 suitnum = 0;
 suits = tri;
 }
 else if(strcasecmp(suits.c_str(), squ.c_str()) == 0){
 suitnum = 1;
 suits = squ;
 }
 else if(strcasecmp(suits.c_str(), diam.c_str()) == 0){
 suitnum = 2;
 suits = diam;
 }
 else if(strcasecmp(suits.c_str(), circ.c_str()) == 0)
 {
 suitnum = 3;
 suits = circ;
 }
 else{
 suits = "no suit";
 suitnum = -1;
 }
 if(!(faceval >= 1 && faceval <= 15)){
 faceval = 0;
 }
 }

 std::string Card::getSuit()const
 {
 return suits;
 }

 int Card::Rank(void) const
 {
 int rankc;
 if(suitnum >= 0 && faceval > 0){
 rankc= (suitnum * 15) + faceval;
 return rankc;
 }
 else{
 rankc = 0;
 return rankc;
 }
 }

 int Card::getSuitNum()const
 {
 return suitnum;
 }

 int Card::getFace()const
 {
 return faceval;
 }

 Card::Card(const Card& other)
 {
 suitnum = other.suitnum;
 suits = other.suits;
 faceval = other.faceval;
 }

 ostream& operator<<(ostream& os, const Card& dt)
 {
 os<<"#"<< dt.Rank()<<",";
 return os;
 }

 bool Card:: operator< (const Card & other) const{
 return this->Rank() < other.Rank();

 }

 bool Card:: operator> (const Card & other) const{
 return this->Rank() > other.Rank();

 }

 bool Card:: operator<= (const Card & other) const{
 return this->Rank() <= other.Rank();

 }

 bool Card:: operator >= (const Card & other) const{
 return this->Rank() >= other.Rank();

 }

 bool Card::operator==(const Card & other) const{
 return this->Rank() == other.Rank();
 }

 */

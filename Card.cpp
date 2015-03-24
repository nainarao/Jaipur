

#include "Card.h"

Card::Card()
{
    typeNum = 0;
    type = "NULL";
}

Card::Card(int t)
{
    switch (t) {
        case 1:
            typeNum = t;
            type = (const string) "Camel";
            break;
        case 2:
            typeNum = t;
            type = "Leather";
            break;
        case 3:
            typeNum = t;
            type = "Spice";
            break;
        case 4:
            typeNum = t;
            type = "Cloth";
            break;
        case 5:
            typeNum = t;
            type = "Silver";
            break;
        case 6:
            typeNum = t;
            type = "Gold";
            break;
        case 7:
            typeNum = t;
            type = "Diamond";
            break;
        default:
            typeNum = -1;
            type = "Invalid";
            break;
    }
}

Card::Card(string x)
{
    if (x == "Camel")
    {
        type = x;
        typeNum = 1;
    }
    else if (x == "Leather")
    {
        type = x;
        typeNum = 2;
    }
    else if (x == "Spice")
    {
        type = x;
        typeNum = 3;
    }
    else if (x == "Cloth")
    {
        type = x;
        typeNum = 4;
    }
    else if (x == "Silver")
    {
        type = x;
        typeNum = 5;
    }
    else if (x == "Gold")
    {
        type = x;
        typeNum = 6;
    }
    else if (x == "Diamond")
    {
        type = x;
        typeNum = 7;
    }
    else
    {
        type = "Invalid";
        typeNum = -1;
    }
}

const string Card:: returnType()
{
    return type;
}

bool Card:: isValuable()
{
    bool ans = false;
    if (this->returnTypeNum() == 5 || this->returnTypeNum() == 6 || this->returnTypeNum() == 7)
    {
        ans = true;
    }
    else
    {
        ans = false;
    }

    return ans;
}



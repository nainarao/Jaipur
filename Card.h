//
//  Card.h
//  IntermediateProject
//
//  Created by Matthew Kosarek on 11/23/14.
//  Copyright (c) 2014 Matthew Kosarek. All rights reserved.
//

#ifndef __IntermediateProject__Card__
#define __IntermediateProject__Card__

#include <stdio.h>
#include <cstdlib>
#include <string>

using namespace std;

class Card
{
private:
    string type;
    int typeNum;
public:
    Card();
    Card(int t);
    Card(string x);
    const string returnType();
    int returnTypeNum() const {return typeNum; };
    bool isValuable();
};

#endif /* defined(__IntermediateProject__Card__) */

//
//  Playcard.hpp
//  Spiderharpan
//
//  Created by Per Nyberg on 2018-03-06.
//  Copyright © 2018 Per Nyberg. All rights reserved.
//

#ifndef Playcard_hpp
#define Playcard_hpp

#include <iostream>
#include <stdio.h>
#include <string>

#include "Cardcolor.cpp"

using namespace std;

class Playcard {
    int value;
    Cardcolor color;
public:
    Playcard(int value, Cardcolor color);
    
    int getValue();
    
    Cardcolor getColor();
    
    string toString();
};
#endif /* Playcard_hpp */

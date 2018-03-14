//
//  Cardstack.hpp
//  Spiderharpan
//
//  Created by Per Nyberg on 2018-03-07.
//  Copyright © 2018 Per Nyberg. All rights reserved.
//

#ifndef Cardstack_hpp
#define Cardstack_hpp

#include "Playcard.hpp"
#include <stdio.h>
#include <stack>
#include <vector>

using namespace std;

class Cardstack {
    stack<Playcard> hiddenCards;
    vector<Playcard> visibleCards;
public:
    Cardstack();
    
    void addHiddenCard(Playcard card);
    
    void addVisibleCard(Playcard card);
    
    Playcard getHiddenCardTop();
    
    Playcard removeHiddenCardTop();
    
    Playcard getVisibleCardTop();
    
    Playcard getVisibleCard(int index);
    
    Playcard removeVisibleCard(int index);
    
    void clear();
    
    int hiddenCardsSize();
    
    int visibleCardsSize();
};

#endif /* Cardstack_hpp */

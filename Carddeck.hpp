//
//  Carddeck.h
//  Spiderharpan
//
//  Created by Per Nyberg on 2018-03-07.
//  Copyright © 2018 Per Nyberg. All rights reserved.
//

#ifndef Carddeck_h
#define Carddeck_h

#include <algorithm>
#include <random>
#include <vector>
#include "Playcard.hpp"
#include "Cardcolor.hpp"
#include "Cardvalues.cpp"

using namespace std;

class Carddeck {
    vector<Playcard> deck;
    
public:
    Carddeck();
    
    /**
     * Sets a new random shuffle-seed
     */
    void resetShuffleSeed();
    
    /**
     * Fills the deck with 52 play-cards, a "normal" deck
     */
    void fillNormalDeck();
    
    /**
     * Fill the deck with one color, 13 play-cards
     */
    void fillDeckWithOneColor(Cardcolor color);

    /**
     * Moves the cards around in the "deck"
     */
    void shuffle();
    
    /**
     * Removes the top card of the "deck" and returns it
     */
    Playcard drawCard();
    
    /**
     * Empties the deck
     */
    void empty();
    
    /**
     * Returns the number of cards in the deck
     */
    int size();
};

#endif /* Carddeck_h */

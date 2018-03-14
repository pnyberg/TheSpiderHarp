//
//  Carddeck.cpp
//  Spiderharpan
//
//  Created by Per Nyberg on 2018-03-06.
//  Copyright © 2018 Per Nyberg. All rights reserved.
//

#include "Carddeck.hpp"


Carddeck::Carddeck() {
}

/**
 * Fills the deck with 52 play-cards, a "normal" deck
 */
void Carddeck::fillNormalDeck() {
    fillDeckWithOneColor(Cardcolor::HEART);
    fillDeckWithOneColor(Cardcolor::SPADE);
    fillDeckWithOneColor(Cardcolor::DIAMOND);
    fillDeckWithOneColor(Cardcolor::CLUB);
}

void Carddeck::fillDeckWithOneColor(Cardcolor color) {
    for (int k = 1 ; k <= 13 ; k++) {
        if (k == 1) {
            deck.push_back(Playcard{int(Cardvalues::ACE), color});
        } else if (k == 11) {
            deck.push_back(Playcard{int(Cardvalues::KNIGHT), color});
        } else if (k == 12) {
            deck.push_back(Playcard{int(Cardvalues::QUEEN), color});
        } else if (k == 13) {
            deck.push_back(Playcard{int(Cardvalues::KING), color});
        } else {
            deck.push_back(Playcard{k, color});
        }
    }
}

/**
 * Moves the cards around in the "deck"
 */
void Carddeck::shuffle() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    auto rng = default_random_engine {seed};
    ::shuffle(deck.begin(), deck.end(), rng);
}
    
/**
 * Removes the top card of the "deck" and returns it
 */
Playcard Carddeck::drawCard() {
    Playcard topCard = deck.at(0);
    deck.erase(deck.begin(), deck.begin()+1);
    return topCard;
}

void Carddeck::empty() {
    deck.clear();
}
    
int Carddeck::size() {
    return int(deck.size());
}

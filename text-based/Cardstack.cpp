//
//  Cardstack.cpp
//  Spiderharpan
//
//  Created by Per Nyberg on 2018-03-07.
//  Copyright © 2018 Per Nyberg. All rights reserved.
//

#include "Cardstack.hpp"

using namespace std;

Cardstack::Cardstack() {
    //hiddenCards = *new stack<Playcard>;
    //visibleCards = *new vector<Playcard>;
}

void Cardstack::addHiddenCard(Playcard card) {
    hiddenCards.push(card);
}

void Cardstack::addVisibleCard(Playcard card) {
    visibleCards.push_back(card);
}

Playcard Cardstack::getHiddenCardTop() {
    return hiddenCards.top();
}

Playcard Cardstack::removeHiddenCardTop() {
    Playcard top = getHiddenCardTop();
    hiddenCards.pop();
    return top;
}

Playcard Cardstack::getVisibleCardTop() {
    return visibleCards.at(int(visibleCards.size()) - 1);
}

Playcard Cardstack::getVisibleCard(int index) {
    return visibleCards.at(index);
}

Playcard Cardstack::removeVisibleCard(int index) {
    Playcard card = visibleCards.at(index);
    visibleCards.erase(visibleCards.begin()+index, visibleCards.begin()+index+1);
    return card;
}

void Cardstack::clear() {
    while(hiddenCards.size() > 0) {
        hiddenCards.pop();
    }
    visibleCards.clear();
}

int Cardstack::hiddenCardsSize() {
    return int(hiddenCards.size());
}

int Cardstack::visibleCardsSize() {
    return int(visibleCards.size());
}

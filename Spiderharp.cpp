//
//  Spiderharp.cpp
//  Spiderharpan
//
//  Created by Per Nyberg on 2018-03-07.
//  Copyright © 2018 Per Nyberg. All rights reserved.
//

#include "Spiderharp.hpp"

int numberOfStacks = 10;

Spiderharp::Spiderharp(int mode) {
    stacks = new Cardstack*[numberOfStacks];
    deck = new Carddeck();
    
    for (int i = 0 ; i < numberOfStacks ; i++) {
        stacks[i] = new Cardstack();
    }
    
    initGame(mode);
}

/**
 * Init game-methods
 */
void Spiderharp::initGame(int mode) {
    deck->empty();
    for (int i = 0 ; i < numberOfStacks ; i++) {
        stacks[i]->clear();
    }
    
    if (mode == 1) {
        initOneColorGame();
    } else if (mode == 2) {
        initTwoColorGame();
    } else if (mode == 3) {
        initFourColorGame();
    } else {
        cerr << "Mode number " << mode << " doesn't exists!" << endl;
        return;
    }
    
    deck->shuffle();
    fillStacks();
    
    flipUpTopCards();
}

void Spiderharp::initOneColorGame() {
    for (int i = 0 ; i < 8 ; i++) {
        deck->fillDeckWithOneColor(Cardcolor::SPADE);
    }
}

void Spiderharp::initTwoColorGame() {
    for (int i = 0 ; i < 4 ; i++) {
        deck->fillDeckWithOneColor(Cardcolor::SPADE);
        deck->fillDeckWithOneColor(Cardcolor::DIAMOND);
    }
}

void Spiderharp::initFourColorGame() {
    deck->fillNormalDeck();
    deck->fillNormalDeck();
}

void Spiderharp::fillStacks() {
    for (int k = 0 ; k < 5 ; k++) {
        for (int i = 0 ; i < numberOfStacks ; i++) {
            stacks[i]->addHiddenCard(deck->drawCard());
        }
    }
    for (int i = 0 ; i < 4 ; i++) {
        stacks[i]->addHiddenCard(deck->drawCard());
    }
}

void Spiderharp::flipUpTopCard(int index) {
    Playcard card = stacks[index]->removeHiddenCardTop();
    stacks[index]->addVisibleCard(card);
}

void Spiderharp::flipUpTopCards() {
    for (int i = 0 ; i < numberOfStacks ; i++) {
        flipUpTopCard(i);
    }
}

/**
 * Mutator-methods
 */
void Spiderharp::addNewRound() {
    for (int i = 0 ; i < numberOfStacks ; i++) {
        stacks[i]->addVisibleCard(deck->drawCard());
    }
}

void Spiderharp::moveCards(int from, int to, int amount) {
    int removeIndex = stacks[from]->visibleCardsSize() - amount;
    for (int k = 0; k < amount ; k++) {
        stacks[to]->addVisibleCard(stacks[from]->removeVisibleCard(removeIndex));
    }
    
    if (stacks[from]->visibleCardsSize() == 0) {
        if (stacks[from]->hiddenCardsSize() == 0) {
            // leave slot empty @TODO
        } else {
            flipUpTopCard(from);
        }
    }
}

// what happens if the strait is the last cards in the stack -> leaving it empty? @TODO 
void Spiderharp::removePossibleStraits() {
    for (int i = 0 ; i < numberOfStacks ; i++) {
        int stackSize = stacks[i]->visibleCardsSize();
        if (stackSize >= 13) {
            Cardcolor color = stacks[i]->getVisibleCardTop().getColor();
            bool removeCards = true;
            for (int k = 1 ; k <= 13 ; k++) {
                if (stacks[i]->getVisibleCard(stackSize - k).getColor() != color) {
                    removeCards = false;
                    break;
                }
                if (stacks[i]->getVisibleCard(stackSize - k).getValue() != k) {
                    removeCards = false;
                    break;
                }
            }
            
            if (removeCards) {
                cout << "Removing strait from stack #" << i << endl;
                for (int j = 1 ; j <= 13 ; j++) {
                    stacks[i]->removeVisibleCard(stackSize - j);
                }
            }
        }
    }
}

/**
 * Show-methods
 */
void Spiderharp::printStacks() {
    int highestStack = -1;
    
    for (int i = 0 ; i < numberOfStacks ; i++) {
        if (highestStack < stacks[i]->hiddenCardsSize() + stacks[i]->visibleCardsSize()) {
            highestStack = stacks[i]->hiddenCardsSize() + stacks[i]->visibleCardsSize();
        }
    }
    
    for (int k = 1 ; k <= highestStack ; k++) {
        for (int i = 0 ; i < numberOfStacks ; i++) {
            if (stacks[i]->hiddenCardsSize() >= k) {
                cout << "XXX ";
            } else if(stacks[i]->visibleCardsSize() >= k - stacks[i]->hiddenCardsSize()) {
                if (stacks[i]->getVisibleCard((k - stacks[i]->hiddenCardsSize() - 1)).getValue() != 10) {
                    cout << " ";
                }
                cout << stacks[i]->getVisibleCard((k - stacks[i]->hiddenCardsSize() - 1)).toString() << " ";
            } else {
                cout << "--- ";
            }
        }
        cout << endl;
    }
}

/**
 * Check-methods
 */
bool Spiderharp::hasNewRound() {
    return deck->size() > 0;
}

bool Spiderharp::canAddNewRound() {
    for (int i = 0 ; i < numberOfStacks ; i++) {
        if (stacks[i]->hiddenCardsSize() + stacks[i]->visibleCardsSize() == 0) {
            return false;
        }
    }
    
    return true;
}

bool Spiderharp::checkIfCardsCanBeMoved(int from, int to, int amount) {
    if (amount > stacks[from]->visibleCardsSize()) {
        return false;
    }
    
    int colorIndex = stacks[from]->visibleCardsSize() - amount;
    Cardcolor color = stacks[from]->getVisibleCard(colorIndex).getColor();
    int value = stacks[from]->getVisibleCard(colorIndex).getValue();
    
    if (stacks[to]->visibleCardsSize() > 0 && stacks[to]->getVisibleCardTop().getValue() != value + 1) {
        return false;
    }
    
    for (int k = 1; k < amount ; k++) {
        if (stacks[from]->getVisibleCard(colorIndex+k).getColor() != color) {
            return false;
        }
        if (stacks[from]->getVisibleCard(colorIndex+k).getValue() != value-k) {
            return false;
        }
    }

    return true;
}

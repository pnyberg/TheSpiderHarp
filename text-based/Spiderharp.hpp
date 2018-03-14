//
//  Spiderharp.hpp
//  Spiderharpan
//
//  Created by Per Nyberg on 2018-03-07.
//  Copyright © 2018 Per Nyberg. All rights reserved.
//

#ifndef Spiderharp_hpp
#define Spiderharp_hpp

#include <stdio.h>
#include "Cardstack.hpp"
#include "Carddeck.hpp"

class Spiderharp {
    Cardstack** stacks;
    Carddeck* deck;
public:
    /**
     * Create the "deck" with
     */
    Spiderharp(int mode);
    
    /*******************************
     * Init game-methods
     *******************************/
    /**
     * Init the game
     */
    void initGame(int mode);
    
    /**
     * Game with only Spade
     */
    void initOneColorGame();

    /**
     * Game with Spade and Diamond
     */
    void initTwoColorGame();

    /**
     * Game with all four colors
     */
    void initFourColorGame();
    
    /**
     * Fill the ten stacks with 54 cards (four stacks of 6 and six stacks of 5)
     */
    void fillStacks();
    
    /**
     * "Flip" the top card of stack with index "index"
     */
    void flipUpTopCard(int index);

    /**
     * "Flip" all the top cards, that is, move top card from hidden to visible
     */
    void flipUpTopCards();
    
    /*******************************
     * Mutator-methods
     *******************************/
    /**
     * Add one open card to every stack
     */
    void addNewRound();
    
    /**
     * Move a certain amount of cards from "from" to "to"
     */
    void moveCards(int from, int to, int amount);
    
    /**
     * Check (and remove) cards if they are a strait
     */
    void removePossibleStraits();
    
    /*******************************
     * Show-methods
     *******************************/
    /**
     * Print the top cards of the stacks (10 stacks)s
     */
    void printStacks();
    
    /*******************************
     * Check-methods
     *******************************/
    /**
     * Whether or not the Spiderharp can add a new layer of cards
     */
    bool hasNewRound();
    
    /**
     * If all the slots have at least one card then a new layer may be added (if not cards have to be moved)
     */
    bool canAddNewRound();
    
    /**
     * Check if the given amount of cards can be moved from "from" to "to"
     */
    bool checkIfCardsCanBeMoved(int from, int to, int amount);
};

#endif /* Spiderharp_hpp */

//
//  main.cpp
//  Spiderharpan
//
//  Created by Per Nyberg on 2018-03-06.
//  Copyright © 2018 Per Nyberg. All rights reserved.
//

#include <iostream>
#include <regex>
#include <sstream>
#include <string>

#include "Carddeck.hpp"
#include "Cardstack.hpp"
#include "Playcard.hpp"
#include "Spiderharp.hpp"

using namespace std;

const string printCommand = "print";
const string moveCommand = "move [amount] from [index] to [index]";
const string newRoundCommand = "new round";
const string newGameCommand = "new game";
const string quitCommand = "quit";

int* handleMoveCommand(string text) {
    istringstream stringStream(text);
    
    int amount = -1;
    int from = -1;
    int to = -1;
    
    string token;
    stringStream >> token; // matches move
    
    stringStream >> token;
    amount = stoi(token);
    
    stringStream >> token; // matches from
    
    stringStream >> token;
    from = stoi(token);
    
    stringStream >> token; // matches to
    
    stringStream >> token;
    to = stoi(token);
    
    int* attributes = new int[3];
    attributes[0] = from;
    attributes[1] = to;
    attributes[2] = amount;
    return attributes;
}

void handleCommand(Spiderharp* harp, string text) {
    bool commandDone = false;

    if (!text.compare("print")) {
        harp->printStacks();
        cout << endl;
        commandDone = true;
    }
    
    regex moveRegex("move [[:digit:]]+ from [[:digit:]] to [[:digit:]]");
    // Using algorithm for splitting string found on:
    // https://stackoverflow.com/questions/236129/the-most-elegant-way-to-iterate-the-words-of-a-string
    if (regex_match(text, moveRegex)) {
        int* commandOptions = handleMoveCommand(text);
        int from = commandOptions[0];
        int to = commandOptions[1];
        int amount = commandOptions[2];
        if(harp->checkIfCardsCanBeMoved(from, to, amount)) {
            harp->moveCards(from, to, amount);
            cout << "Moved " << amount << " card(s) from index " << from << " to index " << to << "!" << endl << endl;
            harp->removePossibleStraits();
        } else {
            cout << "You cannot make that move!" << endl << endl;
        }
        harp->printStacks();
        cout << endl;
        commandDone = true;
    }
    
    if (!text.compare(newRoundCommand) && harp->hasNewRound()) {
        if (harp->canAddNewRound()) {
            harp->addNewRound();
            harp->removePossibleStraits();
            harp->printStacks();
            cout << endl;
        } else {
            cout << "You cannot add a new round with empty slots!" << endl << endl;
        }
        commandDone = true;
    }
    
    if (!text.compare(newGameCommand)) {
        harp->initGame(3);
        harp->printStacks();
        cout << endl;
        commandDone = true;
    }
    
    if (!text.compare(quitCommand)) {
        cout << "Quitting, good bye!" << endl << endl;
        exit(0);
    }
    
    if (!commandDone) {
        cout << "Couldn't match that input to an existing command!" << endl << endl;
    }
}

int main(int argc, const char * argv[]) {
    Spiderharp* harp = new Spiderharp(3);
    string text = "";
    
    harp->printStacks();
    cout << endl;

    while(true) {
        cout << "Menu:" << endl;
        cout << "- Print the harp [\"" + printCommand + "\"]" << endl;
        cout << "- Move cards [\"" + moveCommand + "\"]" << endl;
        if (harp->hasNewRound()) {
            cout << "- Add new round [\"" + newRoundCommand + "\"]" << endl;
        }
        cout << "- Init new game [\"" + newGameCommand + "\"]" << endl;
        cout << "- Quit [\"" + quitCommand + "\"]" << endl;
        cout << endl;
        cout << "Input:" << endl << "> ";
        getline(cin, text);
        
        cout << endl;
        handleCommand(harp, text);
    }
    
    return 0;
}

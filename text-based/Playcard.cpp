//
//  Playcard.cpp
//  Spiderharpan
//
//  Created by Per Nyberg on 2018-03-06.
//  Copyright © 2018 Per Nyberg. All rights reserved.
//
#include "Playcard.hpp"
#include "Cardvalues.cpp"

Playcard::Playcard(int value, Cardcolor color) {
    this->value = value;
    this->color = color;
}
    
int Playcard::getValue() {
    return this->value;
}

Cardcolor Playcard::getColor() {
    return this->color;
}

string Playcard::toString() {
    string text = "";
    text += (color == Cardcolor::HEART ? "♥" : (color == Cardcolor::SPADE ? "♠" : (color == Cardcolor::DIAMOND ? "♦" : "♣")));
    if (value == int(Cardvalues::ACE) || value == int(Cardvalues::KNIGHT) || value == int(Cardvalues::QUEEN) || value == int(Cardvalues::KING)) {
        text += (value == int(Cardvalues::ACE) ? "A" : (value == int(Cardvalues::KNIGHT) ? "J" : (value == int(Cardvalues::QUEEN) ? "Q" : "K")));
    } else {
        text += to_string(value);
    }
    return text;
}

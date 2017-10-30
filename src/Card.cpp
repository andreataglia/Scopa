//
// Created by Matteo Sinico on 30/10/17.
//

#include "Card.h"

Card::Card(seed _seed, int _value) {
    seed seed = _seed;
    value = _value;
}

void Card::setValue(int value) {
    Card::value = value;
}

int Card::getValue() const {
    return value;
}




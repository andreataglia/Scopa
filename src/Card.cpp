//
// Created by Matteo Sinico on 30/10/17.
//

#include "Card.h"

Card::Card(Seed _seed, int _value) {
    Seed seed = _seed;
    value = _value;
}

void Card::setValue(int value) {
    Card::value = value;
}

int Card::getValue() const {
    return value;
}

Card::Seed Card::getSeed() const {
    return seed;
}

void Card::setSeed(Card::Seed seed) {
    Card::seed = seed;
}




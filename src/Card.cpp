//
// Created by Matteo Sinico on 30/10/17.
//

#include "Card.h"
#include <iostream>
using namespace std;

Card::Card(Seed _seed, int _value) {
    setSeed(_seed);
    value = _value;
}

int Card::getValue() const {
    return value;
}

void Card::printCard(){
    cout << getValue() << " ";
    switch (this->getSeed()) {
        case Card::Seed::Ori:
            cout << "ori" << endl;
            break;
        case Card::Seed::Bastoni:
            cout << "bastoni" << endl;
            break;
        case Card::Seed::Coppe:
            cout << "coppe" << endl;
            break;
        case Card::Seed::Spade:
            cout << "spade" << endl;
            break;
    }

}

Card::Seed Card::getSeed() const {
    return seed;
}

void Card::setSeed(Card::Seed seed) {
    Card::seed = seed;
}




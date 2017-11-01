#include "Card.h"
#include <iostream>

using namespace std;

Card::Card(Seed _seed, int _value) {
    setSeed(_seed);
    value = _value;
    switch (_value) {
        case 1 :
            setPrimieraValue(16);
            break;
        case 2 :
            setPrimieraValue(12);
            break;
        case 3 :
            setPrimieraValue(13);
            break;
        case 4 :
            setPrimieraValue(14);
            break;
        case 5 :
            setPrimieraValue(15);
            break;
        case 6 :
            setPrimieraValue(18);
            break;
        case 7 :
            setPrimieraValue(21);
            break;
        case 8 :
            setPrimieraValue(10);
            break;
        case 9 :
            setPrimieraValue(10);
            break;
        case 10 :
            setPrimieraValue(10);
            break;
    }
}

int Card::getValue() const {
    return value;
}

void Card::printCard() {
    cout << " " << getValue() << " ";
    switch (this->getSeed()) {
        case Card::Seed::Ori:
            cout << "ori";
            break;
        case Card::Seed::Bastoni:
            cout << "bastoni";
            break;
        case Card::Seed::Coppe:
            cout << "coppe";
            break;
        case Card::Seed::Spade:
            cout << "spade";
            break;
    }

}

Card::Seed Card::getSeed() const {
    return seed;
}

void Card::setSeed(Card::Seed seed) {
    Card::seed = seed;
}

int Card::getPrimieraValue() const {
    return primieraValue;
}

void Card::setPrimieraValue(int primieraValue) {
    Card::primieraValue = primieraValue;
}




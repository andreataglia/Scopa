//
// Created by Matteo Sinico on 30/10/17.
//

#ifndef SCOPA_DECK_H
#define SCOPA_DECK_H


#include <list>
#include <memory>
#include "Card.h"
using namespace std;

class Deck {

public:
    Deck();

    void shuffle();

    void print();

    shared_ptr<Card> drawCard();

    list<shared_ptr<Card>> cards;
};


#endif //SCOPA_DECK_H

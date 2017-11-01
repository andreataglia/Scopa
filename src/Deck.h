//
// Created by Matteo Sinico on 30/10/17.
//

#ifndef SCOPA_DECK_H
#define SCOPA_DECK_H


#include <list>
#include <memory>
#include <vector>
#include "Card.h"
using namespace std;

class Deck {

public:
    Deck();

    void shuffle();

    void print();

    shared_ptr<Card> drawCard();

    shared_ptr<Card> drawCard(int, Card::Seed);

    vector<shared_ptr<Card>> cards;
};


#endif //SCOPA_DECK_H

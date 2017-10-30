//
// Created by Spranga on 30-Oct-17.
//

#ifndef SCOPA_STATE_H
#define SCOPA_STATE_H

#include "Card.h"
#include "Deck.h"
#include <memory>
#include <list>

using namespace std;

class State {

public:

    State();

    void setTurn(int newTurn);

    int getTurn() const;

    void advanceTurn();

    int getWhoPlays() const;

    void setWhoPlays(int whoPlays);

    void addCardToPlayer(shared_ptr<Card> card, int player);

    void addCardToPile(shared_ptr<Card> card, int player);

    void addCardToTable(shared_ptr<Card> card);

    void printState();

    list<shared_ptr<Card>> myHand1;
    list<shared_ptr<Card>> myHand2;
    list<shared_ptr<Card>> enemyHand1;
    list<shared_ptr<Card>> enemyHand2;
    list<shared_ptr<Card>> tableCards; //keep them ordered
    list<shared_ptr<Card>> myPile;
    list<shared_ptr<Card>> enemyPile;

private:
    int gameTurn;
    int whoPlays;
};


#endif //SCOPA_STATE_H

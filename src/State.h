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
    void setTurn(int newTurn);

    int getTurn() const;

    void advanceTurn();

    int getWhoPlays() const;

    void setWhoPlays(int whoPlays);

    void addCardToPlayer(unique_ptr<Card> card, int player);

    void addCardToPile(unique_ptr<Card> card, int player);

    void addCardToTable(unique_ptr<Card> card);

    list<unique_ptr<Card>> myHand1;
    list<unique_ptr<Card>> myHand2;
    list<unique_ptr<Card>> enemyHand1;
    list<unique_ptr<Card>> enemyHand2;
    list<unique_ptr<Card>> tableCards; //keep them ordered
    list<unique_ptr<Card>> myPile;
    list<unique_ptr<Card>> enemyPile;

private:
    int gameTurn;
    int whoPlays;
};


#endif //SCOPA_STATE_H

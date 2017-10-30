//
// Created by Spranga on 30-Oct-17.
//

#include <vector>
#include "State.h"

void State::setTurn(int newTurn) {
    if (!(newTurn <= 4 && newTurn >= 1)) throw "Turn is not between 1 and 4!";
    gameTurn = newTurn;
}

int State::getTurn() const {
    return gameTurn;
}

void State::addCardToPlayer(unique_ptr<Card> card, int player) {
    switch (player) {
        case 1 :
            myHand1.push_back(move(card));
        case 2 :
            enemyHand1.push_back(move(card));
        case 3 :
            myHand2.push_back(move(card));
        case 4 :
            enemyHand2.push_back(move(card));
    }
}

void State::addCardToPile(unique_ptr<Card> card, int player) {
    switch (player) {
        case 1 :
            myPile.push_back(move(card));
        case 2 :
            enemyPile.push_back(move(card));
        case 3 :
            myPile.push_back(move(card));
        case 4 :
            enemyPile.push_back(move(card));
    }
}

//cards must be kept in ascending order of value for performance reasons
void State::addCardToTable(unique_ptr<Card> card) {
    list<unique_ptr<Card>>::iterator it;
    for(it = tableCards.begin(); it != tableCards.end(); ++it) {
        if (card->getValue() <= it->get()->getValue()){
            if (card->getValue() == it->get()->getValue() && it->get()->getSeed()==Card::Seed::Ori){
                it++;
            }
            tableCards.insert(it, move(card));
            continue;
        }
    }
}

int State::getWhoPlays() const {
    return whoPlays;
}

void State::advanceTurn() {
    int t = getTurn() + 1;
    setWhoPlays(getWhoPlays() + 1);
    if (getWhoPlays() == 5){
        setWhoPlays(1);
    }
    setTurn(t);
}

void State::setWhoPlays(int whoPlays) {
    State::whoPlays = whoPlays;
}



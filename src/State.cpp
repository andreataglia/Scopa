//
// Created by Spranga on 30-Oct-17.
//

#include <vector>
#include "State.h"
#include <iostream>

State::State() {};

void State::setTurn(int newTurn) {
    if (!(newTurn <= 4 && newTurn >= 1)) throw "Turn is not between 1 and 4!";
    gameTurn = newTurn;
}

int State::getTurn() const {
    return gameTurn;
}

void State::addCardToPlayer(shared_ptr<Card> card, int player) {
    switch (player) {
        case 1 :
            myHand1.push_back(card);
            break;
        case 2 :
            enemyHand1.push_back(card);
            break;
        case 3 :
            myHand2.push_back(card);
            break;
        case 4 :
            enemyHand2.push_back(card);
            break;
    }
}

void State::addCardToPile(shared_ptr<Card> card, int player) {
    switch (player) {
        case 1 :
            myPile.push_back(card);
            break;
        case 2 :
            enemyPile.push_back(card);
            break;
        case 3 :
            myPile.push_back(card);
            break;
        case 4 :
            enemyPile.push_back(card);
            break;
    }
}

//cards must be kept in ascending order of value for performance reasons
void State::addCardToTable(shared_ptr<Card> card) {
    list<shared_ptr<Card>>::iterator it;
    for(it = tableCards.begin(); it != tableCards.end(); ++it) {
        if (card->getValue() <= it->get()->getValue()){
            if (card->getValue() == it->get()->getValue() && it->get()->getSeed()==Card::Seed::Ori){
                it++;
            }
            tableCards.insert(it, card);
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

void State::printState(){

    list<shared_ptr<Card>>::iterator it;
    for(it = myHand1.begin(); it != myHand1.end(); ++it) {
        cout << "myHand1: ";
        it->get()->printCard();
        cout << endl;
    }
    for(it = myHand2.begin(); it != myHand2.end(); ++it) {
        cout << "myHand2: ";
        it->get()->printCard();
        cout << endl;
    }
    for(it = enemyHand1.begin(); it != enemyHand1.end(); ++it) {
        cout << "enemyHand1: ";
        it->get()->printCard();
        cout << endl;
    }
    for(it = enemyHand2.begin(); it != enemyHand2.end(); ++it) {
        cout << "enemyHand2: ";
        it->get()->printCard();
        cout << endl;
    }
    for(it = myPile.begin(); it != myPile.end(); ++it) {
        cout << "myPile: ";
        it->get()->printCard();
        cout << endl;
    }
    for(it = enemyPile.begin(); it != enemyPile.end(); ++it) {
        cout << "enemyPile: ";
        it->get()->printCard();
        cout << endl;
    }
    for(it = tableCards.begin(); it != tableCards.end(); ++it) {
        cout << "tableCards: ";
        it->get()->printCard();
        cout << endl;
    }

    cout << "current turn: " << getTurn() << endl;
    cout << "current player: " << getWhoPlays() << endl;

}


//
// Created by Spranga on 30-Oct-17.
//

#include <vector>
#include "State.h"
#include <iostream>

State::State() {};

void State::setTurn(int newTurn) {
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
        default:
            throw "player does not exist";
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
        default:
            throw "player does not exist";
    }
}

//cards must be kept in ascending order of value for performance reasons
void State::addCardToTable(shared_ptr<Card> card) {
    if (!tableCards.empty()) {
        auto it = tableCards.begin();
        if (card->getSeed() == Card::Seed::Ori) {
            while (it != tableCards.end() && card->getValue() > it->get()->getValue()) {
                it++;
            }
        } else {
            while (it != tableCards.end() && card->getValue() >= it->get()->getValue()) {
                it++;
            }
        }
        tableCards.insert(it, card);
    } else {
        tableCards.push_back(card);
    }
}

int State::getWhoPlays() const {
    return whoPlays;
}

void State::advanceTurn() {
    int t = getTurn() + 1;
    setWhoPlays(getWhoPlays() + 1);
    if (getWhoPlays() == 5) {
        setWhoPlays(1);
    }
    setTurn(t);
}

void State::setWhoPlays(int _whoPlays) {
    whoPlays = _whoPlays;
}

void State::printState() {
    vector<shared_ptr<Card>>::iterator it;
    cout << endl << "myHand1: ";
    for (it = myHand1.begin(); it != myHand1.end(); ++it) {
        it->get()->printCard();
    }
    cout << endl << "myHand2: ";
    for (it = myHand2.begin(); it != myHand2.end(); ++it) {
        it->get()->printCard();
    }
    cout << endl << "enemyHand1: ";
    for (it = enemyHand1.begin(); it != enemyHand1.end(); ++it) {
        it->get()->printCard();
    }
    cout << endl << "enemyHand2: ";
    for (it = enemyHand2.begin(); it != enemyHand2.end(); ++it) {
        it->get()->printCard();
    }
    cout << endl << "myPile: ";
    for (it = myPile.begin(); it != myPile.end(); ++it) {
        it->get()->printCard();
    }
    cout << endl << "enemyPile: ";
    for (it = enemyPile.begin(); it != enemyPile.end(); ++it) {
        it->get()->printCard();
    }
    cout << endl << "tableCards: ";
    for (it = tableCards.begin(); it != tableCards.end(); ++it) {
        it->get()->printCard();
    }
    cout << endl << "current turn: " << getTurn();
    cout << endl << "current player: " << getWhoPlays() << endl;
}

vector<shared_ptr<Card>> *State::getCurrentPlayerHand() {
    switch (getWhoPlays()) {
        case 1:
            return &myHand1;
        case 2:
            return &enemyHand1;
        case 3:
            return &myHand2;
        case 4:
            return &enemyHand2;
        default:
            throw "player does not exist";
    }
}

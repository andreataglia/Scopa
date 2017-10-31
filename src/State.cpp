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
    it = tableCards.begin();
    if(tableCards.empty()){
        tableCards.insert(it, card);
    }
    else{
        while(it!= tableCards.end() && card.get()->getValue() > it->get()->getValue() ){
            it++;
        }
        while(it != tableCards.end() && card.get()->getValue() > it->get()->getValue() && card.get()->getSeed() == Card::Seed::Ori){
            it++;
        }
        tableCards.insert(it, card);
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
    cout << endl << "myHand1: ";
    for(it = myHand1.begin(); it != myHand1.end(); ++it) {
        it->get()->printCard();
    }
    cout << endl << "myHand2: ";
    for(it = myHand2.begin(); it != myHand2.end(); ++it) {
        it->get()->printCard();
    }
    cout << endl << "enemyHand1: ";
    for(it = enemyHand1.begin(); it != enemyHand1.end(); ++it) {
        it->get()->printCard();
    }
    cout << endl << "enemyHand2: ";
    for(it = enemyHand2.begin(); it != enemyHand2.end(); ++it) {
        it->get()->printCard();
    }
    cout << endl << "myPile: ";
    for(it = myPile.begin(); it != myPile.end(); ++it) {
        it->get()->printCard();
    }
    cout << endl << "enemyPile: ";
    for(it = enemyPile.begin(); it != enemyPile.end(); ++it) {
        it->get()->printCard();
    }
    cout << endl << "tableCards: ";
    for(it = tableCards.begin(); it != tableCards.end(); ++it) {
        it->get()->printCard();
    }

    cout << endl << "current turn: " << getTurn() << endl;
    cout << "current player: " << getWhoPlays() << endl;

}


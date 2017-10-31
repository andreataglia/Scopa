//
// Created by Spranga on 30-Oct-17.
//

#include "Game.h"

Game::Game(State state) {
    currentState = state;
}

void Game::playerDiscardCard(int player, shared_ptr<Card> card) {
    //check if there is a card of same value
    list<shared_ptr<Card>>::iterator it;
    bool discarded = true;
    for(it = currentState.tableCards.begin(); it != currentState.tableCards.end(); ++it) {
        //remove from the table and then add the cards to the player pile.
        if (card->getValue() == it->get()->getValue()){
            currentState.tableCards.erase(it);
            currentState.addCardToPile(card, player);
            currentState.addCardToPile(*it, player);
            discarded = false;
        }
    }
    if (discarded){
        currentState.addCardToTable(card);
    }
}

void Game::playerCatch(int player, shared_ptr<Card> playerCard, list<shared_ptr<Card>> tableCardsChosen){
    list<shared_ptr<Card>>::iterator it;
    int sum=0;
    for(it = tableCardsChosen.begin(); it!=tableCardsChosen.end(); ++it){
        sum += it->get()->getValue();
    }
    if (playerCard->getValue() == sum){
        currentState.addCardToPile(playerCard, player);
        for (it = tableCardsChosen.begin(); it != tableCardsChosen.end(); ++it){
            currentState.tableCards.erase(it);
            currentState.addCardToPile(*it, player);
        }
    }
    else throw "not valid catch";
}

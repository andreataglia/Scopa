//
// Created by Spranga on 30-Oct-17.
//

#include "Game.h"

void Game::playerPlaysCard(int player, unique_ptr<Card> card) {
    //check if there is a card of same value
    list<shared_ptr<Card>>::iterator it;
    for(it = currentState.tableCards.begin(); it != currentState.tableCards.end(); ++it) {
        if (card->getValue() == it->get()->getValue()){
            //tableCards.insert(it, move(card));
            continue;
        }
    }
}

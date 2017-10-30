//
// Created by Spranga on 30-Oct-17.
//

#ifndef SCOPA_GAME_H
#define SCOPA_GAME_H

#include "State.h"
#include "Deck.h"

class Game {
public:
    Game(State state);

    void playerPlaysCard(int player, unique_ptr<Card> card);

    Deck deck;
    State currentState;
};


#endif //SCOPA_GAME_H

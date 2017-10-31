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

    void playerDiscardCard(int player, shared_ptr<Card> card);

    void playerCatch(int player, shared_ptr<Card>, list<shared_ptr<Card>>);

    State currentState;
};


#endif //SCOPA_GAME_H

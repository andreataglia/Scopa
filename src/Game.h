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

    void playerPlaysCard(int player);

    void advanceGame();

    int playFullGame();

    long random_at_most(long max);

    void playerCatch(int player, shared_ptr<Card>, list<shared_ptr<Card>>);

    State currentState;
    int myPoints;
    int enemyPoints;
    Deck deck;
private:
    void checkScopa(int player);
};


#endif //SCOPA_GAME_H

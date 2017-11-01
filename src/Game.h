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

    void
    initGame(vector<shared_ptr<Card>> tableCards, vector<shared_ptr<Card>> myHand1, vector<shared_ptr<Card>> myHand2,
             int playerWhoPlays);

    void initRandomGame();

    void updateState(shared_ptr<Card> myCard, vector<shared_ptr<Card>> cardsChosen, bool scopa);

    void playerPlaysCard(int player);

    void advanceGame();

    void suggestMove(int accuracy);

    static short random_at_most(short max);

    int rollOut();

    State currentState;
    int myPoints = 0;
    int enemyPoints = 0;
    Deck deck;
    int lastPlayerToCatch = 0;
    bool gameOver = false;

private:

    void checkScopa(int player);

    void playerPlaysCard(int player, int card_position);

    void resolveCardPlayed(int player, shared_ptr<Card> card);

    void simulateGames(State state, int times, short card);
};


#endif //SCOPA_GAME_H

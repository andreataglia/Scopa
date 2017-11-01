#include <vector>
#include "Game.h"

Game::Game(State state) {
    currentState = state;
}

void Game::initializeGame(){
    currentState.setTurn(1);
    currentState.setWhoPlays(1);
}

void Game::playerPlaysCard(int player) {
    //choose random card to play
    shared_ptr<Card> card;
    switch (player) {
        case 1 :
            //TODO currentState.myHand1.select random
            currentState.myHand1.remove(card);
            break;
        case 2 :
            currentState.enemyHand1.remove(card);
            break;
        case 3 :
            currentState.myHand2.remove(card);
            break;
        case 4 :
            currentState.enemyHand2.remove(card);
            break;
    }

    bool resolved = false;
    //check if there is a card of same value
    vector<shared_ptr<Card>>::iterator it = currentState.tableCards.begin();
    while (it != currentState.tableCards.end() && !resolved) {
        if (card->getValue() == it->get()->getValue()) {
            currentState.addCardToPile(card, player);
            currentState.addCardToPile(*it, player);
            currentState.tableCards.remove(*it);
            checkScopa(player);
            resolved = true;
        }
        it++;
    }

    //TODO check if more cards can sum up to be taken
}

//returns difference between myPoints and enemyPoints
int Game::playFullGame() {
    while (!deck.cards.empty()) {

    }
    return myPoints - enemyPoints;
}

void Game::checkScopa(int player) {
    if (currentState.tableCards.empty()) {
        if (player % 2 == 0) {
            myPoints++;
        } else {
            enemyPoints++;
        }
    }
}

//game advances until players have no cards in their hands
void Game::advanceGame() {
    //draw three cards each if needed
    if (currentState.myHand1.empty() && currentState.enemyHand1.empty() && currentState.myHand2.empty() &&
        currentState.enemyHand2.empty()) {
        for (int i = 0; i < 3; ++i) {
            currentState.myHand1.push_back(deck.drawCard());
            currentState.enemyHand1.push_back(deck.drawCard());
            currentState.myHand2.push_back(deck.drawCard());
            currentState.enemyHand2.push_back(deck.drawCard());
        }
    }
    //find out what stage we are at
    while (true) {
        playerPlaysCard(currentState.getWhoPlays());
    }
}

long random_at_most(long max) {
    unsigned long
    // max <= RAND_MAX < ULONG_MAX, so this is okay.
            num_bins = (unsigned long) max + 1,
            num_rand = (unsigned long) RAND_MAX + 1,
            bin_size = num_rand / num_bins,
            defect   = num_rand % num_bins;

    long x;
    do {
        //x = rnd();
    }
        // This is carefully written not to overflow
    while (num_rand - defect <= (unsigned long)x);

    // Truncated division is intentional
    return x/bin_size;
}

void Game::playerCatch(int player, shared_ptr<Card> playerCard, vector<shared_ptr<Card>> tableCardsChosen){
    vector<shared_ptr<Card>>::iterator it;
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

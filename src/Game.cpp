#include <vector>
#include <algorithm>
#include "Game.h"

Game::Game(State state) {
    currentState = state;
    Deck deck;
    deck.shuffle();
}

void Game::initGame(vector<shared_ptr<Card>> tableCards, vector<shared_ptr<Card>> myHand1, vector<shared_ptr<Card>> myHand2, int playerWhoPlays){
    currentState.setWhoPlays(playerWhoPlays);
    currentState.tableCards = tableCards;
    currentState.myHand1 = myHand1;
    currentState.myHand2 = myHand2;
    for (int i = 0; i < 3; ++i) {
        currentState.enemyHand1.push_back(deck.drawCard());
        currentState.enemyHand2.push_back(deck.drawCard());
    }
}

void Game::initRandomGame() {
    currentState.setTurn(1);
    currentState.setWhoPlays(1);
    for (int i = 0; i < 3; ++i) {
        currentState.myHand1.push_back(deck.drawCard());
        currentState.enemyHand1.push_back(deck.drawCard());
        currentState.myHand2.push_back(deck.drawCard());
        currentState.enemyHand2.push_back(deck.drawCard());
    }
    for(int i = 0; i < 4; i++){
        currentState.tableCards.push_back(deck.drawCard());
    }
    currentState.printState();
}

void Game::updateState(shared_ptr<Card> myCard, vector<shared_ptr<Card>> cardsChosen, bool scopa){
    switch (currentState.getWhoPlays()) {
        case 1 :
            currentState.myHand1.erase(std::remove(currentState.myHand1.begin(), currentState.myHand1.end(), myCard), currentState.myHand1.end());
            break;
        case 2 :
            currentState.enemyHand1.erase(std::remove(currentState.enemyHand1.begin(), currentState.enemyHand1.end(), myCard), currentState.enemyHand1.end());
            break;
        case 3 :
            currentState.myHand2.erase(std::remove(currentState.myHand2.begin(), currentState.myHand2.end(), myCard), currentState.myHand2.end());
            break;
        case 4 :
            currentState.enemyHand2.erase(std::remove(currentState.enemyHand2.begin(), currentState.enemyHand2.end(), myCard), currentState.enemyHand2.end());
            break;
    }
    vector<shared_ptr<Card>>::iterator it;
    for(it = cardsChosen.begin(); it!= cardsChosen.end(); it++ ){
        currentState.tableCards.erase(std::remove(currentState.tableCards.begin(), currentState.tableCards.end(), *it), currentState.tableCards.end());
        if(currentState.getWhoPlays()%2 == 1)
            currentState.myPile.push_back(*it);
        else
            currentState.enemyPile.push_back(*it);
    }
    if(scopa && currentState.getWhoPlays()%2 == 1) {
        myPoints++;
    }
    else enemyPoints++;
}

void Game::playerPlaysCard(int player) {
    //choose random card to play
    shared_ptr<Card> card;
    switch (player) {
        case 1 :
            //TODO currentState.myHand1.select random
            currentState.myHand1.erase(std::remove(currentState.myHand1.begin(), currentState.myHand1.end(), card), currentState.myHand1.end());
            break;
        case 2 :
            currentState.enemyHand1.erase(std::remove(currentState.enemyHand1.begin(), currentState.enemyHand1.end(), card), currentState.enemyHand1.end());
            break;
        case 3 :
            currentState.myHand2.erase(std::remove(currentState.myHand2.begin(), currentState.myHand2.end(), card), currentState.myHand2.end());
            break;
        case 4 :
            currentState.enemyHand2.erase(std::remove(currentState.enemyHand2.begin(), currentState.enemyHand2.end(), card), currentState.enemyHand2.end());
            break;
    }

    bool resolved = false;
    //check if there is a card of same value
    auto it = currentState.tableCards.begin();
    while (it != currentState.tableCards.end() && !resolved) {
        if (card->getValue() == it->get()->getValue()) {
            currentState.addCardToPile(card, player);
            currentState.addCardToPile(*it, player);
            currentState.tableCards.erase(std::remove(currentState.tableCards.begin(), currentState.tableCards.end(), *it), currentState.tableCards.end());
            checkScopa(player);
            resolved = true;
        }
        it++;
    }
    if (!resolved && currentState.tableCards.size() > 2) {
        it = currentState.tableCards.begin();
        auto it2 = currentState.tableCards.begin()++;
        auto it3 = currentState.tableCards.begin()++;
        it3++;
        while (it != currentState.tableCards.end() && !resolved) {

        }
    }

    //TODO check if more cards can sum up to be taken

    advanceGame();
}

//returns difference between myPoints and enemyPoints
int Game::playFullGame() {
    while (!deck.cards.empty()) {

    }
    return myPoints - enemyPoints;
}

void Game::checkScopa(int player) {
    if (currentState.tableCards.empty() && !deck.cards.empty()) {
        if (player % 2 == 0) {
            enemyPoints++;
        } else {
            myPoints++;
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
    currentState.setWhoPlays(currentState.getWhoPlays() + 1);
    currentState.setTurn(currentState.getTurn() + 1);

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
        x = rand();
    }
        // This is carefully written not to overflow
    while (num_rand - defect <= (unsigned long)x);

    // Truncated division is intentional
    return x/bin_size;
}

/*
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
}*/



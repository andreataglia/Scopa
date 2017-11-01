#include <vector>
#include <algorithm>
#include <iostream>
#include <thread>
#include "Game.h"

Game::Game(State state) {
    currentState = state;
    Deck deck;
    deck.shuffle();
}

void
Game::initGame(vector<shared_ptr<Card>> tableCards, vector<shared_ptr<Card>> myHand1, vector<shared_ptr<Card>> myHand2,
               int playerWhoPlays) {
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
    deck.shuffle();
    currentState.setTurn(1);
    currentState.setWhoPlays(1);
    for (int i = 0; i < 3; ++i) {
        currentState.myHand1.push_back(deck.drawCard());
        currentState.enemyHand1.push_back(deck.drawCard());
        currentState.myHand2.push_back(deck.drawCard());
        currentState.enemyHand2.push_back(deck.drawCard());
    }
    for (int i = 0; i < 4; i++) {
        currentState.addCardToTable(deck.drawCard());
    }
}

void Game::updateState(shared_ptr<Card> myCard, vector<shared_ptr<Card>> cardsChosen, bool scopa) {
    switch (currentState.getWhoPlays()) {
        case 1 :
            currentState.myHand1.erase(std::remove(currentState.myHand1.begin(), currentState.myHand1.end(), myCard),
                                       currentState.myHand1.end());
            break;
        case 2 :
            currentState.enemyHand1.erase(
                    std::remove(currentState.enemyHand1.begin(), currentState.enemyHand1.end(), myCard),
                    currentState.enemyHand1.end());
            break;
        case 3 :
            currentState.myHand2.erase(std::remove(currentState.myHand2.begin(), currentState.myHand2.end(), myCard),
                                       currentState.myHand2.end());
            break;
        case 4 :
            currentState.enemyHand2.erase(
                    std::remove(currentState.enemyHand2.begin(), currentState.enemyHand2.end(), myCard),
                    currentState.enemyHand2.end());
            break;
    }
    vector<shared_ptr<Card>>::iterator it;
    for (it = cardsChosen.begin(); it != cardsChosen.end(); it++) {
        currentState.tableCards.erase(std::remove(currentState.tableCards.begin(), currentState.tableCards.end(), *it),
                                      currentState.tableCards.end());
        if (currentState.getWhoPlays() % 2 == 1)
            currentState.myPile.push_back(*it);
        else
            currentState.enemyPile.push_back(*it);
    }
    if (scopa && currentState.getWhoPlays() % 2 == 1) {
        myPoints++;
    } else enemyPoints++;
}

void Game::resolveCardPlayed(int player, shared_ptr<Card> card) {
    bool resolved = false;
    //check if there is ONE card of same value
    auto it = currentState.tableCards.begin();
    while (it != currentState.tableCards.end() && !resolved) {
        if (card->getValue() == it->get()->getValue()) {
            currentState.addCardToPile(card, player);
            currentState.addCardToPile(*it, player);
            currentState.tableCards.erase(
                    std::remove(currentState.tableCards.begin(), currentState.tableCards.end(), *it),
                    currentState.tableCards.end());
            checkScopa(player);
            resolved = true;
            lastPlayerToCatch = player;
        }
        it++;
    }
    //check if THREE cards can be gotten
    if (!resolved && currentState.tableCards.size() > 2) {
        //while (it != currentState.tableCards.end() && !resolved) {}
    }

    //check if TWO cards can be gotten
    if (!resolved && currentState.tableCards.size() > 1) {
        int i = 0, k = 1;
        while (!resolved && i < currentState.tableCards.size()) {
            while (!resolved && k < currentState.tableCards.size()) {
                if (currentState.tableCards[i]->getValue() + currentState.tableCards[k]->getValue() ==
                    card->getValue()) {
                    resolved = true;
                    lastPlayerToCatch = player;
                    currentState.addCardToPile(card, player);
                    currentState.addCardToPile(currentState.tableCards[i], player);
                    currentState.addCardToPile(currentState.tableCards[k], player);
                    currentState.tableCards.erase(currentState.tableCards.begin() + i);
                    currentState.tableCards.erase(currentState.tableCards.begin() + k);
                }
                k++;
            }
            i++;
            k = i + 1;
        }
    }

    //if no match could be found just place the card on the table
    if (!resolved) {
        currentState.addCardToTable(card);
    }
}

void Game::playerPlaysCard(int player, int card_position) {
    short n = 0;
    shared_ptr<Card> card;
    switch (player) {
        case 1 :
            card = currentState.myHand1[card_position];
            currentState.myHand1.erase(currentState.myHand1.begin() + n);
            break;
        case 2 :
            card = currentState.enemyHand1[card_position];
            currentState.enemyHand1.erase(currentState.enemyHand1.begin() + n);
            break;
        case 3 :
            card = currentState.myHand2[card_position];
            currentState.myHand2.erase(currentState.myHand2.begin() + n);
            break;
        case 4 :
            card = currentState.enemyHand2[card_position];
            currentState.enemyHand2.erase(currentState.enemyHand2.begin() + n);
            break;
        default:
            throw "player does not exist!";
    }

    resolveCardPlayed(player, card);
}

void Game::playerPlaysCard(int player) {
    //choose random card to play
    short n = 0;
    shared_ptr<Card> card;
    switch (player) {
        case 1 :
            if (currentState.myHand1.size() > 1) {
                n = Game::random_at_most(static_cast<short>(currentState.myHand1.size() - 1));
            }
            card = currentState.myHand1[n];
            currentState.myHand1.erase(currentState.myHand1.begin() + n);
            break;
        case 2 :
            if (currentState.enemyHand1.size() > 1) {
                n = Game::random_at_most(static_cast<short>(currentState.enemyHand1.size() - 1));
            }
            card = currentState.enemyHand1[n];
            currentState.enemyHand1.erase(currentState.enemyHand1.begin() + n);
            break;
        case 3 :
            if (currentState.myHand2.size() > 1) {
                n = Game::random_at_most(static_cast<short>(currentState.myHand2.size() - 1));
            }
            card = currentState.myHand2[n];
            currentState.myHand2.erase(currentState.myHand2.begin() + n);
            break;
        case 4 :
            if (currentState.enemyHand2.size() > 1) {
                n = Game::random_at_most(static_cast<short>(currentState.enemyHand2.size() - 1));
            }
            card = currentState.enemyHand2[n];
            currentState.enemyHand2.erase(currentState.enemyHand2.begin() + n);
            break;
        default:
            throw "player does not exist!";
    }

    resolveCardPlayed(player, card);
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

int Game::rollOut() {
    while (!gameOver) {
        playerPlaysCard(currentState.getWhoPlays());
        advanceGame();
    }
    vector<shared_ptr<Card>>::iterator it;
    for (it = currentState.tableCards.begin(); it != currentState.tableCards.end(); ++it) {
        currentState.addCardToPile(*it, lastPlayerToCatch);
    }
    currentState.tableCards.clear();

    //Game Over -> count final points

    //carte a lungo
    if (currentState.myPile.size() > 20) { myPoints++; }
    else if (currentState.enemyPile.size() > 20) { enemyPoints++; }

    //ori and sette bello and primiera
    int n = 0;
    bool settebello = false;
    int primiera[4] = {0, 0, 0, 0};
    int primieraEnemy[4] = {0, 0, 0, 0};
    for (it = currentState.myPile.begin(); it != currentState.myPile.end(); ++it) {
        switch (it->get()->getSeed()) {
            case Card::Seed::Ori:
                if (it->get()->getPrimieraValue() > primiera[0]) { primiera[0] = it->get()->getPrimieraValue(); }
                if (it->get()->getValue() == 7) { settebello = true; }
                n++;
                break;
            case Card::Seed::Bastoni:
                if (it->get()->getPrimieraValue() > primiera[1]) { primiera[1] = it->get()->getPrimieraValue(); }
                break;
            case Card::Seed::Coppe:
                if (it->get()->getPrimieraValue() > primiera[2]) { primiera[2] = it->get()->getPrimieraValue(); }
                break;
            case Card::Seed::Spade:
                if (it->get()->getPrimieraValue() > primiera[3]) { primiera[3] = it->get()->getPrimieraValue(); }
                break;
        }
    }
    for (it = currentState.enemyPile.begin(); it != currentState.enemyPile.end(); ++it) {
        switch (it->get()->getSeed()) {
            case Card::Seed::Ori:
                if (it->get()->getPrimieraValue() >
                    primieraEnemy[0]) { primieraEnemy[0] = it->get()->getPrimieraValue(); }
                break;
            case Card::Seed::Bastoni:
                if (it->get()->getPrimieraValue() >
                    primieraEnemy[1]) { primieraEnemy[1] = it->get()->getPrimieraValue(); }
                break;
            case Card::Seed::Coppe:
                if (it->get()->getPrimieraValue() >
                    primieraEnemy[2]) { primieraEnemy[2] = it->get()->getPrimieraValue(); }
                break;
            case Card::Seed::Spade:
                if (it->get()->getPrimieraValue() >
                    primieraEnemy[3]) { primieraEnemy[3] = it->get()->getPrimieraValue(); }
                break;
        }
    }

    int primieraSum = 0;
    for (int i = 0; i < 4; ++i) {
        primieraSum += primiera[i] - primieraEnemy[i];
    }

    if (primieraSum > 0) { myPoints++; } else if (primieraSum < 0) { enemyPoints++; }
    if (n > 5) { myPoints++; }
    else if (n < 5) { enemyPoints++; }
    if (settebello) { myPoints++; } else { enemyPoints++; }

    cout << endl << "///GAME OVER: myPoints: " << myPoints << ", enemyPoints: " << enemyPoints << endl;
    cout << "final state:" << endl;
    currentState.printState();
}

//let players draw cards or just advance turn
void Game::advanceGame() {
    //draw three cards each if needed
    if (currentState.myHand1.empty() && currentState.enemyHand1.empty() && currentState.myHand2.empty() &&
        currentState.enemyHand2.empty() && !deck.cards.empty()) {
        for (int i = 0; i < 3; ++i) {
            currentState.myHand1.push_back(deck.drawCard());
            currentState.enemyHand1.push_back(deck.drawCard());
            currentState.myHand2.push_back(deck.drawCard());
            currentState.enemyHand2.push_back(deck.drawCard());
        }
    }
    currentState.advanceTurn();
    if (currentState.getTurn() > 36) { gameOver = true; }
}

short Game::random_at_most(short max) {
    unsigned long
    // max <= RAND_MAX < ULONG_MAX, so this is okay.
            num_bins = (unsigned long) max + 1,
            num_rand = (unsigned long) RAND_MAX + 1,
            bin_size = num_rand / num_bins,
            defect = num_rand % num_bins;

    long x;
    do {
        x = rand();
    }
        // This is carefully written not to overflow
    while (num_rand - defect <= (unsigned long) x);

    // Truncated division is intentional
    return static_cast<short>( x / bin_size);
}

//task given to thread
void Game::simulateGames(State state, int times, short card) {
    Game game(state);
    game.playerPlaysCard(state.getWhoPlays(), card);
    game.rollOut();
};

//simulate "accuracy" times the game for each possible move
void Game::suggestMove(int accuracy) {
    //std::thread::thread t(simulateGames, accuracy);
    //t.join();
    for (int i = 0; i < currentState.; ++i) {

    }
}

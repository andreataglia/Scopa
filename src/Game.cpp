#include <vector>
#include <algorithm>
#include <iostream>
#include <thread>
#include "Game.h"

Game::Game(State state) {
    currentState = state;
}

void
Game::initGame(vector<shared_ptr<Card>> tableCards, vector<shared_ptr<Card>> myHand1, vector<shared_ptr<Card>> myHand2, int playerWhoPlays) {
    currentState.setWhoPlays(playerWhoPlays);
    currentState.tableCards = tableCards;
    currentState.myHand1 = myHand1;
    currentState.myHand2 = myHand2;
    for (int i = 0; i < 3; ++i) {
        currentState.enemyHand1.push_back(currentState.deck.drawCard());
        currentState.enemyHand2.push_back(currentState.deck.drawCard());
    }
}

void Game::initRandomGame() {
    currentState.deck.shuffle();
    currentState.setTurn(1);
    currentState.setWhoPlays(1);
    for (int i = 0; i < 3; ++i) {
        currentState.myHand1.push_back(currentState.deck.drawCard());
        currentState.enemyHand1.push_back(currentState.deck.drawCard());
        currentState.myHand2.push_back(currentState.deck.drawCard());
        currentState.enemyHand2.push_back(currentState.deck.drawCard());
    }
    for (int i = 0; i < 4; i++) {
        currentState.addCardToTable(currentState.deck.drawCard());
    }
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
                    currentState.addCardToPile(currentState.tableCards[k], player);
                    currentState.addCardToPile(currentState.tableCards[i], player);
                    currentState.tableCards.erase(currentState.tableCards.begin() + k);
                    currentState.tableCards.erase(currentState.tableCards.begin() + i);
                }
                k++;
            }
            i++;
            k = i + 1;
        }
    }

    //check if THREE cards can be gotten
    if (!resolved && currentState.tableCards.size() > 2) {
        int i = 0, k = 1, j = 2;
        while (!resolved && i < currentState.tableCards.size()) {
            while (!resolved && k < currentState.tableCards.size()) {
                while (!resolved && j < currentState.tableCards.size()) {
                    if (currentState.tableCards[i]->getValue() + currentState.tableCards[k]->getValue() + currentState.tableCards[j]->getValue() ==
                        card->getValue()) {
                        resolved = true;
                        lastPlayerToCatch = player;
                        currentState.addCardToPile(card, player);
                        currentState.addCardToPile(currentState.tableCards[j], player);
                        currentState.addCardToPile(currentState.tableCards[k], player);
                        currentState.addCardToPile(currentState.tableCards[i], player);
                        currentState.tableCards.erase(currentState.tableCards.begin() + j);
                        currentState.tableCards.erase(currentState.tableCards.begin() + k);
                        currentState.tableCards.erase(currentState.tableCards.begin() + i);
                    }
                    j++;
                }
                k++;
                j = k + 1;
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
    if (currentState.tableCards.empty() && !currentState.deck.cards.empty()) {
        if (player % 2 == 0) {
            enemyPoints++;
        } else {
            myPoints++;
        }
    }
}

int Game::rollOut(bool verbose) {
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

    if (verbose) {
        cout << endl << "///GAME OVER: myPoints: " << myPoints << ", enemyPoints: " << enemyPoints << endl;
        cout << "final state:";
        currentState.printState();
    }

    return myPoints - enemyPoints;
}

//let players draw cards or just advance turn
void Game::advanceGame() {
    //draw three cards each if needed
    if (currentState.myHand1.empty() && currentState.enemyHand1.empty() && currentState.myHand2.empty() &&
        currentState.enemyHand2.empty() && !currentState.deck.cards.empty()) {
        for (int i = 0; i < 3; ++i) {
            currentState.myHand1.push_back(currentState.deck.drawCard());
            currentState.enemyHand1.push_back(currentState.deck.drawCard());
            currentState.myHand2.push_back(currentState.deck.drawCard());
            currentState.enemyHand2.push_back(currentState.deck.drawCard());
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
    cout << endl << ">>>simulating games with card " << card << endl;
    Game game(state);
    game.playerPlaysCard(state.getWhoPlays(), card);
    game.advanceGame();
    Game copyGame = game;
    int p = 0;
    for (int i = 0; i < times; ++i) {
        game.currentState.deck.shuffle();
        p += game.rollOut(false);
        //TODO do we free up memory this way?
        game = copyGame;
    }
    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
    cout << ">>>playing card " << card << " you score: " << p << endl;
};

//simulate "accuracy" times the game for each possible move
void Game::suggestMove(int accuracy) {
    cout << ">>running simulation for " << accuracy << endl;
    for (int i = 0; i < currentState.getCurrentPlayerHand()->size(); ++i) {
        //std::thread::thread t(simulateGames, accuracy);
        simulateGames(currentState, accuracy, i);
    }
}

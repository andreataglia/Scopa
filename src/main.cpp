#include <iostream>
#include "Game.h"
#include <stdio.h>
#include <string.h>

using namespace std;

Card::Seed sToSeed(string s) {
    try {
        switch (s.at(0)) {
            case 'o':
                return Card::Seed::Ori;
            case 'b':
                return Card::Seed::Bastoni;
            case 's':
                return Card::Seed::Spade;
            case 'c':
                return Card::Seed::Coppe;
            default:
                throw 2;
        }
    }
    catch (int e) {
        throw e;
    }
}

vector<string> split(string sToSplit, string delimiter) {
    vector<string> stringCards;
    string token;
    size_t pos = 0;
    while ((pos = sToSplit.find(delimiter)) != std::string::npos) {
        token = sToSplit.substr(0, pos);
        stringCards.push_back(token);
        sToSplit.erase(0, pos + delimiter.length());
    }
    token = sToSplit.substr(0, pos);
    stringCards.push_back(token);
    sToSplit.erase(0, pos + delimiter.length());
    return stringCards;
}

shared_ptr<Card> toCard(string s, Deck &d) {
    vector<string> sCard = split(s, ",");
    try {
        switch (sCard[1].at(0)) {
            case 'o':
                return d.drawCard(stoi(sCard[0]), Card::Seed::Ori);
            case 'b':
                return d.drawCard(stoi(sCard[0]), Card::Seed::Bastoni);
            case 's':
                return d.drawCard(stoi(sCard[0]), Card::Seed::Spade);
            case 'c':
                return d.drawCard(stoi(sCard[0]), Card::Seed::Coppe);
            default:
                throw 1;
        }
    }
    catch (int e) {
        throw e;
    }
}

vector<shared_ptr<Card>> toVector(string s, Deck &d) {
    vector<string> stringCards = split(s, ";");
    vector<string>::iterator it;
    vector<shared_ptr<Card>> cards;
    for (it = stringCards.begin(); it != stringCards.end(); it++) {
        cards.push_back(toCard(*it, d));
    }
    return cards;
}

void move(string stringCard, vector<shared_ptr<Card>> &v1, vector<shared_ptr<Card>> &v2) {
    vector<string> vectorCard = split(stringCard, ",");
    vector<shared_ptr<Card>>::iterator it;
    shared_ptr<Card> tmp = nullptr;
    try {
        for (it = v1.begin(); it != v1.end(); ++it) {
            if (it->get()->getValue() == stoi(vectorCard[0]) && it->get()->getSeed() == sToSeed(vectorCard[1])) {
                tmp = *it;
                v1.erase(it);
                v2.push_back(tmp);
                it--;
            }
        }
        if (tmp == nullptr) {
            throw 1;
        }
    }
    catch (int e) {
        throw 1;
    }
}

void moveToTable(string stringCard, vector<shared_ptr<Card>> &v1, State &currentState) {
    vector<string> vectorCard = split(stringCard, ",");
    vector<shared_ptr<Card>>::iterator it;
    shared_ptr<Card> tmp = nullptr;
    try {
        for (it = v1.begin(); it != v1.end(); ++it) {
            if (it->get()->getValue() == stoi(vectorCard[0]) && it->get()->getSeed() == sToSeed(vectorCard[1])) {
                tmp = *it;
                v1.erase(it);
                currentState.addCardToTable(tmp);
                it--;
            }
        }
        if (tmp == nullptr) {
            throw 1;
        }
    }
    catch (int e) {
        throw 1;
    }
}

int main() {

    State current_state;
    Game game(current_state);
    cout << "Do you want to initialize a game? y/n" << std::endl;
    string choice;
    cin >> choice;
    vector<shared_ptr<Card>> cards;
    vector<shared_ptr<Card>> tableCards;
    vector<shared_ptr<Card>> myHand1;
    vector<shared_ptr<Card>> myHand2;
    int player;
    if (choice == "y") {
        bool correct = false;
        while (!correct) {
            try {
                cout << "give me the table cards in this way:" << endl << " 1 di ori = 1,o" << endl
                     << " followed by a ; like this:" << endl << " 1,o;2,s;3,b;4,c" << endl;
                string s;
                cin >> s;
                tableCards = toVector(s, game.currentState.deck);
                correct = true;
            }
            catch (int e) {
                if (e == 1) {
                    cout << "card not found" << endl;
                }
            }
        }
        correct = false;
        while (!correct) {
            try {
                cout << "give me the myHand1 cards" << endl;
                string s1;
                cin >> s1;
                myHand1 = toVector(s1, game.currentState.deck);
                correct = true;
            }
            catch (int e) {
                if (e == 1) {
                    cout << "card not found" << endl;
                }
            }
        }
        correct = false;

        while (!correct) {

            try {
                cout << "give me the myHand2 cards" << endl;
                string s2;
                cin >> s2;
                myHand2 = toVector(s2, game.currentState.deck);
                correct = true;
            }

            catch (int e) {
                if (e == 1) {
                    cout << "card not found" << endl;
                }
            }
        }
        correct = false;

        while (!correct) {

            try {
                cout << "who is playing" << endl;
                string s3;
                cin >> s3;
                player = stoi(s3);
                correct = true;
            }
            catch (int e) {
                if (e == 1) {
                    cout << "card not found" << endl;
                }
            }
        }
        game.initGame(tableCards, myHand1, myHand2, player);

    } else {
        game.initRandomGame();
    }
    game.currentState.printState();
    bool finished = false;
    while (!finished) {
        cout << "\n choose what do you want to do:\nm -> make an action\ns->suggest an action\np->print state\nq->quit"
             << endl;
        cin >> choice;
        switch (choice.at(0)) {
            case 'p':
                game.currentState.printState();
                break;
            case 's':
                game.suggestMove(100);
                break;
            case 'q':
                finished = true;
                break;
            case 'm':
                bool correct = false;
                while (!correct) {
                    try {
                        string s;
                        cout << "give me your card" << endl;
                        cin >> s;
                        cout << "give me the table cards chosen or digit none if you don't choose anything" << endl;
                        string s1;
                        cin >> s1;
                        if (s1 == "none") {
                            switch (game.currentState.getWhoPlays()) {
                                case 1 :
                                    moveToTable(s, game.currentState.myHand1, game.currentState);
                                    break;
                                case 2 :
                                    moveToTable(s, game.currentState.enemyHand1, game.currentState);
                                    break;
                                case 3 :
                                    moveToTable(s, game.currentState.myHand2, game.currentState);
                                    break;
                                case 4 :
                                    moveToTable(s, game.currentState.enemyHand2, game.currentState);
                                    break;
                            }
                            game.advanceGame();
                            correct = true;
                        } else {
                            switch (game.currentState.getWhoPlays()) {
                                case 1 :
                                    move(s, game.currentState.myHand1, game.currentState.myPile);
                                    break;
                                case 2 :
                                    move(s, game.currentState.enemyHand1, game.currentState.enemyPile);
                                    break;
                                case 3 :
                                    move(s, game.currentState.myHand2, game.currentState.myPile);
                                    break;
                                case 4 :
                                    move(s, game.currentState.enemyHand2, game.currentState.enemyPile);
                                    break;
                            }

                            vector<string> tableCardsChosen = split(s1, ";");
                            vector<string>::iterator it;
                            for (it = tableCardsChosen.begin(); it != tableCardsChosen.end(); it++) {
                                if (game.currentState.getWhoPlays() % 2 == 1) {
                                    move(*it, game.currentState.tableCards, game.currentState.myPile);
                                } else move(*it, game.currentState.tableCards, game.currentState.enemyPile);
                            }

                            cout << "is Scopa? y/n" << endl;
                            cin >> s;
                            if (s == "y") {
                                if (game.currentState.getWhoPlays() % 2 == 1) {
                                    game.myPoints++;
                                } else game.enemyPoints++;
                            }
                            game.advanceGame();
                            correct = true;
                        }
                    }
                    catch (int e) {
                        if (e == 1) {
                            cout << "card not found" << endl;
                        }
                    }
                }
                break;
        }
    }
    game.currentState.printState();

    return 0;
}


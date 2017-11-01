#include <iostream>
#include "Game.h"
#include <stdio.h>
#include <string.h>

using namespace std;

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
                    cout << "card not found"<< endl;
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
    game.rollOut(true);

    return 0;
}


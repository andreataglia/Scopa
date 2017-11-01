#include "Deck.h"
#include <random>
#include <algorithm>
#include <iostream>
#include <chrono>

using namespace std;

Deck::Deck() {
    for (int i = 1; i <= 10; i++) {
        shared_ptr<Card> card = make_shared<Card>(Card::Seed::Ori, i);
        cards.push_back(card);
    }

    for (int i = 1; i <= 10; i++) {
        shared_ptr<Card> card = make_shared<Card>(Card::Seed::Bastoni, i);
        cards.push_back(card);
    }

    for (int i = 1; i <= 10; i++) {
        shared_ptr<Card> card = make_shared<Card>(Card::Seed::Spade, i);
        cards.push_back(card);
    }

    for (int i = 1; i <= 10; i++) {
        shared_ptr<Card> card = make_shared<Card>(Card::Seed::Coppe, i);
        cards.push_back(card);
    }
}

void Deck::shuffle() // shuffle contents of a list
{
    // shuffle (the references in) the vector
    mt19937 gen(static_cast<unsigned int>(chrono::system_clock::now().time_since_epoch().count()));
    std::shuffle(cards.begin(), cards.end(), gen);

}

shared_ptr<Card> Deck::drawCard() {
    if (!cards.empty()) {
        shared_ptr<Card> card = cards[0];
        cards.erase(cards.begin());
        return card;
    } else {
        throw "deck is empty!";
    }
}

void Deck::print() {
    cout << "printing deck: " << endl;
    vector<shared_ptr<Card>>::iterator it;
    for (it = cards.begin(); it != cards.end(); ++it) {
        it->get()->printCard();
    }
}

shared_ptr<Card> Deck::drawCard(int value, Card::Seed seed){
    vector<shared_ptr<Card>>::iterator it;
    try{
        for (it = cards.begin(); it != cards.end(); ++it) {
            if(it->get()->getValue()==value && it->get()->getSeed() == seed){
                cards.erase(it);
                return *it;
            }
        }
        throw 1;
    }
    catch (int e){
        throw 1;
    }
}

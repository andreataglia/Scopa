//
// Created by Matteo Sinico on 30/10/17.
//

#include "Deck.h"
#include <vector>
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
    // create a vector of (wrapped) references to elements in the list
    // http://en.cppreference.com/w/cpp/utility/functional/reference_wrapper
    std::vector<std::reference_wrapper<const shared_ptr<Card> > > vec(cards.begin(), cards.end());

    // shuffle (the references in) the vector
    mt19937 gen(static_cast<unsigned int>(chrono::system_clock::now().time_since_epoch().count()));
    std::shuffle(vec.begin(), vec.end(), gen);

    // copy the shuffled sequence into a new list
    std::list<shared_ptr<Card>> shuffled_list{vec.begin(), vec.end()};

    // swap the old list with the shuffled list
    cards.swap(shuffled_list);
}

shared_ptr<Card> Deck::drawCard() {
    shared_ptr<Card> card = cards.front();
    cards.pop_front();
    return card;
}

void Deck::print() {
    cout << "printing deck: " << endl;
    list<shared_ptr<Card>>::iterator it;
    for (it = cards.begin(); it != cards.end(); ++it) {
        it->get()->printCard();
    }
}

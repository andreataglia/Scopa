//
// Created by Matteo Sinico on 30/10/17.
//

#include "Deck.h"
#include <vector>
#include <random>
#include <algorithm>
#include <memory>

using namespace std;

Deck::Deck() {
    for(int i=1; i<=10; i++){
        unique_ptr<Card> card(new Card(Card::Seed::Ori , i));
        cards.push_back(move(card));
    }

    for(int i=1; i<=10; i++){
        unique_ptr<Card> card(new Card(Card::Seed::Bastoni , i));
        cards.push_back(move(card));
    }

    for(int i=1; i<=10; i++){
        unique_ptr<Card> card(new Card(Card::Seed::Spade , i));
        cards.push_back(move(card));
    }

    for(int i=1; i<=10; i++){
        unique_ptr<Card> card(new Card(Card::Seed::Coppe , i));
        cards.push_back(move(card));
    }
}

template<typename T>
void Deck::shuffle(std::list<T> &lst) {
    // create a vector of (wrapped) references to elements in the list
    // http://en.cppreference.com/w/cpp/utility/functional/reference_wrapper
    std::vector< std::reference_wrapper< const T > > vec( lst.begin(), lst.end() ) ;

    // shuffle (the references in) the vector
    std::shuffle( vec.begin(), vec.end(), std::mt19937{ std::random_device{}() } ) ;

    // copy the shuffled sequence into a new list
    std::list<T> shuffled_list {  vec.begin(), vec.end() } ;

    // swap the old list with the shuffled list
    lst.swap(shuffled_list) ;
}
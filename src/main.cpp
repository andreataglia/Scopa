#include <iostream>
#include "Game.h"

int main() {
    using namespace std;

    State current_state;
    Deck deck;
    deck.shuffle();

    cout << "Do you wanna create a random game? y/n" << std::endl;
    string choice;
    cin >> choice;
    if (choice == "y"){
        current_state.setTurn(1);
        current_state.setWhoPlays(1);
        for(int i=1; i<=4; i++){
            for (int j=0; j<=2; j++){
                current_state.addCardToPlayer(deck.drawCard(), i);
            }
        }

        for(int i=0; i<=3; i++){
            current_state.addCardToTable(deck.drawCard());
        }

        current_state.printState();

        Game game(current_state);

    }
    else current_state.printState();
    return 0;
}

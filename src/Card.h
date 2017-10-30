//
// Created by Matteo Sinico on 30/10/17.
//

#ifndef SCOPA_CARD_H
#define SCOPA_CARD_H


class Card {
public:

    enum seed {Ori, Bastoni, Spade, Coppe};

    Card(seed seed, int value);

    int getValue() const;

    void setValue(int value);

private:

    int value;

};


#endif //SCOPA_CARD_H

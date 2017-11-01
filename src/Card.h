//
// Created by Matteo Sinico on 30/10/17.
//

#ifndef SCOPA_CARD_H
#define SCOPA_CARD_H


class Card {
public:

    enum class Seed {Ori, Bastoni, Spade, Coppe};

    Card(Seed seed, int value);

    int getValue() const;

    Seed getSeed() const;

    void setSeed(Seed seed);

    void printCard();

private:
    Seed seed;
    int value;
    int primieraValue;
public:
    int getPrimieraValue() const;

    void setPrimieraValue(int primieraValue);
};


#endif //SCOPA_CARD_H

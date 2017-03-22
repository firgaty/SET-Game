#include <iostream>
#include "Card.h"
#include "Deck.h"
#include "Tools.h"
#include "Game.h"


int main(int argc, char **argv)
{
    std::cout << "Hello World" << std::endl;

    Deck deck(4, 3, false);

    deck.print();

    std::deque<Card> *vec = deck.getCards();
    std::deque<Card> set;

    vec->at(0);

    set.push_back((Card &&) vec->at(0)); vec->at(0).print();
    set.push_back((Card &&) vec->at(1)); vec->at(1).print();
    set.push_back((Card &&) vec->at(2)); vec->at(2).print();

    if(deck.isSet(set)) {
        std::cout << "SET" << std::endl;
        deck.print(set);
    } else {
        std::cout << "Not SET" << std::endl;
    }

    for(int i = 0; i < 4; i++) {
        if(Deck::allDifferent(set, i)) {
            std::cout << "Different " << Tools::intToString(i) << std::endl;
        } else if (Deck::allSame(set, i)) {
            std::cout << "Same " << Tools::intToString(i) << std::endl;
        } else {
            std::cout << "Neither " << Tools::intToString(i) << std::endl;
        }
    }

    Deck *deck2 = new Deck(4, 3, false);
    Game(deck2, 0);

    return 0;
}

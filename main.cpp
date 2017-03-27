#include <iostream>
#include "Card.h"
#include "Deck.h"
#include "Tools.h"
#include "Game.h"

int main(int argc, char **argv)
{
//    Deck deck(4, 3, false);
//
//    deck.print();
//
//    std::deque<Card> *vec = deck.getCards();
//    std::deque<Card> set;
//
//    vec->at(0);
//
//    set.push_back((Card &&) vec->at(0)); vec->at(0).print();
//    set.push_back((Card &&) vec->at(1)); vec->at(1).print();
//    set.push_back((Card &&) vec->at(2)); vec->at(2).print();
//
//    if(deck.isSet(set)) {
//        std::cout << "SET" << std::endl;
//        deck.print(set);
//    } else {
//        std::cout << "Not SET" << std::endl;
//    }
//
//    for(int i = 0; i < 4; i++) {
//        if(Deck::allDifferent(set, i)) {
//            std::cout << "Different " << Tools::intToString(i) << std::endl;
//        } else if (Deck::allSame(set, i)) {
//            std::cout << "Same " << Tools::intToString(i) << std::endl;
//        } else {
//            std::cout << "Neither " << Tools::intToString(i) << std::endl;
//        }
//    }
//
//    Deck *deck2 = new Deck(4, 3, false);
//    Game(deck2, 0);
//
//    int in = 0;
//    std::deque<int> *totalSetFound = new std::deque<int>(10, 0);
//    std::deque<int> *totalSetErased = new std::deque<int>(10, 0);
//    std::deque<int> *totalCardsPerRound = new std::deque<int>(10, 0);
//    std::deque<float> *moyennesFound = new std::deque<float>(10, 0.0);
//    std::deque<float> *moyennesErased = new std::deque<float>(10, 0.0);
//
//
//
//    std::cout << "Entrez le nombre d'iteration à effectuer pour avoir une moyenne :\n";
//    std::cin >> in;
//
//    for(int i (0); i < in; i++) {
//        Deck *deck3 = new Deck(4, 3, false);
//        Game game(deck3, 0);
//        Tools::addDeque(totalSetFound, game.getSetFound());
//        Tools::addDeque(totalSetErased, game.getSetErased());
//        Tools::addDeque(totalCardsPerRound, game.getNbRoundPerCards());
//    }
//
//    for(int i(0); i < moyennesFound->size(); i ++) {
//        if(totalCardsPerRound->at(i) != 0) {
//            moyennesFound->at(i) = (float) totalSetFound->at(i) / (float) totalCardsPerRound->at(i);
//            moyennesErased->at(i) = (float) totalSetErased->at(i) / (float) totalCardsPerRound->at(i);
//
//        }
//    }
//
//    for(int i(0); i < moyennesFound->size(); i++) {
//        std::cout << i * 3 << " cards :\n";
//        std::cout << "    Found : " << moyennesFound->at(i) << "\n"
//                  << "    Erased : " << moyennesErased->at(i) << "\n" << std::endl;
//    }

    Deck *deck4 = new Deck(4,3,false);
    Game game2(deck4, 2);
    std::deque<float> moyenne(25, 0.0);

    std::cout << "MOYENNES : \n\n";
    for(int i(0); i < game2.getDifferentCards()->size(); i++) {
        moyenne.at(i) = (float) game2.getSetFoundPerNbCards()->at(i) / (float) game2.getDifferentCards()->at(i);
    }
    for(int i(0); i < moyenne.size(); i++) {
        std::cout << "Moyenne " << i << " cartes : " << moyenne.at(i) << std::endl;
    }

    return 0;
}

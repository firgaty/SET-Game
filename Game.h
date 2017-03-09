//
// Created by firgaty on 21/02/17.
//

#ifndef UNI_GAME_H
#define UNI_GAME_H

#include "Card.h"
#include "Tools.h"
#include "Deck.h"
#include <deque>

class Game {
public:
    Game();
    Game(Deck *deck);
    Game(Deck *deck, int mode); // 0: normal, 1: find all sets.
    ~Game();

    int round(int lastRound);
    bool dealCards(int nbCards); // Returns false if no more cards are left.
    std::deque<std::deque<int>> findSet(); // Redo it recursive.
    std::deque<std::deque<int>> findSetsInDeck();

    int removeSets(std::deque<std::deque<int>> setList); // IN PROGRESS removes all possible sets in m_roundCards and returns how many sets were removed.
    bool removeSet(std::deque<int> set);

    void setSetFound(int *setFound);
    void setSetErased(int *setErased);

    void printTab(int *tab, int size);
    const void printRoundCards();
    const void printSet(std::deque<int> &set);

protected:
    Deck *m_deck;
    int m_rounds;
    std::deque<Card> *m_roundCards;

    int *m_setFound;
    int *m_setErased;

    void reset();
    void addFound(std::deque<std::deque<int>> setList, int cardsInRound);
    void addErased(int nbSets, int cardsInRound);
};


#endif //UNI_GAME_H

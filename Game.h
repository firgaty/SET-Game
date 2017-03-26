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
    std::deque<std::deque<int>> findSetsInDeck();

    int removeSets(std::deque<std::deque<int>> setList); // IN PROGRESS removes all possible sets in m_roundCards and returns how many sets were removed.
    bool removeSet(std::deque<Card> &set);

    void setSetFound(std::deque<int> *setFound);
    void setSetErased(std::deque<int> *setErased);
    void setNbRoundPerCards(std::deque<int> *nbRoundPerCards);
    void setSetFoundPerNbCards(std::deque<int>* setter);
    void setDifferentCards(std::deque<int>* setter);

    int findSetsPerCards(int nbIteration, int nbCards, int setsFound);

    std::deque<int>* getSetFound();
    std::deque<int>* getSetErased();
    std::deque<int>* getNbRoundPerCards();
    std::deque<int>* getSetFoundPerNbCards();
    std::deque<int>* getDifferentCards();

    void printTab(int *tab, int size);
    void printDeque(std::deque<int> &deque);
    const void printRoundCards();
    const void printSet(std::deque<int> &set);

protected:
    Deck *m_deck;
    int m_rounds;
    Deck *m_roundCards;

    std::deque<int> *m_setFound;
    std::deque<int> *m_setErased;
    std::deque<int> *m_nbRoundPerCards;
    std::deque<int> *m_setFoundPerNbCards;
    std::deque<int> *m_differentCards;
    std::deque<bool> *m_isSetPerCards;

    void reset();
    void addFound(std::deque<std::deque<int>> setList, int cardsInRound);
    void addErased(int nbSets, int cardsInRound);
    void addNbRoundPerCards(int cardsInRound);
};


#endif //UNI_GAME_H

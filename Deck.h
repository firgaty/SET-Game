#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <deque>

class Deck
{
public:
    Deck(int nbAttr, int attrLength, bool noCards);
    Deck(int nbAttr, int attrLength, std::deque<Card> cards);
    ~Deck();

    // PRINT.
    const void print();
    static const void print(std::deque<Card> &set);
    const void print(std::deque<int> &setPos);

    // FUNCTIONS TO TEST SETS.
    bool isSet(std::deque<Card> &cards);
    static bool isSet(std::deque<Card> &cards, int nbAttr);
    static bool allDifferent(std::deque<Card> &cards, int index);
    static bool allSame(std::deque<Card> &cards, int index);
    bool isCardInDeck(const Card &c) const;
    bool isSetInDeck(const std::deque<Card> &set);

    std::deque<std::deque<int>> findSetsInDeck();

    // GETTERS & SETTERS.
    int getNbCards();
    int getNbAttr();
    int getAttrLength();
    std::deque<Card>* getCards();
    Card getCardAt(int i);

    std::tuple<Card, int> getRandCard();

    Card removeCard(int index);
    Card removeCard(Card &c);
    void addCard(Card c);

protected:
    int m_nbCards;
    int m_nbAttr;
    int m_attrLength;
    std::deque<Card> *m_cards;

    void initCards(int nbAttr, int attrLength, int nbIterations, std::deque<int> &attr);
};

#endif // DECK_H

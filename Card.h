#ifndef CARD_H
#define CARD_H

#include <deque>

class Card
{
public:
    Card(std::deque<int> attr, int nbAttr);
    ~Card();

    const void print();

    std::deque<int> getAttr();
    int getNbAttr();

protected:
    int m_nbAttr;
    std::deque<int> m_attr;
};

#endif // CARD_H

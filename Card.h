#ifndef CARD_H
#define CARD_H

#include <deque>

class Card
{
public:
    Card(std::deque<int> attr, int nbAttr);
    ~Card();

    const void print();

    std::deque<int> getAttr() const;
    int getNbAttr();

    bool isEqual(const Card &c) const;

protected:
    int m_nbAttr;
    std::deque<int> m_attr;
};

bool operator==(const Card &a, const Card &b);

#endif // CARD_H

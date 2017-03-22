#include "Card.h"
#include <iostream>
#include <sstream>
#include "Tools.h"

Card::Card(std::deque<int> attr, int nbAttr) : m_attr(attr), m_nbAttr(nbAttr)
{
}

Card::~Card()
{
}

std::deque<int> Card::getAttr() const {
    return this->m_attr;
}

int Card::getNbAttr() {
    return this->m_nbAttr;
}

const void Card::print() {
    std::string str;
    for(int i = 0; i < m_nbAttr; i ++ ) {
        str += " " + Tools::intToString(m_attr.at((unsigned long)i));
    }
    std::cout << str << std::endl;
    Tools::writeInFile(str, false);

    return;
}

bool Card::isEqual(const Card &c) const {
    for(int i(0); i < m_nbAttr; i ++) {
        if (m_attr.at((unsigned int) i) != c.getAttr().at((unsigned int) i)) {
            return false;
        }
    }
    return true;
}

//###############################################

bool operator==(const Card &a, const Card &b) {
    return a.isEqual(b);
}
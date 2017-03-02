#include "Deck.h"
#include "Tools.h"
#include <tuple>
#include <fstream>

Deck::Deck(int nbAttr, int attrLength) : m_attrLength(attrLength), m_nbAttr(nbAttr)
{
    this->m_cards = new std::deque<Card>();
    std::deque<int> attr;

    for(int i = 0; i < m_nbAttr; i++) {
        attr.push_back(0);
    }

    initCards(m_nbAttr, m_attrLength, m_nbAttr, attr);

    m_nbCards = (int)m_cards->size();

}

Deck::~Deck()
{
    delete m_cards;
}

void Deck::initCards(int nbAttr, int attrLength, int nbIterations, std::deque<int> &attr) {

    if(nbIterations <= 0) {
        this->m_cards->push_back(Card(attr, nbAttr));
    } else {
        for(int i = 0; i < attrLength; i++) {
            attr.at(attr.size() - nbIterations) = i;
            initCards(nbAttr, attrLength, nbIterations - 1, attr);
        }
    }
    return;
}

const void Deck::print() {
    for (int i = 0; i < m_cards->size(); i++) {
        std::string str = Tools::intToString(i) + ".";
        std::cout << str;
        m_cards->at((unsigned long)i).print();
    }
    return;
}

const void Deck::print(std::deque<Card> &set) {
    for (int i = 0; i < set.size(); i++) {
        std::string str = Tools::intToString(i) + ".";
        std::cout << str;
        Tools::writeInFile(str, false);
        set.at((unsigned long)i).print();
    }
    return;
}

const void Deck::print(std::deque<int> &setPos) {
    for (int i = 0; i < setPos.size(); i++) {
        m_cards->at((unsigned long)setPos.at((unsigned long)i)).print();
    }
}

std::deque<std::deque<int>> Deck::findSetsInDeck() {
    std::deque<Card> set;
    std::deque<std::deque<int>> setList;
    for(int i = 0; i < m_cards->size() - 2; i++) {
        set.push_back((Card &&) getCardAt(i));
        for(int j = i + 1; j < m_cards->size() - 1; j++) {
            set.push_back((Card &&) getCardAt(j));
            for(int k = j + 1; k < m_cards->size(); k++) {
                set.push_back((Card &&) getCardAt(k));
                if(Deck::isSet(set, m_nbAttr)) {
                    std::deque<int> setPos;
                    setPos.push_back(i); setPos.push_back(j); setPos.push_back(k);
                    setList.push_back(setPos);
                }
                set.pop_back();
            }
            set.pop_back();
        }
        set.pop_back();
    }
    return setList;
}

/*
 * GETTER
 */

int Deck::getNbCards() {
    return this->m_nbCards;
}

int Deck::getNbAttr() {
    return this->m_nbAttr;
}

int Deck::getAttrLength() {
    return this->m_attrLength;
}

std::deque<Card>* Deck::getCards() {
    return this->m_cards;
}

bool Deck::isSet(std::deque<Card> &cards) {
    int i = 0;
    while(i < this->m_nbAttr) {
        if(!(allSame(cards, i)) && !(allDifferent(cards, i))) {
            return false;
        }
        i++;
    }
    return true;
}

bool Deck::isSet(std::deque<Card> &cards, int nbAttr) {
    int i = 0;
    while(i < nbAttr) {
        if(!(allSame(cards, i)) && !(allDifferent(cards, i))) {
            return false;
        }
        i++;
    }
    return true;
}

bool Deck::allSame(std::deque<Card> &cards, int index) {
    if(cards.at(1).getAttr().at((unsigned long)index) != cards.at(2).getAttr().at((unsigned long)index)) {
        return false;
    } else if (cards.at(1).getAttr().at((unsigned long)index) != cards.at(0).getAttr().at((unsigned long)index)) {
        return false;
    } else if ((cards.at(2).getAttr().at((unsigned long)index)) != cards.at(0).getAttr().at((unsigned long) index)) {
        return false;
    }
    return true;
}

bool Deck::allDifferent(std::deque<Card> &cards, int index) {
    if(cards.at(1).getAttr().at((unsigned long)index) == cards.at(2).getAttr().at((unsigned long)index)) {
        return false;
    } else if (cards.at(1).getAttr().at((unsigned long)index) == cards.at(0).getAttr().at((unsigned long)index)){
        return false;
    } else if (cards.at(2).getAttr().at((unsigned long)index) == cards.at(0).getAttr().at((unsigned long)index)) {
        return false;
    }
    return true;
}

Card Deck::removeCard(int index) {
    Card out = this->m_cards->at((unsigned long)index);
    this->m_cards->erase(m_cards->begin() + index);
    this->m_nbCards--;
    return out;
}

Card Deck::getCardAt(int i) {
    return this->m_cards->at((unsigned long)i);
}

std::tuple<Card, int> Deck::getRandCard() {
    unsigned long i = std::rand() % this->m_cards->size();
    return  std::make_tuple(this->m_cards->at(i), i);
}

void Deck::addCard(Card c) {
    this->m_cards->push_back(c);
}



//
// Created by firgaty on 21/02/17.
//

#include <tuple>
#include "Game.h"

Game::Game() {
    this->m_deck = new Deck(4, 3);
    this->m_roundCards = new std::deque<Card>();
    Tools::writeInFile("SET's TEST RESULTS :", true);
    reset();

    //m_rounds = round(m_rounds);
}

Game::Game(Deck *deck) {
    this->m_deck = deck;
    this->m_roundCards = new std::deque<Card>();
    Tools::writeInFile("SET's TEST RESULTS :", true);
    reset();
}

Game::Game(Deck *deck, int mode) {
    this->m_deck = deck;
    this->m_roundCards = new std::deque<Card>();
    reset();

    Tools::writeInFile("SET's TEST RESULTS :", true);

    if(mode == 1) { // Where we find all sets in the deck.
        std::deque<std::deque<int>> setList = m_deck->findSetsInDeck();
        for(int i = 0; i < setList.size(); i++) {
            std::cout << Tools::intToString(i) << std::endl;
            Tools::writeInFile(Tools::intToString(i), false);
            m_deck->print(setList.at((unsigned long)i));
        }
        return;
    }

    round(0);
    std::cout << "SETs found :" << std::endl;
    printTab(m_setFound, 10);
    std::cout << "SETs erased :" << std::endl;
    printTab(m_setErased, 10);
}

Game::~Game() {
    delete m_deck;
}

void Game::reset() {
    m_rounds = 0;

    int setFound[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int setErased[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    setSetFound(setFound);
    setSetErased(setErased);
}

int  Game::round(int lastRound) {
    m_rounds++;

    // 1) Deal.
    bool end(false);
    if(m_roundCards->size() < 12) {
        dealCards(12 - (int)m_roundCards->size());
    } else if (m_roundCards->size() % 3 > 3) { // if already 12 cards (or more) displayed, add 3 more.
        dealCards(3);
    } else { // if less than 3 cards left, stop.
        return lastRound;
    }

    printRoundCards();

    // 2) find sets.
    std::deque<std::deque<int>> setList = findSet();
    int cardsInRound = (int) this->m_roundCards->size();
    addFound(setList, cardsInRound);


    // 3) remove sets.
    addErased(this->removeSets(setList), cardsInRound);

    // Do it again.
    return round(lastRound + 1);
}

bool Game::dealCards(int nbCards) {
    if(nbCards < m_deck->getNbCards()) { // We check how many cards are left and see if they are sufficient.
        nbCards = m_deck->getNbCards();
    }

    if(nbCards == 0) return false; // if there are no mre cards return false

    for(int i = 0; i < nbCards; i++) {
        m_roundCards->push_back(m_deck->removeCard(std::get<1>(m_deck->getRandCard())));
        // add a random card from the deck and delete it from it.
    }

    return true;
}

std::deque<std::deque<int>> Game::findSet() {
    std::deque<Card> set;
    std::deque<std::deque<int>> setList;
    for(int i = 0; i < m_roundCards->size() - 2; i++) {
        set.push_back((Card &&) m_roundCards->at((unsigned long)i));
        for(int j = i + 1; j < m_roundCards->size() - 1; j++) {
            set.push_back((Card &&) m_roundCards->at((unsigned long)j));
            for(int k = j + 1; k < m_roundCards->size(); k++) {
                set.push_back((Card &&) m_roundCards->at((unsigned long)k));
                if(Deck::isSet(set, m_deck->getNbAttr())) {
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
    std::cout << "SETs found :" << std::endl;
    for(int i; i < setList.size(); i++) {
        printSet(setList.at(i));
    }
    return setList;
}

std::deque<std::deque<int>> Game::findSetsInDeck() {
    std::deque<Card> set;
    std::deque<std::deque<int>> setList;
    for(int i = 0; i < m_deck->getNbCards() - 2; i++) {
        set.push_back((Card &&) m_deck->getCardAt(i));
        for(int j = i + 1; j < m_deck->getNbCards() - 1; j++) {
            set.push_back((Card &&) m_deck->getCardAt(j));
            for(int k = j + 1; k < m_deck->getNbCards(); k++) {
                set.push_back((Card &&) m_deck->getCardAt(k));
                if(Deck::isSet(set, m_deck->getNbAttr())) {
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


bool Game::removeSet(std::deque<int> set) {
    for(int i = 0; i < set.size(); i++) {
        m_roundCards->erase(m_roundCards->begin() + set.at((unsigned long)i));
    }
    return false;
}

int Game::removeSets(std::deque<std::deque<int>> setList) {
    // Verifies if there are any 2 sets that share the same card.
    for(int i = 0; i < setList.size() - 1; i++) {
        for(int j = i + 1; j < setList.size(); j++) {
            bool same(false);
            for(int k = 0; k < setList.at((unsigned long)i).size(); k++) {
                if(setList.at((unsigned long)i).at((unsigned long)k) == setList.at((unsigned long)j).at((unsigned long)k)) same = true;
            }
            if(same){
                setList.erase(setList.begin() + i);

                // We make the iterator i go to the next set and reinitialize j.
                i++;
                j = i + 1;
                same = false;
            }
        }
    }

    int out(0);
    std::cout << "SETs erased :" << std::endl;

    for(int i(0); i < setList.size(); i++) {
        this->removeSet(setList.at(i));
        printSet(setList.at(i));
        out++;
    }
    return out;
}

void Game::setSetFound(int *setFound) {
    this->m_setFound = setFound;
}

void Game::setSetErased(int *setErased) {
    this->m_setErased = setErased;
}

void Game::addFound(std::deque<std::deque<int>> setList, int cardsInRound) {
    int index = cardsInRound / 3;
    for(int i(0); i < setList.size(); i++) {
        for(int j; j < setList.at(i).size(); j++) {
            this->m_setFound[index] += 1;
        }
    }
}

void Game::addErased(int nbSets, int cardsInRound) {
    this->m_setErased[cardsInRound / 3] += nbSets;

}

void Game::printTab(int *tab, int size) {
    for(int i(0); i < size; i++) {
        std::cout << "Pour " << Tools::intToString(i * 3) << " cartes : " << Tools::intToString(tab[i]) << "SETs" << std::endl;
    }
}

const void Game::printSet(std::deque<int> &setPos) {
    for (int i = 0; i < setPos.size(); i++) {
        m_roundCards->at((unsigned long)setPos.at((unsigned long)i)).print();
    }
}

const void Game::printRoundCards() {
    std::cout << "Round N." << Tools::intToString(m_rounds) << std::endl;
    for (int i = 0; i < this->m_roundCards->size(); i++) {
        std::string str = Tools::intToString(i) + ".";
        std::cout << str;
        m_roundCards->at((unsigned long)i).print();
    }
    return;
}


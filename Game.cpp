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
    }
}

Game::~Game() {
    delete m_deck;
}

void Game::reset() {
    m_rounds = 0;
    m_nbSet12 = 0;
    m_nbSet15 = 0;
}

int  Game::round(int lastRound) {
    m_rounds++;
    bool end(false);
    if(m_roundCards->size() < 12) {
        dealCards(12 - (int)m_roundCards->size());
    } else if (m_roundCards->size() % 3 > 3) {
        dealCards(3);
    } else {
        return lastRound;
    }

    std::deque<std::deque<int>> setList = findSet();



    return round(lastRound);
}

bool Game::dealCards(int nbCards) {
    if(nbCards < m_deck->getNbCards()) {
        nbCards = m_deck->getNbCards();
    }

    if(nbCards == 0) return false;

    for(int i = 0; i < nbCards; i++) {
        m_roundCards->push_back(m_deck->removeCard(std::get<1>(m_deck->getRandCard())));
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
            }
        }
    }

    // IN PROGRESS.
    return 0;
}


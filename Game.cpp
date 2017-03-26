//
// Created by firgaty on 21/02/17.
//

#include <tuple>
#include "Game.h"

Game::Game() {
    this->m_deck = new Deck(4, 3, false);
    this->m_roundCards = new Deck(4, 3, true);
    Tools::writeInFile("SET's TEST RESULTS :", true);
    reset();

    //m_rounds = round(m_rounds);
}

Game::Game(Deck *deck) {
    this->m_deck = deck;
    this->m_roundCards = new Deck(4, 3, true);
    Tools::writeInFile("SET's TEST RESULTS :", true);
    reset();
}

/**
 * @param deck
 * @param mode
 * 0 : Normal SET game with a dispay of the deck.
 * 1 : Finds all SETs in deck.
 * 2 : Tests how many cards at least are needed to have at least 1 set amongst them.
 */
Game::Game(Deck *deck, int mode) {
    this->m_deck = deck;
    this->m_roundCards = new Deck(4, 3, true);
    reset();

    Tools::writeInFile("SET's TEST RESULTS :", true);

    switch (mode) {
        case 1 : {
            std::deque<std::deque<int>> setList = m_deck->findSetsInDeck();
            for(int i = 0; i < setList.size(); i++) {
                std::cout << Tools::intToString(i) << std::endl;
                Tools::writeInFile(Tools::intToString(i), false);
                m_deck->print(setList.at((unsigned long)i));
            }
            return;
        }
        default:;
    }

    round(0);
    std::cout << "SETs found :" << std::endl;
    printDeque(*m_setFound);
    std::cout << "SETs erased :" << std::endl;
    printDeque(*m_setErased);
}

Game::~Game() {
    delete m_deck;
}

void Game::reset() {
    m_rounds = 0;

    std::deque<int> *setFound = new std::deque<int>(10, 0);
    std::deque<int> *setErased = new std::deque<int>(10, 0);
    std::deque<int> *nbRoundPerCards = new std::deque<int>(10, 0);

    setSetFound(setFound);
    setSetErased(setErased);
    setNbRoundPerCards(nbRoundPerCards);
}

int  Game::round(int lastRound) {
    m_rounds++;

    // 1) Deal.
    bool end(false);
    if(m_deck->getNbCards() == 3) {
        end = !dealCards(3);
    } else if(m_roundCards->getNbCards() < 12) {
        std::cout  << "\nDeal cards\n" << m_roundCards->getNbCards() << "\n" << 12 - m_roundCards->getNbCards() << std::endl;
        end = !dealCards(12 - m_roundCards->getNbCards()); // Deal cards crash
    } else if (m_roundCards->getNbCards() % 3 > 3) { // if already 12 cards (or more) displayed, add 3 more.
        end = !dealCards(3);
    } else if(m_deck->getNbCards() > 0) {
        end = !dealCards(3);
    } else { // if less than 3 cards left, stop.
        return lastRound;
    }
    if(end) return lastRound;


    printRoundCards();
    int cardsInRound =  this->m_roundCards->getNbCards();
    addNbRoundPerCards(cardsInRound);

    if(cardsInRound != 0) {}
    // 2) find sets.
    std::deque<std::deque<int>> setList = m_roundCards->findSetsInDeck();
    addFound(setList, cardsInRound);


    // 3) remove sets.
    addErased(this->removeSets(setList), cardsInRound);


    // Do it again.
    return round(lastRound + 1);
}

bool Game::dealCards(int nbCards) {
    if(nbCards > m_deck->getNbCards()) { // We check how many cards are left and see if they are sufficient.
        nbCards = m_deck->getNbCards();
    }

    if(nbCards == 0) return false; // if there are no mre cards return false

    for(int i = 0; i < nbCards; i++) {
        m_roundCards->addCard(m_deck->removeCard(std::get<1>(m_deck->getRandCard())));
        // add a random card from the deck and delete it from it.
    }

    return true;
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

int Game::removeSets(std::deque<std::deque<int>> setList) {
    // We get all the cards at the coordinates given by setList.
    std::cout << "\nRemove Sets\n";
    std::deque<std::deque<Card>> cardList;
    for(int i(0); (unsigned int)i < setList.size(); i ++) {
        std::deque<Card> set;
        for(int j(0); j < setList.at(i).size(); j ++) {
            set.push_back(m_roundCards->getCardAt(setList.at(i).at(j)));
        }
        cardList.push_back(set);
    }

    int out (0);
    // Check if the cards are still in the m_roundCards and erase them.q
    for(int i(0); i < cardList.size(); i++) {
        if(removeSet(cardList.at((unsigned int)i))) {
            std::cout << "Set in deck\n";
            out++;
        } else {
            std::cout << "Card not in deck\n";
        }

    }
    return out;
}

int Game::findSetsPerCards(int nbIteration, int nbCards, int foundSets) {
    for(int i(nbIteration); i < m_deck->getNbCards() - (nbCards - nbIteration); i++) {
        m_roundCards->addCard(m_deck->getCardAt(i));
        if(m_roundCards->getNbCards() == nbCards) {
            m_setFoundPerNbCards->at((unsigned int) nbCards) = (int) m_roundCards->findSetsInDeck().size();
            m_differentCards->at((unsigned int) nbCards) ++;

        }
        return findSetsPerCards(nbIteration + 1, nbCards, foundSets);
    }
    m_roundCards->removeCard(m_roundCards->getNbCards() - 1);
}

void Game::setSetFound(std::deque<int> *setFound) {
    this->m_setFound = setFound;
}

void Game::setSetErased(std::deque<int> *setErased) {
    this->m_setErased = setErased;
}
void Game::setNbRoundPerCards(std::deque<int> *nbRoundPerCards) {
    this->m_nbRoundPerCards = nbRoundPerCards;
}

void Game::addFound(std::deque<std::deque<int>> setList, int cardsInRound) {
    this->m_setFound->at((unsigned int) cardsInRound / 3) += setList.size();
}

void Game::addErased(int nbSets, int cardsInRound) {
    this->m_setErased->at((unsigned int) cardsInRound / 3) += nbSets;

}

void Game::addNbRoundPerCards(int cardsInRound) {
    this->m_nbRoundPerCards->at((unsigned int) cardsInRound / 3) += 1;
}

void Game::printTab(int *tab, int size) {
    for(int i(0); i < size; i++) {
        std::cout << "Pour " << Tools::intToString(i * 3) << " cartes : " << Tools::intToString(tab[i]) << " SETs" << std::endl;
    }
}

const void Game::printSet(std::deque<int> &setPos) {
    for (int i = 0; i < setPos.size(); i++) {
        m_roundCards->getCardAt(setPos.at(i)).print();
    }
}

const void Game::printRoundCards() {
    std::cout << "Round N." << Tools::intToString(m_rounds) << std::endl;
    for (int i = 0; i < this->m_roundCards->getNbCards(); i++) {
        std::string str = Tools::intToString(i) + ".";
        std::cout << str;
        m_roundCards->getCardAt(i).print();
    }
    return;
}

bool Game::removeSet(std::deque<Card> &set) {
    if(m_roundCards->isSetInDeck(set)) {
        for(int i (0); i < set.size(); i ++) {
            m_roundCards->removeCard(set.at((unsigned int)i));
        }
        return true;
    }
    return false;
}

void Game::printDeque(std::deque<int> &deque) {
    for(int i(0); i < deque.size(); i ++) {
        std::cout << "Pour " << Tools::intToString(i * 3) << " cartes : " << Tools::intToString(deque.at(i)) << " SETs" << std::endl;
    }
}

std::deque<int>* Game::getNbRoundPerCards() {
    return this->m_nbRoundPerCards;
}

std::deque<int>* Game::getSetErased() {
    return this->m_setErased;
}

std::deque<int>* Game::getSetFound() {
    return this->m_setFound;
}
std::deque<int>* Game::getDifferentCards() {
    return this->m_differentCards;
}
std::deque<int>* Game::getSetFoundPerNbCards() {
    return this->m_setFoundPerNbCards;
}

void Game::setDifferentCards(std::deque<int> *setter) {
    this->m_differentCards = setter;
}
void Game::setSetFoundPerNbCards(std::deque<int> *setter) {
    this->m_setFoundPerNbCards = setter;
}
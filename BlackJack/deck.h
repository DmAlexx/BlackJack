#ifndef DECK_H
#define DECK_H

#include <vector>
#include <memory>
#include "card.h"
#include <QString>
#include <map>
#include <algorithm>



class Deck
{
public:
    Deck();
    std::shared_ptr<Card> cardIssue();

private:
    std::vector<std::shared_ptr<Card>> m_deck;
    std::vector<int> m_cardsOnHands;
    void createDeck();
};

#endif // DECK_H

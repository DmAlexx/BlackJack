#include "deck.h"
#include <cstdlib>
#include <random>

namespace
{
const int NUMBER_OF_CARDS_IN_ISSUE = 1;
const int NUMBER_OF_CARDS_IN_SUIT = 13;
const int NUMBER_OF_SUITS = 4;
}

Deck::Deck()
{
    createDeck();
    for (int i= 0; i < 52; ++i)
    {
        m_cardsOnHands.push_back(i);
    }
    std::random_shuffle(m_cardsOnHands.begin(), m_cardsOnHands.end());
}

std::shared_ptr<Card> Deck::cardIssue()
{
    int tempCardNumber = 0;
    tempCardNumber = m_cardsOnHands.back();
    m_cardsOnHands.pop_back();
    return m_deck[tempCardNumber];
}

void Deck::createDeck()
{
    m_deck.reserve(52);
    int cardsCounter = 0;
    CardSuit tempCardSuit;
    CardValue tempCardValue;
    QString path;

    for (int i = 0; i < NUMBER_OF_SUITS; ++i)
    {
        for(auto& it : NUMBER_TO_CARD_SUIT)
        {
            if (i == it.first)
            {
                tempCardSuit = it.second;
                break;
            }
        }

        for (int j = 0; j < NUMBER_OF_CARDS_IN_SUIT; ++j)
        {
            m_deck.push_back(std::make_shared<Card>(tempCardSuit));
            for (auto& it : NUMBER_TO_CARD_VALUE)
            {
                if (j == it.first)
                {
                    tempCardValue = it.second;
                    m_deck.back()->setCardValue(tempCardValue);
                    break;
                }
            }
            for (const auto& it1 : numberToPath)
            {
                if (it1.first == cardsCounter)
                {
                        path = it1.second;
                        m_deck.back()->setPath(path);
                        ++cardsCounter;
                        break;
                }
            }
        }
    }
}

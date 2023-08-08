#include "dealer.h"

Dealer::Dealer()
{
    m_state = PlayerState::IN_GAME;
}

void Dealer::addCard(std::shared_ptr<Card> card)
{
    m_cardsOnHand.push_back(card);
}

int Dealer::getPointsOnHand()
{
    m_pointsOnHand = 0;
    for (int i = 0; i < m_cardsOnHand.size(); ++i)
    {
        m_pointsOnHand += m_cardsOnHand[i]->getCardPoint();
    }
    return m_pointsOnHand;

}

int Dealer::getPointsOnHandAfterIssue()
{
    return m_pointsOnHand = m_cardsOnHand.back()->getCardPoint();
}

void Dealer::discardingCard()
{
    while (!m_cardsOnHand.empty())
    {
        m_cardsOnHand.pop_back();
    }
}


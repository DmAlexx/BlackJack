#include "player.h"

namespace
{
    int START_CREDITS_ON_HAND = 1000;
}

Player::Player()
    : m_creditsOnHand(START_CREDITS_ON_HAND)
{
    m_playerState = PlayerState::IN_GAME;
}

void Player::addCard(std::shared_ptr<Card> card)
{
    m_cardsOnHand.push_back(card);
}

int Player::getPointsOnHand()
{
    m_pointsOnHand = 0;
    for (int i = 0; i < m_cardsOnHand.size(); ++i)
    {
        m_pointsOnHand += m_cardsOnHand[i]->getCardPoint();
    }
    return m_pointsOnHand;
}

void Player::setCreditsOnHand(int creditsToBet)
{
    m_creditsOnHand -= creditsToBet;
}

void Player::changePlayerState(PlayerState state)
{
    m_playerState = state;
}

void Player::discardingCard()
{
    while (!m_cardsOnHand.empty())
    {
        m_cardsOnHand.pop_back();
    }
}

void Player::increaseCreditsOnHand(int creditsInBank)
{
    m_creditsOnHand += creditsInBank;
}

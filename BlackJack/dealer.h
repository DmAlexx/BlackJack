#ifndef DEALER_H
#define DEALER_H

#include <memory>
#include "card.h"
#include <vector>
#include "player.h"

class Dealer
{
public:
    Dealer();
    void addCard(std::shared_ptr<Card> card);
    int getPointsOnHand();
    void setPointsOnHand(int pointsOnHand) {m_pointsOnHand = pointsOnHand;}
    int getNumberOfCardsOnHand() { return m_cardsOnHand.size(); }
    std::shared_ptr<Card> getLastCardOnHand() {return m_cardsOnHand.back();}
    std::shared_ptr<Card> getCardOnHand(int numberOfCard) {return m_cardsOnHand[numberOfCard];}
    TypeOfPlayer getTypeOfPlayer() { return TypeOfPlayer::DEALER; }
    int getPointsOnHandAfterIssue();
    void setPlayerState(PlayerState state) { m_state = state;}
    PlayerState getPlayerState () { return m_state ;}
    void discardingCard();

protected:
    int m_pointsOnHand = 0;
    std::vector<std::shared_ptr<Card>> m_cardsOnHand;
    PlayerState m_state;
};

#endif // DEALER_H

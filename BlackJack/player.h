#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "card.h"
#include <memory>
#include <map>

enum class TypeOfPlayer
{
    HUMAN,
    AI,
    DEALER
};

enum class PlayerState
{
    IN_GAME,
    LOSE,
    WAITING_RESULT,
    WINNER
};

class Player
{
public:
    Player();
    void addCard(std::shared_ptr<Card> card);
    int getPointsOnHand();
    int getCreditsOnHand() {return m_creditsOnHand;}
    void setCreditsOnHand(int creditsToBet);
    virtual TypeOfPlayer getTypeOfPlayer() = 0;
    std::vector<std::shared_ptr<Card>> getCardsOnHand() { return m_cardsOnHand; }
    std::shared_ptr<Card> getLastCardOnHand() {return m_cardsOnHand.back();}
    int getNumberOfCardsOnHand() { return m_cardsOnHand.size(); }
    void changePlayerState(PlayerState state);
    PlayerState getPlayerState() { return m_playerState; }
    void discardingCard();
    void increaseCreditsOnHand(int creditsInBank);

protected:
    int m_pointsOnHand = 0;
    int m_creditsOnHand = 0;
    std::vector<std::shared_ptr<Card>> m_cardsOnHand;
    PlayerState m_playerState;
};

class PlayerAI : public Player
{
    TypeOfPlayer getTypeOfPlayer() override { return TypeOfPlayer::AI; }
};

class PlayerHuman : public Player
{
    TypeOfPlayer getTypeOfPlayer() override { return TypeOfPlayer::HUMAN; }
};

#endif // PLAYER_H

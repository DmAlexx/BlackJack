#include "card.h"

Card::Card(CardSuit &cardSuit, CardValue cardValue, QString path, int cardPoint)
    : m_cardSuit(cardSuit),
    m_cardValue(cardValue),
    m_path(path)
{

}

void Card::setCardValue(CardValue &cardValue)
{
    m_cardValue = cardValue;
    for(auto& it : CARD_VALUE_TO_POINT)
    {
        if (it.first == cardValue)
        {
            m_cardPoint = it.second;
        }
    }
}

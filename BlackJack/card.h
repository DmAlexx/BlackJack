#ifndef CARD_H
#define CARD_H

#include <map>
#include <QString>



enum class CardSuit
{
    DIAMONDS = 0,
    HEARTS = 1,
    CLUBS = 2,
    SPADES = 3
};



enum class CardValue
{
    TWO = 2,
    THREE = 3,
    FOUR = 4,
    FIVE = 5,
    SIX = 6,
    SEVEN = 7,
    EIGHT = 8,
    NINE = 9,
    TEN = 10,
    JACK = 10,
    QUEEN = 10,
    KING = 10,
    ACE = 11
};

//extern std::map<CardSuit, std::map<CardValue, QString>> pathToCardValues1;
//extern std::map<CardSuit,std::map<CardValue, QString>> pathToCardValues2;

const std::map<CardValue, short int> CARD_VALUE_TO_POINT
{
    {CardValue::TWO, 2},
    {CardValue::THREE, 3},
    {CardValue::FOUR, 4},
    {CardValue::FIVE, 5},
    {CardValue::SIX, 6},
    {CardValue::SEVEN, 7},
    {CardValue::EIGHT, 8},
    {CardValue::NINE, 9},
    {CardValue::TEN, 10},
    {CardValue::JACK, 10},
    {CardValue::QUEEN, 10},
    {CardValue::KING, 10},
    {CardValue::ACE, 11}
};

const std::map<short int, CardSuit> NUMBER_TO_CARD_SUIT
{
     {0, CardSuit::DIAMONDS},
     {1, CardSuit::HEARTS},
     {2, CardSuit::CLUBS},
     {3, CardSuit::SPADES}
};

const std::map<short int, CardValue> NUMBER_TO_CARD_VALUE
{
    {0, CardValue::TWO},
    {1, CardValue::THREE},
    {2, CardValue::FOUR},
    {3, CardValue::FIVE},
    {4, CardValue::SIX},
    {5, CardValue::SEVEN},
    {6, CardValue::EIGHT},
    {7, CardValue::NINE},
    {8, CardValue::TEN},
    {9, CardValue::JACK},
    {10, CardValue::QUEEN},
    {11, CardValue::KING},
    {12, CardValue::ACE}
};

const std::map<int, QString> numberToPath
{

                             {0, ":/resources/cards_fonts/1/two_of_diamonds.png"},
                             {1, ":/resources/cards_fonts/1/three_of_diamonds.png"},
                             {2, ":/resources/cards_fonts/1/four_of_diamonds.png"},
                             {3, ":/resources/cards_fonts/1/five_of_diamonds.png"},
                             {4, ":/resources/cards_fonts/1/six_of_diamonds.png"},
                             {5, ":/resources/cards_fonts/1/seven_of_diamonds.png"},
                             {6, ":/resources/cards_fonts/1/eight_of_diamonds.png"},
                             {7, ":/resources/cards_fonts/1/nine_of_diamonds.png"},
                             {8, ":/resources/cards_fonts/1/ten_of_diamonds.png"},
                             {9, ":/resources/cards_fonts/1/jack_of_diamonds.png"},
                             {10, ":/resources/cards_fonts/1/queen_of_diamonds.png"},
                             {11, ":/resources/cards_fonts/1/king_of_diamonds.png"},
                             {12, ":/resources/cards_fonts/1/ace_of_diamonds.png"},
                               {13, ":/resources/cards_fonts/1/two_of_hearts.png"},
                               {14, ":/resources/cards_fonts/1/three_of_hearts.png"},
                               {15, ":/resources/cards_fonts/1/four_of_hearts.png"},
                               {16, ":/resources/cards_fonts/1/five_of_hearts.png"},
                               {17, ":/resources/cards_fonts/1/six_of_hearts.png"},
                               {18, ":/resources/cards_fonts/1/seven_of_hearts.png"},
                               {19, ":/resources/cards_fonts/1/eight_of_hearts.png"},
                               {20, ":/resources/cards_fonts/1/nine_of_hearts.png"},
                               {21, ":/resources/cards_fonts/1/ten_of_hearts.png"},
                               {22, ":/resources/cards_fonts/1/jack_of_hearts.png"},
                               {23, ":/resources/cards_fonts/1/queen_of_hearts.png"},
                               {24, ":/resources/cards_fonts/1/king_of_hearts.png"},
                               {25, ":/resources/cards_fonts/1/ace_of_hearts.png"},
                               {26, ":/resources/cards_fonts/1/two_of_clubs.png"},
                              {27, ":/resources/cards_fonts/1/three_of_clubs.png"},
                              {28, ":/resources/cards_fonts/1/four_of_clubs.png"},
                              {29, ":/resources/cards_fonts/1/five_of_clubs.png"},
                              {30, ":/resources/cards_fonts/1/six_of_clubs.png"},
                              {31, ":/resources/cards_fonts/1/seven_of_clubs.png"},
                              {32, ":/resources/cards_fonts/1/eight_of_clubs.png"},
                              {33, ":/resources/cards_fonts/1/nine_of_clubs.png"},
                              {34, ":/resources/cards_fonts/1/ten_of_clubs.png"},
                              {35, ":/resources/cards_fonts/1/jack_of_clubs.png"},
                              {36, ":/resources/cards_fonts/1/queen_of_clubs.png"},
                              {37, ":/resources/cards_fonts/1/king_of_clubs.png"},
    {38, ":/resources/cards_fonts/1/ace_of_clubs.png"},
                           {39, ":/resources/cards_fonts/1/two_of_spades.png"},
                           {40, ":/resources/cards_fonts/1/three_of_spades.png"},
                           {41, ":/resources/cards_fonts/1/four_of_spades.png"},
                           {42, ":/resources/cards_fonts/1/five_of_spades.png"},
                           {43, ":/resources/cards_fonts/1/six_of_spades.png"},
                           {44, ":/resources/cards_fonts/1/seven_of_spades.png"},
                           {45, ":/resources/cards_fonts/1/eight_of_spades.png"},
                           {46, ":/resources/cards_fonts/1/nine_of_spades.png"},
                           {47, ":/resources/cards_fonts/1/ten_of_spades.png"},
                           {48, ":/resources/cards_fonts/1/jack_of_spades.png"},
                           {49, ":/resources/cards_fonts/1/queen_of_spades.png"},
                           {50, ":/resources/cards_fonts/1/king_of_spades.png"},
                           {51, ":/resources/cards_fonts/1/ace_of_spades.png"}
};

class Card
{
public:
    Card() = default;
    Card(CardSuit& cardSuit, CardValue cardValue = CardValue::TWO, QString path = "", int cardPoint = 0);
    void setCardValue(CardValue& cardValue);
    void setPath(QString path) {m_path = path;}
    CardSuit& getCardSuit() {return m_cardSuit;}
    CardValue& getCardValue() {return m_cardValue;}
    int getCardPoint() {return m_cardPoint;}
    void setCardPoint(int cardPoint) {m_cardPoint = cardPoint;}
    QString getPathToCardSuit() { return m_path; }

private:
    CardSuit m_cardSuit;
    CardValue m_cardValue;
    QString m_path;
    short int m_cardPoint = 0; // 2 - 10 = 2 - 10, "Jack" - 10 , "Queen" - 10, "King" - 10, "Ace" - 11 - default;
};

#endif // CARD_H

#ifndef GAME_H
#define GAME_H

#include "deck.h"
#include "player.h"
#include "dealer.h"
#include <memory>
#include <vector>
#include "rectangle.h"
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <QMessageBox>
#include <QGraphicsProxyWidget>
#include <QApplication>

struct Coordinates
{
    int x = 0;
    int y = 0;
};

class Game
{
public:
    Game(std::shared_ptr<int> gameSwitcher);
    std::vector<std::shared_ptr<Player>> getPlayer() { return m_players; }
    void startTheGame();
    void setScene(std::shared_ptr<QGraphicsScene> scene); //{ m_scene = scene; }
    void checkResult();
    void moving_ai();
    void betForAi();
    void hitTheCard(TypeOfPlayer humanOrAi);
    void humanStateInfo();
    void winnerDefinition();
    void showDealerCards();
    void betMessageInfo();
    void newLoop();
    void changeCreditsInBank(int credits);
    void setLastHumanBet(int bet);

private:
    std::vector<std::shared_ptr<Deck>> m_deck;
    std::vector<std::shared_ptr<Player>> m_players;
    std::shared_ptr<Dealer> m_dealer;
    std::vector<std::shared_ptr<QGraphicsItemAnimation>> m_animation;
    std::vector<std::shared_ptr<Rectangle>> m_rect;
    std::shared_ptr<QGraphicsScene> m_scene = nullptr;
    void firstDealOfCards();
    void animation(Coordinates& coord);
    void showCard(QString path);
    void textOnScene();
    void setSceneTextStyle(std::shared_ptr<QGraphicsTextItem> textItem, QString text, int x, int y);
    void showMessageBox(QString winnerText);
    std::shared_ptr<QGraphicsTextItem> m_humanNameText = nullptr;
    std::shared_ptr<QGraphicsTextItem> m_humanInfoText = nullptr;
    std::shared_ptr<QGraphicsTextItem> m_humanInfoPointsText = nullptr;
    std::shared_ptr<QGraphicsTextItem> m_aiNameText = nullptr;
    std::shared_ptr<QGraphicsTextItem> m_aiInfoText = nullptr;
    std::shared_ptr<QGraphicsTextItem> m_aiInfoPointsText = nullptr;
    std::shared_ptr<QGraphicsTextItem> m_dealerNameText = nullptr;
    std::shared_ptr<QGraphicsTextItem> m_dealerInfoText = nullptr;
    std::shared_ptr<QGraphicsTextItem> m_dealerInfoPointsText = nullptr;
    std::shared_ptr<QGraphicsTextItem> m_resultHumanInfoText = nullptr;
    std::shared_ptr<QGraphicsTextItem> m_resultAiInfoText = nullptr;
    std::shared_ptr<QGraphicsTextItem> m_stateHumanInfoText = nullptr;
    std::shared_ptr<QGraphicsTextItem> m_stateAiInfoText = nullptr;
    std::shared_ptr<QGraphicsTextItem> m_creditsHumanInfo = nullptr;
    std::shared_ptr<QGraphicsTextItem> m_creditsAiInfo = nullptr;
    std::shared_ptr<int> m_gameSwitcher = nullptr;
    int m_creditsInBank = 0;
    int m_lastHumanBet = 0;
    int m_lastAiBet = 0;

};

#endif // GAME_H

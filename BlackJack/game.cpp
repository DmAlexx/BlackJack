#include "game.h"

namespace
{
    const int NUMBER_OF_CARDS_ON_HAND_IN_START = 0;
    const int NUMBER_OF_CARDS_ON_HAND_AFTER_ISSUE = 2;
    const int COORDINATES_FOR_HUMAN_X = 0;
    const int COORDINATES_FOR_HUMAN_AI_Y = 450;
    const int COORDINATES_FOR_AI_X = 475;
    const int COORDINATES_FOR_DEALER_X = 375;
    const int COORDINATES_FOR_DEALER_Y = 0;
}

Game::Game(std::shared_ptr<int> gameSwitcher)
    : m_gameSwitcher(gameSwitcher)
{
    m_players.reserve(2);
    m_players.push_back(std::make_shared<PlayerHuman>());
    m_players.push_back(std::make_shared<PlayerAI>());
    m_deck.push_back(std::make_shared<Deck>());
    m_dealer = std::make_shared<Dealer>();
    m_resultHumanInfoText = std::make_shared<QGraphicsTextItem>();
    m_resultAiInfoText = std::make_shared<QGraphicsTextItem>();
}

void Game::startTheGame()
{
    firstDealOfCards();
    textOnScene();
}

void Game::setScene(std::shared_ptr<QGraphicsScene> scene)
{
    m_scene = scene;
}

void Game::checkResult()
{

    for (auto& it : m_players)
    {
        if (it->getPointsOnHand() > 21)
        {
            if (it->getTypeOfPlayer() == TypeOfPlayer::HUMAN && m_players[0]->getPlayerState() != PlayerState::LOSE)
            {
                m_players[0]->changePlayerState(PlayerState::LOSE);
                setSceneTextStyle(m_resultHumanInfoText, "YOU LOSE!", 5, 450);
                moving_ai();
            }
            else if (it->getTypeOfPlayer() == TypeOfPlayer::AI && m_players[1]->getPlayerState() != PlayerState::LOSE)
            {
                m_players[1]->changePlayerState(PlayerState::LOSE);
                setSceneTextStyle(m_resultAiInfoText, "YOU LOSE!", 450, 450);
                showDealerCards();
            }
        }
    }
}

void Game::betForAi()
{
    int betSwitcher = 0;
    betSwitcher = rand() % 5;
    QString creditsText;

    switch (betSwitcher)
    {
    case 0:
        m_lastAiBet = 5;
        break;

    case 1:
        m_lastAiBet = 10;
        break;

    case 2:
        m_lastAiBet = 25;
        break;

    case 3:
        m_lastAiBet = 50;
        break;

    case 4:
        m_lastAiBet = 100;
        break;
    }

    if (m_lastAiBet > m_players[1]->getCreditsOnHand())
    {
        setSceneTextStyle(m_creditsAiInfo, "not enough credits", 580, 650);
    }
    else
    {
        m_players[1]->setCreditsOnHand(m_lastAiBet);
        changeCreditsInBank(m_lastAiBet);
        creditsText = QString::number(m_players[1]->getCreditsOnHand());
        setSceneTextStyle(m_creditsAiInfo, creditsText + "$", 580, 650);
    }
}

void Game::moving_ai()
{
    int loopCounter = 0;
    int standOrHit = 0;
    loopCounter = rand() % 2 + 1;

    betForAi();

    for (int i=0; i < loopCounter; ++i)
    {
        standOrHit = rand() % 2;
        if (standOrHit == 0 && m_players[1]->getPlayerState() == PlayerState::IN_GAME)
        {
            hitTheCard(TypeOfPlayer::AI);
            checkResult();
        }
        else
        {
            if (m_players[1]->getPlayerState() != PlayerState::WAITING_RESULT && m_players[1]->getPlayerState() != PlayerState::LOSE)
            {
                m_players[1]->changePlayerState(PlayerState::WAITING_RESULT);
                m_stateAiInfoText = std::make_shared<QGraphicsTextItem>();
                setSceneTextStyle(m_stateAiInfoText, "STAND!", 450, 650);
                showDealerCards();
            }
            break;
        }
    }
    if (m_players[1]->getPlayerState() != PlayerState::WAITING_RESULT && m_players[1]->getPlayerState() != PlayerState::LOSE)
    {
        m_players[1]->changePlayerState(PlayerState::WAITING_RESULT);
        m_stateAiInfoText = std::make_shared<QGraphicsTextItem>();
        setSceneTextStyle(m_stateAiInfoText, "STAND!", 450, 650);
        showDealerCards();
    }
    winnerDefinition();
}

void Game::hitTheCard(TypeOfPlayer humanOrAi)
{
        Coordinates coord;
        if (humanOrAi == TypeOfPlayer::HUMAN)
        {
            m_players[0]->addCard(m_deck.back()->cardIssue());
            m_rect.push_back(std::make_shared<Rectangle>((":/resources/cards_fonts/1/suit.png"), m_players[0]->getTypeOfPlayer()));
            m_scene->addItem(m_rect.back().get());
            coord.x = m_players[0]->getNumberOfCardsOnHand() * 40;
            coord.y = COORDINATES_FOR_HUMAN_AI_Y;
            animation(coord);
            showCard(m_players[0]->getLastCardOnHand()->getPathToCardSuit());
            setSceneTextStyle(m_humanInfoPointsText, QString::number(m_players[0]->getPointsOnHand()), 5, 600);
        }
        else if (humanOrAi == TypeOfPlayer::AI)
        {
            m_players[1]->addCard(m_deck.back()->cardIssue());
            m_rect.push_back(std::make_shared<Rectangle>((":/resources/cards_fonts/1/suit.png"), m_players[1]->getTypeOfPlayer()));
            m_scene->addItem(m_rect.back().get());
            coord.x = COORDINATES_FOR_AI_X + m_players[1]->getNumberOfCardsOnHand() * 40;
            coord.y = COORDINATES_FOR_HUMAN_AI_Y;
            animation(coord);
            showCard(m_players[1]->getLastCardOnHand()->getPathToCardSuit());
            setSceneTextStyle(m_aiInfoPointsText, QString::number(m_players[1]->getPointsOnHand()), 450, 600);
        }
}

void Game::humanStateInfo()
{
    m_stateHumanInfoText = std::make_shared<QGraphicsTextItem>();
    setSceneTextStyle(m_stateHumanInfoText, "STAND!", 5, 650);
}

void Game::winnerDefinition()
{
    QString creditsText;
    if ((m_players[0]->getPlayerState() == PlayerState::LOSE && (21 - m_players[1]->getPointsOnHand()) < (21 - m_dealer->getPointsOnHand()) && m_players[1]->getPlayerState() != PlayerState::LOSE)
        || ((21 - m_players[1]->getPointsOnHand()) < (21 - m_players[0]->getPointsOnHand()) && (21 - m_players[1]->getPointsOnHand()) < (21 - m_dealer->getPointsOnHand())) && m_players[1]->getPlayerState() != PlayerState::LOSE)
    {
        m_players[1]->changePlayerState(PlayerState::WINNER);
        m_players[1]->increaseCreditsOnHand(m_creditsInBank);
        creditsText = QString::number(m_players[1]->getCreditsOnHand());
        setSceneTextStyle(m_creditsAiInfo, creditsText + "$", 580, 650);
        showMessageBox("AI is a winner");
        //ai winner
    }
    else if ((m_players[1]->getPlayerState() == PlayerState::LOSE && (21 - m_players[0]->getPointsOnHand()) < (21 - m_dealer->getPointsOnHand()) && m_players[0]->getPlayerState() != PlayerState::LOSE)
        || ((21 - m_players[0]->getPointsOnHand()) < (21 - m_players[1]->getPointsOnHand()) && (21 - m_players[0]->getPointsOnHand()) < (21 - m_dealer->getPointsOnHand())) && m_players[0]->getPlayerState() != PlayerState::LOSE)
    {
        m_players[0]->changePlayerState(PlayerState::WINNER);
        m_players[0]->increaseCreditsOnHand(m_creditsInBank);
        creditsText = QString::number(m_players[0]->getCreditsOnHand());
        setSceneTextStyle(m_creditsHumanInfo, creditsText + "$", 105, 650);
        showMessageBox("Human is a winner");
        //human winner
    }
    else if ((21 - m_players[0]->getPointsOnHand()) == (21 - m_dealer->getPointsOnHand()) && (21 - m_players[1]->getPointsOnHand()) == (21 - m_dealer->getPointsOnHand()))
    {
        m_players[0]->changePlayerState(PlayerState::WINNER);
        m_players[0]->increaseCreditsOnHand(m_lastHumanBet);
        m_players[1]->changePlayerState(PlayerState::WINNER);
        m_players[1]->increaseCreditsOnHand(m_lastAiBet);
        m_dealer->setPlayerState(PlayerState::WINNER);
        creditsText = QString::number(m_players[0]->getCreditsOnHand());
        setSceneTextStyle(m_creditsHumanInfo, creditsText + "$", 105, 650);
        creditsText = QString::number(m_players[1]->getCreditsOnHand());
        setSceneTextStyle(m_creditsAiInfo, creditsText + "$", 580, 650);

        showMessageBox("Draw");
        //draw
    }
    else if (((21 - m_players[0]->getPointsOnHand()) < (21 - m_players[1]->getPointsOnHand()) && (21 - m_players[0]->getPointsOnHand()) == (21 - m_dealer->getPointsOnHand()))
        || ((21 - m_players[0]->getPointsOnHand()) == (21 - m_dealer->getPointsOnHand()) && (m_players[1]->getPlayerState() == PlayerState::LOSE)))
    {
        // winner human, dealer
        m_players[0]->changePlayerState(PlayerState::WINNER);
        m_players[0]->increaseCreditsOnHand(m_creditsInBank);
        m_dealer->setPlayerState(PlayerState::WINNER);
        showMessageBox("Human and Dealer are winners");
        creditsText = QString::number(m_players[0]->getCreditsOnHand());
        setSceneTextStyle(m_creditsHumanInfo, creditsText + "$", 105, 650);
    }
    else if ((21 - m_players[0]->getPointsOnHand()) == (21 - m_players[1]->getPointsOnHand()) && (21 - m_players[0]->getPointsOnHand()) < (21 - m_dealer->getPointsOnHand()) && (m_players[1]->getPlayerState() != PlayerState::LOSE))
    {
        // winner human, winner ai
        m_players[0]->changePlayerState(PlayerState::WINNER);
        m_players[0]->increaseCreditsOnHand(m_lastHumanBet);
        m_players[1]->changePlayerState(PlayerState::WINNER);
        m_players[1]->increaseCreditsOnHand(m_lastAiBet);
        creditsText = QString::number(m_players[0]->getCreditsOnHand());
        setSceneTextStyle(m_creditsHumanInfo, creditsText + "$", 105, 650);
        creditsText = QString::number(m_players[1]->getCreditsOnHand());
        setSceneTextStyle(m_creditsAiInfo, creditsText + "$", 580, 650);
        showMessageBox("Human and AI are winners");
    }
    else if(((21 - m_players[1]->getPointsOnHand()) < (21 - m_players[0]->getPointsOnHand()) && (21 - m_players[1]->getPointsOnHand()) == (21 - m_dealer->getPointsOnHand()))
        || ((21 - m_players[1]->getPointsOnHand()) == (21 - m_dealer->getPointsOnHand()) && (m_players[0]->getPlayerState() == PlayerState::LOSE)))
    {
    // winner ai, winner dealer
        m_dealer->setPlayerState(PlayerState::WINNER);
        m_players[1]->changePlayerState(PlayerState::WINNER);
        m_players[1]->increaseCreditsOnHand(m_creditsInBank);
        creditsText = QString::number(m_players[1]->getCreditsOnHand());
        setSceneTextStyle(m_creditsAiInfo, creditsText + "$", 580, 650);
        showMessageBox("AI and Dealer are winners");
    }
    else
    {
        //winner dealer
        m_dealer->setPlayerState(PlayerState::WINNER);
        showMessageBox("Dealer is a winner");
    }
}

void Game::showDealerCards()
{
    Coordinates coord;
    for (int i = 0; i < m_rect.size(); ++i)
    {
        if (m_rect[i]->getPlayerType() == TypeOfPlayer::DEALER)
        {
            m_rect.erase(m_rect.begin() + i);
        }
    }

    for (int i = 0; i < NUMBER_OF_CARDS_ON_HAND_AFTER_ISSUE; ++i)
    {
        m_rect.push_back(std::make_shared<Rectangle>((":/resources/cards_fonts/1/suit.png"), m_dealer->getTypeOfPlayer()));
        m_scene->addItem(m_rect.back().get());
        coord.x = 50 + i * 40 + COORDINATES_FOR_DEALER_X;
        coord.y = COORDINATES_FOR_DEALER_Y;
        m_rect.back()->setPos(coord.x, coord.y);
        showCard(m_dealer->getCardOnHand(i)->getPathToCardSuit());
    }
    setSceneTextStyle(m_dealerInfoPointsText, QString::number(m_dealer->getPointsOnHand()), 380, 150);
}

void Game::betMessageInfo()
{
    setSceneTextStyle(m_creditsHumanInfo, "not enough credits", 105, 650);
}

void Game::showMessageBox(QString winnerText)
{
    std::shared_ptr<QMessageBox> messageBox = std::make_shared<QMessageBox>();
    messageBox->setText(winnerText);
    messageBox->setStandardButtons(QMessageBox::Ok);
    int clickedButton = messageBox->exec();
    if (clickedButton == QMessageBox::Ok)
    {
        newLoop();
    }
}

void Game::newLoop()
{
    for (int i = 0; i < m_rect.size(); ++i)
    {
        m_scene->removeItem(m_rect[i].get());
    }
    for (int i = 0; i < m_players.size(); ++i)
    {
        m_players[i]->discardingCard();
        m_players[i]->changePlayerState(PlayerState::IN_GAME);
    }
    m_dealer->discardingCard();
    m_dealer->setPlayerState(PlayerState::IN_GAME);
    while (!m_animation.empty())
    {
        m_animation.pop_back();
    }
    while (!m_rect.empty())
    {
        m_rect.pop_back();
    }

    m_scene->removeItem(m_humanInfoText.get());
    m_scene->removeItem(m_humanInfoPointsText.get());
    m_scene->removeItem(m_aiInfoText.get());
    m_scene->removeItem(m_aiInfoPointsText.get());
    m_scene->removeItem(m_dealerInfoText.get());
    m_scene->removeItem(m_dealerInfoPointsText.get());
    m_scene->removeItem(m_resultHumanInfoText.get());
    m_scene->removeItem(m_resultAiInfoText.get());
    m_scene->removeItem(m_stateAiInfoText.get());
    m_scene->removeItem(m_stateHumanInfoText.get());
    m_deck.push_back(std::make_shared<Deck>());
    *m_gameSwitcher = 0;
    m_creditsInBank = 0;
}

void Game::changeCreditsInBank(int credits)
{
    m_creditsInBank += credits;
}

void Game::setLastHumanBet(int bet)
{
    m_lastHumanBet = bet;
}

void Game::firstDealOfCards()
{
    Coordinates coord;
    for (int i = 0; i < m_players.size(); ++i)
    {
        for (int j = 0; j < NUMBER_OF_CARDS_ON_HAND_AFTER_ISSUE; ++j)
        {
            m_players[i]->addCard(m_deck.back()->cardIssue());
            m_rect.push_back(std::make_shared<Rectangle>((":/resources/cards_fonts/1/suit.png"), m_players[i]->getTypeOfPlayer()));
            m_scene->addItem(m_rect.back().get());
            coord.x = 50 + i * COORDINATES_FOR_AI_X  + j * 40;
            coord.y = COORDINATES_FOR_HUMAN_AI_Y;
            animation(coord);
            showCard(m_players[i]->getLastCardOnHand()->getPathToCardSuit());
        }
    }

    for (int i = 0; i < NUMBER_OF_CARDS_ON_HAND_AFTER_ISSUE; ++i)
    {
        m_dealer->addCard(m_deck.back()->cardIssue());
        m_rect.push_back(std::make_shared<Rectangle>((":/resources/cards_fonts/1/suit.png"), m_dealer->getTypeOfPlayer()));
        m_scene->addItem(m_rect.back().get());
        coord.x = 50 + i * 40 + COORDINATES_FOR_DEALER_X;
        coord.y = COORDINATES_FOR_DEALER_Y;
        animation(coord);
        if (i != 0)
        {
            showCard(m_dealer->getLastCardOnHand()->getPathToCardSuit());
        }
    }
}

void Game::animation(Coordinates& coord)
{
    m_animation.push_back(std::make_shared<QGraphicsItemAnimation>());
    m_animation.back()->setItem(m_rect.back().get());
    m_animation.back()->setTimeLine(new QTimeLine(350));
    m_animation.back()->setPosAt(0, QPointF(0, 0));
    m_animation.back()->setPosAt(1, QPointF(coord.x, coord.y));
    m_animation.back()->timeLine()->start();
}

void Game::showCard(QString path)
{
    m_rect.back()->setNewPath(path);
    m_scene->addItem(m_rect.back().get());
}

void Game::textOnScene()
{
    m_humanNameText = std::make_shared<QGraphicsTextItem>();
    m_humanInfoText = std::make_shared<QGraphicsTextItem>();
    m_humanInfoPointsText = std::make_shared<QGraphicsTextItem>();
    m_aiNameText = std::make_shared<QGraphicsTextItem>();
    m_aiInfoText = std::make_shared<QGraphicsTextItem>();
    m_aiInfoPointsText = std::make_shared<QGraphicsTextItem>();
    m_dealerNameText = std::make_shared<QGraphicsTextItem>();
    m_dealerInfoText = std::make_shared<QGraphicsTextItem>();
    m_dealerInfoPointsText = std::make_shared<QGraphicsTextItem>();
    m_creditsHumanInfo = std::make_shared<QGraphicsTextItem>();
    m_creditsAiInfo = std::make_shared<QGraphicsTextItem>();

    setSceneTextStyle(m_humanNameText, "Human", 5, 500);
    setSceneTextStyle(m_humanInfoText, "points", 5, 550);
    setSceneTextStyle(m_humanInfoPointsText, QString::number(m_players[0]->getPointsOnHand()), 5, 600);
    QString creditsText = QString::number(m_players[0]->getCreditsOnHand());
    setSceneTextStyle(m_creditsHumanInfo, creditsText + "$", 105, 650);

    setSceneTextStyle(m_aiNameText, "AI", 450, 500);
    setSceneTextStyle(m_aiInfoText, "points", 450, 550);
    setSceneTextStyle(m_aiInfoPointsText, QString::number(m_players[1]->getPointsOnHand()), 450, 600);
    creditsText = QString::number(m_players[1]->getCreditsOnHand());
    setSceneTextStyle(m_creditsAiInfo, creditsText + "$", 580, 650);

    setSceneTextStyle(m_dealerNameText, "Dealer", 380, 50);
    setSceneTextStyle(m_dealerInfoText, "points", 380, 100);
    setSceneTextStyle(m_dealerInfoPointsText, QString::number(m_dealer->getPointsOnHandAfterIssue()), 380, 150);
}

void Game::setSceneTextStyle(std::shared_ptr<QGraphicsTextItem> textItem, QString text, int x, int y)
{
    textItem->setPlainText(text);
    textItem->setPos(x,y);
    QFont font("Segoe UI", 22);
    textItem->setFont(font);
    textItem->setDefaultTextColor(QColor(255, 255, 255));
    m_scene->addItem(textItem.get());
}

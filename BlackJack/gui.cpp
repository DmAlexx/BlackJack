#include "gui.h"
#include "./ui_gui.h"

namespace
{
    int START_CREDITS_ON_HAND = 1000;
}

GUI::GUI(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::GUI)
    , m_creditsOnHand(START_CREDITS_ON_HAND)
{
    m_ui->setupUi(this);
    m_view = m_ui->graphicsView;
    setInterfaceStyle();
    m_gameSwitcher = std::make_shared<int>(0);
    m_game = std::make_shared<Game>(m_gameSwitcher);
    m_game->setScene(m_scene);
}

GUI::~GUI()
{
    delete m_ui;
    delete m_view;
}

void GUI::setInterfaceStyle()
{

    this->setStyleSheet(StyleHelper::getMainWindowBackGrnd());
    m_scene = std::make_shared<QGraphicsScene>();
    m_scene->setSceneRect(0, 0, 1083, 778);
    m_scene->setBackgroundBrush(QColor::fromRgb(0,135,0));

    //m_scene->addItem(m_rect);
    m_view->setScene(m_scene.get());
    m_view->show();

    m_ui->BET5->setStyleSheet(StyleHelper::getStartRadioButtonStyle());
    m_ui->BET10->setStyleSheet(StyleHelper::getStartRadioButtonStyle());
    m_ui->BET25->setStyleSheet(StyleHelper::getStartRadioButtonStyle());
    m_ui->BET50->setStyleSheet(StyleHelper::getStartRadioButtonStyle());
    m_ui->BET100->setStyleSheet(StyleHelper::getStartRadioButtonStyle());

    m_ui->pushButton_deal->setStyleSheet(StyleHelper::getStartButtonsKeyStyle());
    m_ui->pushButton_hit->setStyleSheet(StyleHelper::getStartButtonsKeyStyle());
    m_ui->pushButton_stand->setStyleSheet(StyleHelper::getStartButtonsKeyStyle());

    m_ui->groupBox->setStyleSheet("QGroupBox { border: 0; }");
    m_ui->groupBox_2->setStyleSheet("QGroupBox { border: 0; }");

    addBlackJackTitle();
    addChipsTitle();

    m_ui->BET5->setChecked(true);
    if (m_ui->BET5->isChecked())
    {
        changePixmapForBet(":/resources/images/RedChipCropped5.png");
        m_creditForBet = 5;
    }
}

void GUI::changePixmapForBet(QString path)
{
    QPixmap pixmap(path);
    pixmap.scaled(QSize(75, 75), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    m_ui->label->setPixmap(pixmap);
}

void GUI::addBlackJackTitle()
{
    QPixmap pixmap(":/resources/images/blackjack_title.png");
    m_ui->bj_title->setPixmap(pixmap);
}

void GUI::addChipsTitle()
{
    QPixmap pixmap(":/resources/images/chips_title.png");
    m_ui->chips_title->setPixmap(pixmap);
}



void GUI::on_BET5_clicked(bool checked)
{
    if (m_ui->BET5->isChecked())
    {
        changePixmapForBet(":/resources/images/RedChipCropped5.png");
        m_creditForBet = 5;
    }
}

void GUI::on_BET10_clicked(bool checked)
{
    if (m_ui->BET10->isChecked())
    {
        changePixmapForBet(":/resources/images/BlueChipCropped10.png");
        m_creditForBet = 10;
    }
}

void GUI::on_BET25_clicked(bool checked)
{
    if (m_ui->BET25->isChecked())
    {
        changePixmapForBet(":/resources/images/GreenChipCropped25.png");
        m_creditForBet = 25;
    }
}

void GUI::on_BET50_clicked(bool checked)
{
    if (m_ui->BET50->isChecked())
    {
        changePixmapForBet(":/resources/images/OrangeChipCropped50.png");
        m_creditForBet = 50;
    }
}

void GUI::on_BET100_clicked(bool checked)
{
    if (m_ui->BET100->isChecked())
    {
        changePixmapForBet(":/resources/images/BlackChipCropped100.png");
        m_creditForBet = 100;
    }
}

void GUI::on_pushButton_deal_clicked()
{
    if (*m_gameSwitcher == 0)
    {
        if (m_creditForBet > m_game->getPlayer()[0]->getCreditsOnHand())
        {
            m_game->betMessageInfo();
        }
        else
        {
            m_game->getPlayer()[0]->setCreditsOnHand(m_creditForBet);
            m_game->changeCreditsInBank(m_creditForBet);
            m_game->setLastHumanBet(m_creditForBet);
            m_game->startTheGame();
            *m_gameSwitcher = 1;
        }
    }
}

void GUI::on_pushButton_hit_clicked()
{
    if (m_game->getPlayer()[0]->getPlayerState() != PlayerState::IN_GAME && *m_gameSwitcher == 1)
    {
        return;
    }
    else if(m_game->getPlayer()[0]->getPlayerState() == PlayerState::IN_GAME && *m_gameSwitcher == 1)
    {
        m_game->hitTheCard(TypeOfPlayer::HUMAN);
        m_game->checkResult();
    }
}

void GUI::on_pushButton_stand_clicked()
{
    if (m_game->getPlayer()[0]->getPlayerState() == PlayerState::LOSE && *m_gameSwitcher == 1)
    {
        return;
    }
    else if(m_game->getPlayer()[0]->getPlayerState() == PlayerState::IN_GAME && *m_gameSwitcher == 1)
    {
        m_game->humanStateInfo();
        m_game->getPlayer()[0]->changePlayerState(PlayerState::WAITING_RESULT);
        m_game->moving_ai();
    }
}

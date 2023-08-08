#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QBrush>

#include "stylehelper.h"
#include "rectangle.h"
#include "game.h"
#include <memory>
#include <vector>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class GUI; }
QT_END_NAMESPACE

class GUI : public QMainWindow
{
    Q_OBJECT

public:
    GUI(QWidget *parent = nullptr);
    ~GUI();

private slots:
    void on_pushButton_deal_clicked();
    void on_pushButton_hit_clicked();
    void on_pushButton_stand_clicked();

    void on_BET5_clicked(bool checked);
    void on_BET10_clicked(bool checked);
    void on_BET25_clicked(bool checked);
    void on_BET50_clicked(bool checked);
    void on_BET100_clicked(bool checked);

private:
    void setInterfaceStyle();
    void changePixmapForBet(QString path);
    void addBlackJackTitle();
    void addChipsTitle();

    Ui::GUI *m_ui;
    std::shared_ptr<QGraphicsScene> m_scene = nullptr;
    QGraphicsView* m_view = nullptr;
    int m_creditForBet = 0;
    std::vector<std::shared_ptr<Player>> m_players;
    std::shared_ptr<Game> m_game;
    int m_creditsOnHand = 0;
    QString text_Credits;
    std::shared_ptr<int> m_gameSwitcher = nullptr;
};
#endif // GUI_H

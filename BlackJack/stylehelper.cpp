#include "stylehelper.h"

QString StyleHelper::getMainWindowBackGrnd()
{
    return "QMainWindow {"
           "background-image: url(:/resources/images/bg.png);"
           "}";
}

QString StyleHelper::getStartButtonsKeyStyle()
{
    return "QPushButton{"
        "color:white;"
        "}"

           "QPushButton{"
           "font: 16pt 'Segoe UI';"
           "}"

        "QPushButton{"
           "border:none;"
           "border-radius:4px;"
           "background: #d99c52;"
           "}"

        "QPushButton::hover{"
           "background-color: #d9af65;"
        "}"

        "QPushButton::pressed{"
            "background-color: #d99c52;"
    "}";
}

QString StyleHelper::getStartRadioButtonStyle()
{
    return "QRadioButton {"
           "    color: white;"
           "    font: 14pt 'Segoe UI';"
           "}"

           "QRadioButton::indicator {"
           "    width: 16px;"
           "    height: 16px;"
           "    border-radius: 8px;"
           "    background-color: white;"
           "}"

           "QRadioButton::indicator:checked {"
           "    background-color: #d99c52;"
           "}";
}

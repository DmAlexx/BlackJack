#ifndef STYLEHELPER_H
#define STYLEHELPER_H

#include <Qstring>

class StyleHelper
{
public:
    StyleHelper()=default;
    static QString getMainWindowBackGrnd();
    static QString getStartButtonsKeyStyle();
    static QString getStartLabelStyle();
    static QString getStartRadioButtonStyle();
};

#endif // STYLEHELPER_H

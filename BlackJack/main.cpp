#include "gui.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    srand(time(0));
    QApplication a(argc, argv);
    GUI w;
    w.show();
    return a.exec();
}

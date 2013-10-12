// Comments go here TBD


#include <QApplication>
#include "MainWindow.h"

int main(int c, char **v)
{
    QApplication app(c,v);

    MainWindow mw;
    mw.show();

    return app.exec();
}

// Comments go here TBD


#include <QApplication>
#include "StringConstants.h"
#include "MainWindow.h"

int main(int c, char **v)
{
    QApplication app(c,v);

    MainWindow mw;
    mw.setWindowTitle(MAINWINDOW_TITLE);
    mw.show();

    return app.exec();
}

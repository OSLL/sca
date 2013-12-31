// Comments go here TBD


#include <QApplication>
#include <QString>
#ifdef WIN32
    #include <windows.h>
#endif
#include "StringConstants.h"
#include "MainWindow.h"

void logToFile(QtMsgType type, const char *msg)
{
    QFile file(LOG_PATH);
    if (!file.open(QFile::ReadWrite | QFile::Text | QFile::Append))
    {
        abort();
        return;
    }
    QTextStream logStream(&file);
    QString str(LOG_PATTERN);
    switch (type)
    {
    case QtDebugMsg:
        str = str.arg("Debug");
        break;
    case QtWarningMsg:
        str = str.arg("Warning");
        break;
    case QtCriticalMsg:
        str = str.arg("Critical");
        break;
    case QtFatalMsg:
        str = str.arg("Fatal").arg(msg);
        abort();
    default:
        file.close();
        return;
    }
    str = str.arg(msg);
    logStream << str;
#ifdef WIN32
    OutputDebugString(reinterpret_cast<const wchar_t *>(str.utf16()));
#endif
    file.close();
}

int main(int c, char **v)
{
    qInstallMsgHandler(logToFile);
    qDebug() << "SCA started @" << QTime::currentTime();
    QApplication app(c,v);

    MainWindow mw;
    mw.setWindowTitle(MAINWINDOW_TITLE);
    mw.show();

    return app.exec();
}

#ifndef SOURCEBROWSER_H
#define SOURCEBROWSER_H

#include <QTreeView>
#include <QTextDocument>
#include <QFile>
#include <QMenu>
#include <QAction>

class SourceBrowser : public QTreeView
{
    Q_OBJECT
public:
    explicit SourceBrowser(QWidget *parent = 0);
signals:
    void openFile();
public slots:
    void ShowContextMenu(const QPoint &pos);
    
};

#endif // SOURCEBROWSER_H

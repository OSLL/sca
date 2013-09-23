#ifndef SOURCEBROWSER_H
#define SOURCEBROWSER_H

#include <QTreeView>
#include <QTextDocument>
#include <QFile>
#include <QMenu>
#include <QAction>
#include <QFileSystemModel>
#include <QMessageBox>

class SourceBrowser : public QTreeView
{
    Q_OBJECT
public:
    explicit SourceBrowser(QWidget *parent = 0);
    void setMenu(QMenu *_menu);
private:
    QMenu *menu;
signals:
    void addToScene();
    void openBinaryFile();
    void openFile();
public slots:
    void ShowContextMenu(const QPoint &pos);
    
};

#endif // SOURCEBROWSER_H

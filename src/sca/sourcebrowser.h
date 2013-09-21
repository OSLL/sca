#ifndef SOURCEBROWSER_H
#define SOURCEBROWSER_H

#include <QTreeView>
#include <QTextDocument>
#include <QFile>

class SourceBrowser : public QTreeView
{
    Q_OBJECT
public:
    explicit SourceBrowser(QWidget *parent = 0);
    
signals:

public slots:
    
};

#endif // SOURCEBROWSER_H

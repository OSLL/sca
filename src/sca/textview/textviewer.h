#ifndef TEXTVIEWER_H
#define TEXTVIEWER_H

#include <QTextEdit>

class TextViewer : public QTextEdit
{
    Q_OBJECT
public:
    explicit TextViewer(QWidget *parent = 0);
    
signals:
    
public slots:
    
};

#endif // TEXTVIEWER_H

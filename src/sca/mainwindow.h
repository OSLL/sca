#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ui_mainwindow.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *m_ui;

public:
    explicit MainWindow(QWidget *parent = 0);
    
signals:
    
public slots:
    
};

#endif // MAINWINDOW_H

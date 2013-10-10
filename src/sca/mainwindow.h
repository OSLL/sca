#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QFileSystemModel>
#include <QMessageBox>
#include <QPushButton>
#include <QDebug>
#include <ui_mainwindow.h>

#include "SourceBrowser.h"
#include "FileLoader.h"
#include "ObjectTextViewer.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *m_ui;
    QFileSystemModel *m_fileModel;
public:
    explicit MainWindow(QWidget *parent = 0);
signals:
    
public slots:
    void loadTextFile();
private slots:
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QFileSystemModel>
#include <ui_mainwindow.h>
class GraphScene;

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *m_ui;
    QFileSystemModel *m_fileModel;
    GraphScene *scene;
public:
    explicit MainWindow(QWidget *parent = 0);
signals:
    
public slots:
    void processFile();
    void loadTextFile(const QString &code = UTF8);
    void loadBinaryFile();
    void addToScene();
private slots:
};

#endif // MAINWINDOW_H

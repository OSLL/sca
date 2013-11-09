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
    GraphScene *m_scene;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
    
public slots:
    void processFile();
    void loadTextFile(const QString &code = UTF8);
    void loadBinaryFile();
    void addToScene();
    void openAbout();
    void exportToImage();
private slots:
};

#endif // MAINWINDOW_H

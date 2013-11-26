#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*----------------------------
 * \todo Fix addFileVisual(IScaobjectFile *&)
 */

#include <QMainWindow>
#include <QFileSystemModel>
#include <ui_mainwindow.h>
class GraphScene;
class GraphModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *m_ui;
    QFileSystemModel *m_fileModel;
    GraphScene *m_scene;
    GraphModel *m_model;

    QToolBar *linkToolBar;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
    
public slots:
    void processFile();
    void loadTextFile(const QString &code = UTF8);
    void loadBinaryFile();
    void openAbout();
    void exportToImage();
    void openHelp();
    void changeLinkToolBar();
private slots:
};

#endif // MAINWINDOW_H

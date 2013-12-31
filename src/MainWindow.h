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
class GraphTableProxyModel;
class SCAFileSystemModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *m_ui;
    SCAFileSystemModel *m_fileModel;
    GraphScene *m_scene;
    GraphModel *m_model;
    GraphFilter *m_filter;
    GraphTableProxyModel *m_tableProxy;
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
    void saveToFile();
    void openFile();
    void openHelp();
    void refreshFilterLine(const QString &text);
    void switchToObject(IScaObject *);
    void annotateNoGraphObject();
    void showAdvancedFilter();
private slots:
    void on_filterLine_textChanged(const QString &arg1);
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*----------------------------
 * \todo Fix addFileVisual(IScaobjectFile *&)
 */

#include <QMainWindow>
#include <QFileSystemModel>
#include <ui_mainwindow.h>
#include <srchiliteqt/Qt4SyntaxHighlighter.h>

class GraphScene;
class GraphModel;
class GraphTableProxyModel;
class SCAFileSystemModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    void createSyntaxList();

    Ui::MainWindow *m_ui;
    SCAFileSystemModel *m_fileModel;
    GraphScene *m_scene;
    GraphModel *m_model;
    GraphFilter *m_filter;
    GraphTableProxyModel *m_tableProxy;
    PropertyBrowser *m_propertyBrowser;
    srchiliteqt::Qt4SyntaxHighlighter *highlighter;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
    
public slots:
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
    void changeSyntax(QString langFile);
private slots:
    void on_filterLine_textChanged(const QString &arg1);
};

#endif // MAINWINDOW_H

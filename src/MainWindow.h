#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*----------------------------
 * \todo Fix addFileVisual(IScaobjectFile *&)
 */

#include <QMainWindow>
#include <QFileSystemModel>
#include <ui_mainwindow.h>
#include <srchiliteqt/Qt4SyntaxHighlighter.h>
#include "templates/settings/SettingsDialog.h"

class GraphScene;
class GraphModel;
class GraphTableProxyModel;
class SCAFileSystemModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    void createConnections();
    void createFilterConnections();
    void createTableViewConnections();
    void createGraphViewConnections();
    void createCustomContextMenuConnections();
    void createSourceBrowserConnections();
    void createMenuBarConnections();
    QMessageBox::StandardButton checkChanges();
    void clearAll();

    Ui::MainWindow *m_ui;
    QString m_currentFilePath;
    QString m_currentFileName;
    GraphScene *m_scene;
    GraphModel *m_model;
    GraphFilter *m_filter;
    PropertyBrowser *m_propertyBrowser;
    GraphTableProxyModel *m_tableProxy;
    SCAFileSystemModel *m_fileModel;
    bool m_fileChanged;
    bool m_fileIsOnDisk;
    QProcess *m_process;
    QSettings *m_settings;
    SettingsDialog *m_settingsDialog;

    QMenu *m_toolsMenu;
    QSignalMapper *m_toolsSignalMapper;


public:
    explicit MainWindow(QWidget *parent = 0);
    void closeEvent(QCloseEvent *);
    ~MainWindow();
signals:
    
public slots:
    void loadTextFile(const QString &code = UTF8);
    void loadBinaryFile();
    void openAbout();
    void exportToImage();
    void saveToFile();
    void newFile();
    void saveFile();
    void openFile();
    void setFileChanged(bool value = true);
    void openHelpDialog();
    void refreshFilterLine(const QString &text);
    void switchToObject(IScaObject *);
    void annotateNoGraphObject();
    void showAdvancedFilter();
    void close();
    void runCommand(const QString &command);
    void createToolsMenu();

private slots:
    void on_filterLine_textChanged(const QString &arg1);


};

#endif // MAINWINDOW_H

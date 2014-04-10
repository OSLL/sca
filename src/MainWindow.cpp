#include "MainWindow.h"
#include "NumericalConstants.h"
#include "StringConstants.h"

#include <QMessageBox>
#include <QPushButton>
#include <QDebug>
#include <QPixmap>
#include <QDesktopServices>
#include <QGridLayout>
#include <QStringList>

#include "widgets/PropertyBrowser.h"
#include "widgets/SourceBrowser.h"
#include "widgets/ObjectTextViewer.h"
#include "widgets/FilterDialog.h"
#include "widgets/ProcessView.h"
#include "FileLoader.h"
#include "GraphScene.h"
#include "GraphModel.h"
#include "GraphFilter.h"
#include "GraphTableProxyModel.h"
#include "GraphSaver.h"
#include "GraphLoader.h"
#include "visual/LinkVisual.h"
#include "common/SCAFileSystemModel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), m_ui(new Ui::MainWindow),
    m_currentFilePath(""),
    m_currentFileName(DEFAULT_NEW_FILE_NAME),
    m_scene(new GraphScene(0, 0, DEFAULT_SCENE_WIDTH, DEFAULT_SCENE_HEIGHT, this)),
    m_model(new GraphModel(this)),
    m_filter(new GraphFilter(m_model, this)),
    m_tableProxy(new GraphTableProxyModel(m_filter, this)),
    m_fileModel(new SCAFileSystemModel(m_model, this)),
    m_fileChanged(false),
    m_fileIsOnDisk(false),
    m_process(new QProcess(this)),
    m_settings(new QSettings(this)),
    m_settingsDialog(new SettingsDialog(m_settings, this)),
    m_toolsMenu(NULL),
    m_toolsSignalMapper(new QSignalMapper(this))
{
    m_ui->setupUi(this);
    setWindowIcon(QIcon(LOGO_PATH));

    //Setup model and filter
    m_ui->graphViewer->setScene(m_scene);
    m_ui->graphViewer->setModel(m_model);
    m_scene->setModel(m_filter);

    //We need to create propertyBrowser in-code due to it's virtual functions
    //that are initialized only when we use 'new' operation and after m_ui->setupUi();.
    m_propertyBrowser = new PropertyBrowser(m_model, m_scene,
                                            m_ui->dockPropertyBrowser),
            m_ui->dockPropertyBrowser->setWidget(m_propertyBrowser);

    //Set up file model
    m_fileModel->setRootPath("");
    m_ui->sourceBrowser->setModel(m_fileModel);
    m_ui->filterLine->setText("");

    //Leave only "name"(zero) column in SourceBrowser and last "Annotation"
    for (int i = 1; i < m_fileModel->columnCount() - 1; i++)
    {
        m_ui->sourceBrowser->hideColumn(i);
    }

    //Set some flags for widgets
    m_ui->textViewer->setWordWrapMode(QTextOption::NoWrap);
    m_ui->sourceBrowser->setContextMenuPolicy(Qt::CustomContextMenu);
    m_ui->graphViewer->setContextMenuPolicy(Qt::CustomContextMenu);

    QHeaderView *header = m_ui->tableView->horizontalHeader();
    m_ui->tableView->setModel(m_tableProxy);
    m_ui->tableView->setGridStyle(Qt::SolidLine);
    header->setMovable(true);
    header->setContextMenuPolicy(Qt::CustomContextMenu);

    createConnections();
    createToolsMenu();
    createActions();
    loadSettings();
}

void MainWindow::closeEvent(QCloseEvent *ev)
{
    if (checkChanges() == QMessageBox::Cancel)
    {
        ev->ignore();
        return;
    }
    else
    {
        saveSettings();
        QWidget::closeEvent(ev);
    }
}

void MainWindow::createConnections()
{
    connect(m_filter, SIGNAL(dataChanged(QModelIndex,QModelIndex)),
            this, SLOT(setFileChanged()));
    connect(m_ui->graphViewer, SIGNAL(itemMoved(int)),
            this, SLOT(setFileChanged()));

    connect(m_settingsDialog->getToolsModel(), SIGNAL(rowsRemoved (QModelIndex, int, int)),
            this, SLOT(createToolsMenu()));
    connect(m_settingsDialog->getToolsModel(), SIGNAL(dataChanged(QModelIndex,QModelIndex)),
            this, SLOT(createToolsMenu()));

    createFilterConnections();
    createTableViewConnections();
    createGraphViewConnections();
    createSourceBrowserConnections();
    createCustomContextMenuConnections();
    createMenuBarConnections();
}

void MainWindow::createFilterConnections()
{
    connect(m_filter, SIGNAL(filterChanged()), m_scene, SLOT(refreshAll()));
    connect(m_filter, SIGNAL(dataChanged(QModelIndex,QModelIndex)),
            m_tableProxy, SLOT(updateMap()));
    connect(m_filter, SIGNAL(rowsRemoved(QModelIndex, int, int)),
            m_tableProxy, SLOT(updateMap()));
    connect(m_filter, SIGNAL(filterChanged()),
            m_tableProxy, SLOT(updateMap()));
}

void MainWindow::createTableViewConnections()
{
    //Connect doubleClick on tableView to center on item in scene
    connect(m_ui->tableView, SIGNAL(doubleClicked(QModelIndex)),
            m_ui->graphViewer, SLOT(moveTo(QModelIndex)));
}

void MainWindow::createGraphViewConnections()
{
    //Connect going in widgets to object on doubleClicking it in scene
    connect(m_ui->graphViewer, SIGNAL(goToObject(IScaObject*)),
            m_ui->sourceBrowser, SLOT(goToObject(IScaObject*)));
    connect(m_ui->graphViewer, SIGNAL(goToObject(IScaObject*)),
            m_ui->textViewer, SLOT(goToObject(IScaObject*)));
    connect(m_ui->graphViewer, SIGNAL(goToObject(IScaObject*)),
            m_ui->hexEditor, SLOT(goToObject(IScaObject*)));
    connect(m_ui->graphViewer, SIGNAL(goToObject(IScaObject*)),
            this, SLOT(switchToObject(IScaObject*)));

    //Connects for propertyBrowser
    connect(m_ui->graphViewer, SIGNAL(goToObject(int)),
            m_propertyBrowser, SLOT(loadItem(int)));
    connect(m_ui->graphViewer, SIGNAL(itemMoved(int)),
            m_propertyBrowser, SLOT(itemMoved(int)));

    connect(m_ui->graphViewer, SIGNAL(runCommand(QString, QString)),
            this, SLOT(runCommand(QString, QString)));
}

void MainWindow::createCustomContextMenuConnections()
{
    //Connect customContextMenus
    connect(m_ui->tableView->horizontalHeader(), SIGNAL(customContextMenuRequested(QPoint)),
            m_ui->tableView, SLOT(ShowContextMenu(QPoint)));
    connect(m_ui->tableView, SIGNAL(customContextMenuRequested(QPoint)),
            m_ui->tableView, SLOT(ShowContextMenu(QPoint)));
    connect(m_ui->sourceBrowser, SIGNAL(customContextMenuRequested(QPoint)),
            m_ui->sourceBrowser, SLOT(showContextMenu(QPoint)));
    connect(m_ui->graphViewer, SIGNAL(customContextMenuRequested(QPoint)),
            m_ui->graphViewer, SLOT(ShowContextMenu(QPoint)));
}

void MainWindow::createSourceBrowserConnections()
{
    //Connect clicking on file to opening it in textViewer
    connect(m_ui->sourceBrowser, SIGNAL(openFile()),
            this, SLOT(loadTextFile()));
    connect(m_ui->sourceBrowser, SIGNAL(openFileAs(QString)),
            this, SLOT(loadTextFile(QString)));
    connect(m_ui->sourceBrowser, SIGNAL(openBinaryFile()),
            this, SLOT(loadBinaryFile()));
    connect(m_ui->sourceBrowser, SIGNAL(annotate()),
            this, SLOT(annotateNoGraphObject()));

    connect(m_ui->sourceBrowser, SIGNAL(runCommand(QString, QString)),
            this, SLOT(runCommand(QString, QString)));
}

void MainWindow::createMenuBarConnections()
{
    //Connect file actions
    connect(m_ui->actionNew, SIGNAL(triggered()),
            this, SLOT(newFile()));
    connect(m_ui->actionSave, SIGNAL(triggered()),
            this, SLOT(saveFile()));
    connect(m_ui->actionSaveAs, SIGNAL(triggered()),
            this, SLOT(saveToFile()));
    connect(m_ui->actionExport, SIGNAL(triggered()),
            this, SLOT(exportToImage()));
    connect(m_ui->actionOpen, SIGNAL(triggered()),
            this, SLOT(openFile()));

    //MenuBar connections
    connect(m_ui->actionOpenInTextViewer, SIGNAL(triggered()),
            this, SLOT(loadTextFile()));
    connect(m_ui->actionOpenInBinaryView, SIGNAL(triggered()),
            this, SLOT(loadBinaryFile()));
    connect(m_ui->actionAbout, SIGNAL(triggered()),
            this, SLOT(openAbout()));
    connect(m_ui->actionHelp, SIGNAL(triggered()),
            this, SLOT(openHelpDialog()));
    connect(m_ui->advancedFilterButton, SIGNAL(clicked()),
            this, SLOT(showAdvancedFilter()));
    connect(m_ui->actionFilter, SIGNAL(triggered()),
            this, SLOT(showAdvancedFilter()));

    //"Enabling" docks when needed
    connect(m_ui->actionTableView, SIGNAL(triggered(bool)),
            m_ui->dockTableView, SLOT(setVisible(bool)));
    connect(m_ui->actionSourceTree, SIGNAL(triggered(bool)),
            m_ui->dockFileBrowser, SLOT(setVisible(bool)));
    connect(m_ui->actionTextView, SIGNAL(triggered(bool)),
            m_ui->dockTextEditor, SLOT(setVisible(bool)));
    connect(m_ui->actionHexView, SIGNAL(triggered(bool)),
            m_ui->dockHexEditor, SLOT(setVisible(bool)));
    connect(m_ui->actionPropertyBrowser, SIGNAL(triggered(bool)),
            m_ui->dockPropertyBrowser, SLOT(setVisible(bool)));

    //"Checking" actions when docks are visible
    connect(m_ui->dockTextEditor, SIGNAL(visibilityChanged(bool)),
            m_ui->actionTextView, SLOT(setChecked(bool)));
    connect(m_ui->dockHexEditor, SIGNAL(visibilityChanged(bool)),
            m_ui->actionHexView, SLOT(setChecked(bool)));
    connect(m_ui->dockFileBrowser, SIGNAL(visibilityChanged(bool)),
            m_ui->actionSourceTree, SLOT(setChecked(bool)));
    connect(m_ui->dockTableView, SIGNAL(visibilityChanged(bool)),
            m_ui->actionTableView, SLOT(setChecked(bool)));
    connect(m_ui->dockPropertyBrowser, SIGNAL(visibilityChanged(bool)),
            m_ui->actionPropertyBrowser, SLOT(setChecked(bool)));

    //"Bug-fix" for raising dock when it is hidden when merged to another one
    connect(m_ui->actionTableView, SIGNAL(triggered()),
            m_ui->dockTableView, SLOT(raise()));
    connect(m_ui->actionSourceTree, SIGNAL(triggered()),
            m_ui->dockFileBrowser, SLOT(raise()));
    connect(m_ui->actionTextView, SIGNAL(triggered()),
            m_ui->dockTextEditor, SLOT(raise()));
    connect(m_ui->actionHexView, SIGNAL(triggered()),
            m_ui->dockHexEditor, SLOT(raise()));
    connect(m_ui->actionPropertyBrowser, SIGNAL(triggered()),
            m_ui->dockPropertyBrowser, SLOT(raise()));

    connect(m_ui->actionSettings, SIGNAL(triggered()),
            m_settingsDialog, SLOT(exec()));
}

void MainWindow::createActions()
{

    QMenu *menu;
    //GraphView context menu
    menu = m_ui->graphViewer->getMenu();

    QAction *connectAction = menu->addAction(CONNECT_OBJECTS);
    QAction *createGroup = menu->addAction(CREATE_GROUP);
    QAction *removeAction = menu->addAction(DELETE_ITEMS);
    QAction *ungroupAction = menu->addAction(UNGROUP_OBJECTS);
    menu->addSeparator();
    QAction *toTextAction = menu->addAction(TO_TEXT_BLOCK);
    QAction *toIdentAction = menu->addAction(TO_IDENTIFIER);
    menu->addSeparator();
    QAction *setLeftArrow = menu->addAction(LEFT_ARROW);
    setLeftArrow->setCheckable(true);
    QAction *setRightArrow = menu->addAction(RIGHT_ARROW);
    setRightArrow->setCheckable(true);
    menu->addSeparator();
    QAction *editAnnotAction = menu->addAction(EDIT_ANNOTATION);

    connect(m_ui->graphViewer, SIGNAL(canCreateGroup(bool)),
            createGroup, SLOT(setEnabled(bool)));
    connect(m_ui->graphViewer, SIGNAL(canUngroup(bool)),
            ungroupAction, SLOT(setEnabled(bool)));

    connect(m_ui->graphViewer, SIGNAL(objectsCanConnect(bool)),
            connectAction, SLOT(setEnabled(bool)));
    connect(m_ui->graphViewer, SIGNAL(objectsSelected(bool)),
            removeAction, SLOT(setEnabled(bool)));

    connect(m_ui->graphViewer, SIGNAL(canConvertToText(bool)),
            toTextAction, SLOT(setEnabled(bool)));
    connect(m_ui->graphViewer, SIGNAL(canConvertToIdent(bool)),
            toIdentAction, SLOT(setEnabled(bool)));

    connect(m_ui->graphViewer, SIGNAL(linkSelected(bool)),
            setLeftArrow, SLOT(setEnabled(bool)));
    connect(m_ui->graphViewer, SIGNAL(linkSelected(bool)),
            setRightArrow, SLOT(setEnabled(bool)));

    connect(m_ui->graphViewer, SIGNAL(linkHasLeftArrow(bool)),
            setLeftArrow, SLOT(setChecked(bool)));
    connect(m_ui->graphViewer, SIGNAL(linkHasRightArrow(bool)),
            setRightArrow, SLOT(setChecked(bool)));

    connect(m_ui->graphViewer, SIGNAL(objectSelected(bool)),
            editAnnotAction, SLOT(setEnabled(bool)));

    connect(connectAction, SIGNAL(triggered()),
            m_ui->graphViewer, SLOT(connectSelectedObjects()));
    connect(removeAction, SIGNAL(triggered()),
            m_ui->graphViewer, SLOT(removeSelectedObjects()));
    connect(toTextAction, SIGNAL(triggered()),
            m_ui->graphViewer, SLOT(convertSelectedNodeToText()));
    connect(toIdentAction, SIGNAL(triggered()),
            m_ui->graphViewer, SLOT(convertSelectedNodeToIdentifier()));
    connect(setLeftArrow, SIGNAL(toggled(bool)),
            m_ui->graphViewer, SLOT(setSelectedLinkLeftArrow(bool)));
    connect(setRightArrow, SIGNAL(toggled(bool)),
            m_ui->graphViewer, SLOT(setSelectedLinkRightArrow(bool)));
    connect(editAnnotAction, SIGNAL(triggered()),
            m_ui->graphViewer, SLOT(editSelectedAnnotation()));
    connect(createGroup, SIGNAL(triggered()),
            m_ui->graphViewer, SLOT(createGroupFromSelection()));
    connect(ungroupAction, SIGNAL(triggered()),
            m_ui->graphViewer, SLOT(ungroupSelectedObjects()));

    connectAction->setDisabled(true);
    removeAction->setDisabled(true);
    toTextAction->setDisabled(true);
    toIdentAction->setDisabled(true);
    setLeftArrow->setDisabled(true);
    setRightArrow->setDisabled(true);
    editAnnotAction->setDisabled(true);
    createGroup->setDisabled(true);
    ungroupAction->setDisabled(true);

    //----------------------------------------------------


    m_ui->toolBar->addAction(m_ui->actionOpen);
    m_ui->toolBar->addAction(m_ui->actionSave);
    m_ui->toolBar->addSeparator();
    m_ui->toolBar->addAction(connectAction);
    m_ui->toolBar->addAction(removeAction);
    m_ui->toolBar->addAction(editAnnotAction);
    m_ui->toolBar->addSeparator();
    m_ui->toolBar->addAction(setLeftArrow);
    m_ui->toolBar->addAction(setRightArrow);
    m_ui->toolBar->addSeparator();
    m_ui->toolBar->addAction(m_ui->actionSettings);
}

void MainWindow::createToolsMenu()
{
    if(!m_toolsMenu)
    {
        m_toolsMenu = new QMenu("Tools", this);
        m_ui->sourceBrowser->getMenu()->addMenu(m_toolsMenu);
        connect(m_toolsSignalMapper, SIGNAL(mapped(QString)),
                m_ui->sourceBrowser, SLOT(runTool(QString)));
        m_ui->graphViewer->getMenu()->addMenu(m_toolsMenu);
        connect(m_toolsSignalMapper, SIGNAL(mapped(QString)),
                m_ui->graphViewer, SLOT(runTool(QString)));
    }
    else
    {
        m_toolsMenu->clear();
        m_toolsMenu->setTitle("Tools");
    }

    QStringList tools = m_settingsDialog->getToolsModel()->stringList();

    foreach(QString tool, tools)
    {
        QAction *toolAction = new QAction(tool, m_toolsMenu);
        m_toolsMenu->addAction(toolAction);
        connect(toolAction, SIGNAL(triggered()),
                m_toolsSignalMapper, SLOT(map()));
        m_toolsSignalMapper->setMapping(toolAction, tool);
    }
}

QMessageBox::StandardButton MainWindow::checkChanges()
{
    //Check if user wants to save changes
    if (m_fileChanged)
    {
        int button =
                QMessageBox::question(this, SAVE_CHANGED_FILE_QUESTION_TITLE,
                                      SAVE_CHANGED_FILE_QUESTION_TEXT.arg(m_currentFilePath),
                                      QMessageBox::Yes,
                                      QMessageBox::No,
                                      QMessageBox::Cancel);
        if (button == QMessageBox::Yes)
        {
            saveFile();
        }
        return static_cast<QMessageBox::StandardButton>(button);
    }
    else
    {
        return QMessageBox::NoButton;
    }
}

void MainWindow::loadSettings()
{
    m_settings->beginGroup(SETTINGS_GLOBAL);
    bool firstRun = !(m_settings->value(SETTINGS_FIRST_RUN).toBool());
    m_settings->endGroup();
    if (firstRun)
    {
        processFirstRun();
    }
    m_settings->sync();
    qDebug() << "[MainWindow]: loading settings, keys: " << m_settings->allKeys();
    m_settings->beginGroup(SETTINGS_WIDGET);
    restoreState(m_settings->value(SETTINGS_STATE).toByteArray());
    restoreGeometry(m_settings->value(SETTINGS_GEOMETRY).toByteArray());
    m_settings->endGroup();

    updateActions();
}

void MainWindow::updateActions()
{
    m_ui->actionHexView->setChecked(!m_ui->dockHexEditor->isHidden());
    m_ui->actionPropertyBrowser->setChecked(!m_ui->dockPropertyBrowser->isHidden());
    m_ui->actionTableView->setChecked(!m_ui->dockTableView->isHidden());
    m_ui->actionSourceTree->setChecked(!m_ui->dockFileBrowser->isHidden());
    m_ui->actionTextView->setChecked(!m_ui->dockTextEditor->isHidden());
}

void MainWindow::saveSettings()
{
    m_settings->beginGroup(SETTINGS_WIDGET);
    m_settings->setValue(SETTINGS_GEOMETRY, saveGeometry());
    m_settings->setValue(SETTINGS_STATE, saveState());
    m_settings->endGroup();
    m_settings->sync();
    qDebug() << "[MainWindow]: saving settings, keys: " << m_settings->allKeys();
}

void MainWindow::clearAll()
{
    m_scene->clear();
    m_model->clear();
    m_filter->refreshRegExp();
    m_propertyBrowser->clear();
    m_tableProxy->updateMap();
}

void MainWindow::processFirstRun()
{
    //Do what you want here if it was first run of program
    QStringList list;
    list << "readelf -a %f" << "objdump -d %f";
    m_settings->beginGroup("Global");
    m_settings->setValue("firstrun", QVariant(true));
    m_settings->endGroup();
    m_settingsDialog->setToolList(list);
}

MainWindow::~MainWindow()
{
    if (m_scene != NULL)
        delete m_scene;
    if (m_fileModel != NULL)
        delete m_fileModel;
    if (m_ui != NULL)
        delete m_ui;
    if (m_filter != NULL)
        delete m_filter;
}

void MainWindow::loadBinaryFile()
{
    QModelIndex curIndex = m_ui->sourceBrowser->currentIndex();
    QFileInfo fileInf = m_fileModel->fileInfo(curIndex);
    m_ui->hexEditor->loadFromFile(fileInf.absoluteFilePath());
}

void MainWindow::openAbout()
{
    QMessageBox about(QMessageBox::NoIcon, ABOUT_TITLE, ABOUT_TEXT,
                      QMessageBox::Ok, 0);
    about.setIconPixmap(QPixmap(LOGO_PATH).scaled(64, 64));
    about.setWindowIcon(QIcon(LOGO_PATH));
    about.exec();
}

void MainWindow::exportToImage()
{
    QString selectedFilter = tr("Png(*.png)");
    QString path = QFileDialog::getSaveFileName(this, tr("Export to"), QDir::homePath(),
                                                tr("PNG (*.png);;JPEG (*.jpg *.jpeg);;BMP (*.bmp)"),
                                                &selectedFilter);
    if (selectedFilter == tr("PNG (*.png)"))
    {
        path += ".png";
    }
    if (selectedFilter == tr("JPEG (*.jpg *.jpeg)"))
    {
        path += ".jpg";
    }
    if (selectedFilter == tr("BMP (*.bmp)"))
    {
        path += ".bmp";
    }

    m_ui->graphViewer->exportToImage(path);
}

void MainWindow::saveToFile()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Save"), QDir::homePath(),
                                                tr("GM (*.gm)"));
    if (path.isEmpty())
    {
        return;
    }
    QFileInfo fi(path);
    if(fi.suffix() != QString("gm"))
        path += ".gm";

    GraphSaver *saver = new GraphSaver(path);
    saver->save(m_model, m_scene);
    delete saver;
    m_fileIsOnDisk = true;
    m_currentFileName = fi.fileName();
    m_currentFilePath = path;
    statusBar()->showMessage(FILE_SAVE_SUCCESSFUL, STATUS_BAR_FILE_SAVED_TIMEOUT);

    setFileChanged(false);
}

void MainWindow::newFile()
{
    checkChanges();

    clearAll();
    m_currentFileName = DEFAULT_NEW_FILE_NAME;
    m_currentFilePath = "";
    setFileChanged(false);
    m_fileIsOnDisk = false;
}

void MainWindow::saveFile()
{
    if (m_fileIsOnDisk)
    {
        GraphSaver *saver = new GraphSaver(m_currentFilePath);
        saver->save(m_model, m_scene);
        delete saver;
        setFileChanged(false);
        statusBar()->showMessage(FILE_SAVE_SUCCESSFUL,
                                 STATUS_BAR_FILE_SAVED_TIMEOUT);
    }
    else
    {
        saveToFile();
    }
}

void MainWindow::openFile()
{
    checkChanges();
    QString path = QFileDialog::getOpenFileName(this, tr("Open"), QDir::homePath(),
                                                tr("GM (*.gm)"));
    if (path.isEmpty())
    {
        return;
    }
    clearAll();

    GraphLoader *loader = new GraphLoader(path);
    loader->loadGraph(m_model, m_scene);
    delete loader;

    m_currentFilePath = path;
    QFileInfo fi(path);
    m_currentFileName = fi.fileName();
    m_fileIsOnDisk = true;
    m_ui->sourceBrowser->reset();
    m_ui->tableView->reset();
    setFileChanged(false);
}

void MainWindow::setFileChanged(bool value)
{
    m_fileChanged = value;
    this->setWindowTitle(MAINWINDOW_TITLE.arg(m_currentFileName + (m_fileChanged?"*":"") ));
    if (m_fileChanged)
    {
        disconnect(m_ui->graphViewer, SIGNAL(itemMoved(int)),
                   this, SLOT(setFileChanged()));
        disconnect(m_model, SIGNAL(dataChanged(QModelIndex,QModelIndex)),
                   this, SLOT(setFileChanged()));
    }
    else
    {
        connect(m_ui->graphViewer, SIGNAL(itemMoved(int)),
                this, SLOT(setFileChanged()), Qt::UniqueConnection);
        connect(m_model, SIGNAL(dataChanged(QModelIndex,QModelIndex)),
                this, SLOT(setFileChanged()), Qt::UniqueConnection);
    }
}

void MainWindow::openHelpDialog()
{
    QString link = QApplication::applicationDirPath() +
            QString(HELP_PATH);
    QUrl url = QUrl::fromLocalFile(link);
    qDebug() << url;
    QDesktopServices::openUrl(url);
}

void MainWindow::refreshFilterLine(const QString &text)
{
    m_ui->filterLine->setText(text);
}

void MainWindow::switchToObject(IScaObject *obj)
{
    switch (obj->getType())
    {
    case IScaObject::TEXTBLOCK:
    {
        m_ui->textViewer->setFocus();
        m_ui->dockTextEditor->raise();
        break;
    }
    case IScaObject::BINARYBLOCK:
    {
        m_ui->hexEditor->setFocus();
        m_ui->dockHexEditor->raise();
        break;
    }
    case IScaObject::DIRECTORY:
    {
        m_ui->sourceBrowser->setFocus();
        m_ui->dockFileBrowser->raise();
        break;
    }
    case IScaObject::FILE:
    {
        m_ui->sourceBrowser->setFocus();
        m_ui->dockFileBrowser->raise();
        break;
    }
    case IScaObject::IDENTIFIER:
    {
        m_ui->textViewer->setFocus();
        m_ui->dockTextEditor->raise();
        break;
    }
    case IScaObject::LINE:
    {
        m_ui->textViewer->setFocus();
        m_ui->dockTextEditor->raise();
        break;
    }
    case IScaObject::SYMBOL:
    {
        m_ui->textViewer->setFocus();
        m_ui->dockTextEditor->raise();
        break;
    }
    default:
        break;
    }
}

void MainWindow::annotateNoGraphObject()
{
    QFileInfo curFileInfo = m_fileModel->fileInfo(m_ui->sourceBrowser->currentIndex());
    IScaObject *object = NULL;
    object = m_model->getObjectByPath(curFileInfo.absoluteFilePath());
    if (object != NULL)
    {
        m_model->editAnnotation(m_model->getId(object));
        return;
    }
    if (curFileInfo.isDir())
    {
        object = new IScaObjectDirectory(curFileInfo);
    }
    else if (curFileInfo.isFile())
    {
        object = new IScaObjectFile(curFileInfo);
    }
    else
    {
        //This is some weird thing, ignore it
        return;
    }
    int id = m_model->addObject(object);
    m_model->setData(m_model->index(id, 0), QVariant(false), onSceneRole);
    if (m_model->editAnnotation(id) == false)
    {
        //User clicked cancel, delete object
        m_model->removeObject(id);
    }
    setFileChanged(true);
}

void MainWindow::showAdvancedFilter()
{
    FilterDialog *wid;
    QList<FilterDialog *> filters = findChildren<FilterDialog *>();
    if (filters.size() == 1)
    {
        //So filter already showed up
        wid = static_cast<FilterDialog *>(filters.at(0));
        wid->raise();
        wid->move(QApplication::desktop()->screen()->rect().center()
                  - wid->rect().center());
    }
    else
    {
        wid = new FilterDialog(m_filter, m_scene, this);
        wid->setFixedSize(wid->size());
        qDebug() << "[Main window]: Advanced filter called";
    }
    wid->show();
}

void MainWindow::runCommand(const QString &tool, const QString &file)
{
    QDockWidget *dock = new QDockWidget(this);
    ProcessView *processView = new ProcessView(dock);
    processView->setCurrentPath(file);

    QString command(tool);
    command.replace(QString("%f"), file);

    QGridLayout *layout = new QGridLayout(dock);
    layout->addWidget(processView, 0, 0);
    QWidget *newWidget = new QWidget(this);
    newWidget->setLayout(layout);

    dock->setWidget(newWidget);
    processView->execute(command);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    dock->setWindowTitle(command);
}

void MainWindow::loadTextFile(const QString &code)
{
    QModelIndex curIndex = m_ui->sourceBrowser->currentIndex();
    QFileInfo fileInf = m_fileModel->fileInfo(curIndex);
    m_ui->textViewer->loadFromFile(fileInf.absoluteFilePath(), code);
}

void MainWindow::on_filterLine_textChanged(const QString &arg1)
{
    m_filter->setFilePath(arg1);
}

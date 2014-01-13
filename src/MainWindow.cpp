#include "MainWindow.h"
#include "NumericalConstants.h"
#include "StringConstants.h"

#include <QMessageBox>
#include <QPushButton>
#include <QDebug>
#include <QPixmap>
#include <QDesktopServices>

#include "widgets/PropertyBrowser.h"
#include "widgets/SourceBrowser.h"
#include "widgets/ObjectTextViewer.h"
#include "widgets/FilterDialog.h"
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
    QMainWindow(parent), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    setWindowIcon(QIcon(LOGO_PATH));

    //Create and setup model and filter
    m_scene = new GraphScene(0, 0, DEFAULT_SCENE_WIDTH, DEFAULT_SCENE_HEIGHT, this);
    m_ui->graphViewer->setScene(m_scene);

    m_model = new GraphModel(this);
    m_ui->graphViewer->setModel(m_model);

    m_filter = new GraphFilter(m_model, this);
    m_scene->setModel(m_filter);

    m_propertyBrowser = new PropertyBrowser(m_model, m_scene,
                                            m_ui->dockPropertyBrowser);
    m_ui->dockPropertyBrowser->setWidget(m_propertyBrowser);
    m_propertyBrowser->setModel(m_model);
    m_propertyBrowser->setScene(m_scene);

    m_tableProxy = new GraphTableProxyModel(m_filter, this);
    m_ui->tableView->setModel(m_tableProxy);
    m_ui->tableView->horizontalHeader()->setMovable(true);
    m_ui->tableView->setGridStyle(Qt::SolidLine);
    connect(m_filter, SIGNAL(filterChanged()), m_scene, SLOT(refreshAll()));
    connect(m_filter, SIGNAL(dataChanged(QModelIndex,QModelIndex)),
            m_tableProxy, SLOT(updateMap()));
    connect(m_filter, SIGNAL(rowsRemoved(QModelIndex, int, int)),
            m_tableProxy, SLOT(updateMap()));
    connect(m_filter, SIGNAL(filterChanged()),
            m_tableProxy, SLOT(updateMap()));
    //Connect doubleClick on tableView to center on item in scene
    connect(m_ui->tableView, SIGNAL(doubleClicked(QModelIndex)),
            m_ui->graphViewer, SLOT(moveTo(QModelIndex)));
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

    //Set up file model
    m_fileModel = new SCAFileSystemModel(m_model, this);
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
    header->setContextMenuPolicy(Qt::CustomContextMenu);

    //Connect customContextMenus
    connect(header, SIGNAL(customContextMenuRequested(QPoint)),
            m_ui->tableView, SLOT(ShowContextMenu(QPoint)));
    connect(m_ui->tableView, SIGNAL(customContextMenuRequested(QPoint)),
            m_ui->tableView, SLOT(ShowContextMenu(QPoint)));
    connect(m_ui->sourceBrowser, SIGNAL(customContextMenuRequested(QPoint)),
            m_ui->sourceBrowser, SLOT(ShowContextMenu(QPoint)));
    connect(m_ui->graphViewer, SIGNAL(customContextMenuRequested(QPoint)),
            m_ui->graphViewer, SLOT(ShowContextMenu(QPoint)));
    //Connect clicking on file to opening it in textViewer
    connect(m_ui->sourceBrowser, SIGNAL(openFile()),
            this, SLOT(loadTextFile()));
    connect(m_ui->sourceBrowser, SIGNAL(openFileAs(QString)),
            this, SLOT(loadTextFile(QString)));
    connect(m_ui->sourceBrowser, SIGNAL(openBinaryFile()),
            this, SLOT(loadBinaryFile()));
    connect(m_ui->sourceBrowser, SIGNAL(annotate()),
            this, SLOT(annotateNoGraphObject()));
    //MenuBar connections
    connect(m_ui->actionOpenInTextViewer, SIGNAL(triggered()),
            this, SLOT(loadTextFile()));
    connect(m_ui->actionOpenInBinaryView, SIGNAL(triggered()),
            this, SLOT(loadBinaryFile()));
    connect(m_ui->actionAbout, SIGNAL(triggered()),
            this, SLOT(openAbout()));
    connect(m_ui->actionHelp, SIGNAL(triggered()),
            this, SLOT(openHelp()));
    connect(m_ui->advancedFilterButton, SIGNAL(clicked()),
            this, SLOT(showAdvancedFilter()));
    connect(m_ui->actionFilter, SIGNAL(triggered()),
            this, SLOT(showAdvancedFilter()));

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
    if(QFileInfo(path).suffix() == QString())
        path += ".gm";

    GraphSaver saver(path);
    saver.save(m_model, m_scene);
}

void MainWindow::openFile()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open"), QDir::homePath(),
                                                tr("GM (*.gm)"));
    if (path.isEmpty())
    {
        return;
    }
    GraphLoader loader(path);
    loader.loadGraph(m_model, m_scene);
    m_ui->sourceBrowser->reset();
    m_ui->tableView->reset();
}

void MainWindow::openHelp()
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
            break;
        }
    case IScaObject::BINARYBLOCK:
        {
            m_ui->hexEditor->setFocus();
            break;
        }
    case IScaObject::DIRECTORY:
        {
            m_ui->sourceBrowser->setFocus();
            break;
        }
    case IScaObject::FILE:
        {
            m_ui->sourceBrowser->setFocus();
            break;
        }
    case IScaObject::IDENTIFIER:
        {
            m_ui->textViewer->setFocus();
            break;
        }
    case IScaObject::LINE:
        {
            m_ui->textViewer->setFocus();
            break;
        }
    case IScaObject::SYMBOL:
        {
            m_ui->textViewer->setFocus();
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
    m_model->setData(m_model->index(id, 0), QVariant(false), isShownRole);
    if (m_model->editAnnotation(id) == false)
    {
        //User clicked cancel, delete object
        m_model->removeObject(id);
    }
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
        qDebug() << "[Main window]: Advanced filter called";
    }
    wid->show();
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

//void MainWindow::createSyntaxList()
//{
//    QStringList langFilter("*.lang");
//    QDir langsDir("./langs");
//    QStringList syntaxFiles = langsDir.entryList(langFilter, QDir::Files);

//    QMenu *syntaxMenu = new QMenu("Syntax", this);
//    QActionGroup *syntaxActions = new QActionGroup(this);
//    QSignalMapper *syntaxMapper  = new QSignalMapper(this);
//    foreach(QString syntax, syntaxFiles)
//    {
//        QAction *action = new QAction(QFileInfo(syntax).baseName(), this);
//        action->setCheckable(true);

//        syntaxActions->addAction(action);
//        syntaxMenu->addAction(action);

//        if(QFileInfo(syntax).baseName() == "default")
//            action->setChecked(true);
//    }
//    m_ui->menuView->addMenu(syntaxMenu);
//}

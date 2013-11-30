#include "MainWindow.h"
#include "NumericalConstants.h"
#include "StringConstants.h"

#include <QMessageBox>
#include <QPushButton>
#include <QDebug>
#include <QPixmap>
#include <QDesktopServices>

#include "widgets/SourceBrowser.h"
#include "FileLoader.h"
#include "widgets/ObjectTextViewer.h"
#include "GraphScene.h"
#include "GraphModel.h"
#include "visual/LinkVisual.h"
#include "widgets/FilterDialog.h"
#include "GraphFilter.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    setWindowIcon(QIcon(LOGO_PATH));

    //Create and setup model and filter
    m_scene = new GraphScene(0, 0, DEFAULT_SCENE_WIDTH, DEFAULT_SCENE_HEIGHT, this);
    m_model = new GraphModel(this);
    m_filter = new GraphFilter(this);
    m_filter->setSourceModel(m_model);

    m_ui->graphViewer->setScene(m_scene);
    m_ui->graphViewer->setModel(m_model);
    m_scene->setModel(m_filter);

    //Set up file model
    m_fileModel = new QFileSystemModel(this);
    m_fileModel->setRootPath("");
    m_ui->sourceBrowser->setModel(m_fileModel);
    m_ui->filterLine->setText("");

    //Leave only "name"(zero) column in SourceBrowser
    for (int i = 1; i < m_fileModel->columnCount(); i++)
    {
        m_ui->sourceBrowser->hideColumn(i);
    }

    //Set some flags for widgets
    m_ui->textViewer->setWordWrapMode(QTextOption::NoWrap);
    m_ui->sourceBrowser->setContextMenuPolicy(Qt::CustomContextMenu);
    m_ui->graphViewer->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(m_filter, SIGNAL(filterChanged()), m_scene, SLOT(refreshAll()));
    //Connect customContextMenus
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
    connect(m_ui->sourceBrowser, SIGNAL(doubleClicked(QModelIndex)),
            this, SLOT(processFile()));
    //MenuBar connections
    connect(m_ui->actionOpenInTextViewer, SIGNAL(triggered()),
            this, SLOT(loadTextFile()));
    connect(m_ui->actionOpenInBinaryView, SIGNAL(triggered()),
            this, SLOT(loadBinaryFile()));
    connect(m_ui->actionAbout, SIGNAL(triggered()),
            this, SLOT(openAbout()));
    connect(m_ui->actionHelp, SIGNAL(triggered()),
            this, SLOT(openHelp()));
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

void MainWindow::processFile()
{
    switch(m_ui->ViewsTabs->currentIndex())
    {
    case 0: //Text view
        loadTextFile();
        break;
    case 1: //Binary view
        loadBinaryFile();
        break;
    }
}

void MainWindow::loadBinaryFile()
{
    QModelIndex curIndex = m_ui->sourceBrowser->currentIndex();
    QFileInfo fileInf = m_fileModel->fileInfo(curIndex);
    m_ui->hexEditor->loadFromFile(fileInf.absoluteFilePath());
    m_ui->ViewsTabs->setCurrentIndex(1);
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
    QString path = QFileDialog::getSaveFileName(this, tr("Export to"), QDir::homePath(),
                                                tr("PNG (*png)"));
    path += ".png";

    m_ui->graphViewer->exportToImage(path);
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

void MainWindow::loadTextFile(const QString &code)
{
    QModelIndex curIndex = m_ui->sourceBrowser->currentIndex();
    QFileInfo fileInf = m_fileModel->fileInfo(curIndex);
    m_ui->textViewer->loadFromFile(fileInf.absoluteFilePath(), code);
    m_ui->ViewsTabs->setCurrentIndex(0);
}

void MainWindow::on_filterLine_textChanged(const QString &arg1)
{
    m_filter->setFilePath(arg1);
}

void MainWindow::on_advancedFilterButton_clicked()
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
    wid = new FilterDialog(m_filter, m_scene, this);
    qDebug() << "Advanced filter called";
    wid->show();
}

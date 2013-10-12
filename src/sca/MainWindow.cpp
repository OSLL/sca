#include "MainWindow.h"
#include "NumericalConstants.h"
#include "StringConstants.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    //Set up file model
    m_fileModel = new QFileSystemModel(this);
    m_fileModel->setRootPath("");
    m_ui->sourceBrowser->setModel(m_fileModel);

    m_ui->textViewer->setWordWrapMode(QTextOption::NoWrap);
    //Leave only "name"(zero) column in SourceBrowser
    for (int i = 1; i < m_fileModel->columnCount(); i++)
    {
        m_ui->sourceBrowser->hideColumn(i);
    }

    m_ui->sourceBrowser->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_ui->sourceBrowser, SIGNAL(customContextMenuRequested(QPoint)),
            m_ui->sourceBrowser, SLOT(ShowContextMenu(QPoint)));
    //Connect clicking on file to opening it in textViewer
    connect(m_ui->sourceBrowser, SIGNAL(openFile()),
            this, SLOT(loadTextFile()));
    connect(m_ui->sourceBrowser, SIGNAL(doubleClicked(QModelIndex)),
            this, SLOT(loadTextFile()));
    connect(m_ui->sourceBrowser, SIGNAL(openBinaryFile()),
            this, SLOT(loadBinaryFile()));
    //MenuBar connections
    connect(m_ui->actionOpenInTextViewer, SIGNAL(triggered()),
            this, SLOT(loadTextFile()));
    connect(m_ui->actionOpenInBinaryView, SIGNAL(triggered()),
            this, SLOT(loadBinaryFile()));

    QSignalMapper* signalMapper = new QSignalMapper (this);
    SourceBrowserMenu *sourceBrowserMenu = m_ui->sourceBrowser->getMenu();
    sourceBrowserMenu->connectActionByMenu(OPEN_IN_TEXT_VIEWER_AS, UTF8, signalMapper, SLOT(map()));
    sourceBrowserMenu->connectActionByMenu(OPEN_IN_TEXT_VIEWER_AS, CP866, signalMapper, SLOT(map()));
    sourceBrowserMenu->connectActionByMenu(OPEN_IN_TEXT_VIEWER_AS, ISO885915, signalMapper, SLOT(map()));

    signalMapper->setMapping(sourceBrowserMenu->getActionByName(UTF8, OPEN_IN_TEXT_VIEWER_AS), UTF8);
    signalMapper->setMapping(sourceBrowserMenu->getActionByName(CP866, OPEN_IN_TEXT_VIEWER_AS), CP866);
    signalMapper->setMapping(sourceBrowserMenu->getActionByName(ISO885915, OPEN_IN_TEXT_VIEWER_AS), ISO885915);

    connect (signalMapper, SIGNAL(mapped(const QString &)), this, SLOT(loadTextFile(const QString &))) ;
}

void MainWindow::loadBinaryFile()
{
    QFileInfo fileInf = m_fileModel->fileInfo(m_ui->sourceBrowser->currentIndex());
    if (fileInf.size() > MAX_BINARY_FILE_SIZE)
    {
        QMessageBox::warning(this, ERROR_TOO_LARGE_BINARY_FILE_TITLE,
                             ERROR_TOO_LARGE_BINARY_FILE_MSG.arg(QString::number(fileInf.size())),
                             QMessageBox::Ok);
        return;
    }
    //Check if the file has already been opened
    //or it is not file at all
    if (m_ui->hexEditor->getCurrentPath() == fileInf.filePath()
            || !fileInf.isFile())
    {
        return;
    }

    FileLoader *fLoader = new FileLoader();

    fLoader->openFile(fileInf.filePath());

    QByteArray arr;
    fLoader->loadToByteArray(arr);
    m_ui->hexEditor->setData(arr);
    m_ui->textViewer->setCurrentPath(fileInf.filePath());

    fLoader->deleteLater();
}

void MainWindow::loadTextFile(const QString &code)
{
    QFileInfo fileInf = m_fileModel->fileInfo(m_ui->sourceBrowser->currentIndex());
    //Check if the file has already been opened
    //or it is not file at all
    if (m_ui->textViewer->getCurrentPath() == fileInf.filePath()
            || !fileInf.isFile())
    {
        return;
    }

    FileLoader *fLoader = new FileLoader();

    fLoader->openFile(fileInf.filePath());

    fLoader->loadToTextDoc(m_ui->textViewer->document(), code.toStdString().c_str());
    m_ui->textViewer->setCurrentPath(fileInf.filePath());

    fLoader->deleteLater();
}


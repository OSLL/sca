#include "MainWindow.h"

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
}

void MainWindow::loadBinaryFile()
{
    QFileInfo fileInf = m_fileModel->fileInfo(m_ui->sourceBrowser->currentIndex());
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

void MainWindow::loadTextFile()
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

    fLoader->loadToTextDoc(m_ui->textViewer->document());
    m_ui->textViewer->setCurrentPath(fileInf.filePath());

    fLoader->deleteLater();
}

#include "MainWindow.h"
#include "NumericalConstants.h"
#include "StringConstants.h"

#include <QMessageBox>
#include <QPushButton>
#include <QDebug>

#include "widgets/SourceBrowser.h"
#include "FileLoader.h"
#include "widgets/ObjectTextViewer.h"
#include "GraphScene.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    scene = new GraphScene(0, 0, DEFAULT_SCENE_WIDTH, DEFAULT_SCENE_HEIGHT);
    m_ui->graphViewer->setScene(scene);
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
    case 2: //Scene
        addToScene();
        break;
    }
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
    m_ui->ViewsTabs->setCurrentIndex(1);
    fLoader->deleteLater();
}

void MainWindow::addToScene()
{
    QFileInfo fileInf = m_fileModel->fileInfo(m_ui->sourceBrowser->currentIndex());

    if (fileInf.isFile())
    {
        QPointF pos = QPointF(m_ui->graphViewer->horizontalScrollBar()->value(),
                              m_ui->graphViewer->verticalScrollBar()->value())
                    + m_ui->graphViewer->rect().center()
                    - QPointF(DEFAULT_FILE_VISUAL_WIDTH / 2,
                              DEFAULT_FILE_VISUAL_HEIGHT / 2);
        IScaObjectFile *objFile = new IScaObjectFile(fileInf);
        scene->addFileVisual(pos, objFile);
    }

    m_ui->ViewsTabs->setCurrentIndex(2);
}

void MainWindow::loadTextFile(const QString &code)
{
    QFileInfo fileInf = m_fileModel->fileInfo(m_ui->sourceBrowser->currentIndex());
    if (fileInf.size() > MAX_TEXT_FILE_SIZE)
    {
        QMessageBox::warning(this, ERROR_TOO_LARGE_TEXT_FILE_TITLE,
                             ERROR_TOO_LARGE_TEXT_FILE_MSG.arg(QString::number(fileInf.size())),
                             QMessageBox::Ok);
        return;
    }
    //Check if the file has already been opened
    //or it is not file at all
    if (!fileInf.isFile() || //path and encoding same
            (m_ui->textViewer->getCurrentPath() == fileInf.filePath()
            && code == m_ui->textViewer->getCurrentEncoding()))
    {
        return;
    }

    FileLoader *fLoader = new FileLoader();

    fLoader->openFile(fileInf.filePath());

    fLoader->loadToTextDoc(m_ui->textViewer->document(), code.toStdString().c_str());
    m_ui->textViewer->setCurrentPath(fileInf.filePath());
    m_ui->textViewer->setCurrentEncoding(code);

    m_ui->ViewsTabs->setCurrentIndex(0);
    fLoader->deleteLater();
}


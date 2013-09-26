#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    //Set up file model
    fileModel = new QFileSystemModel(this);
    fileModel->setRootPath("");
    m_ui->sourceBrowser->setModel(fileModel);

    m_ui->textViewer->setWordWrapMode(QTextOption::NoWrap);

    m_ui->sourceBrowser->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_ui->sourceBrowser, SIGNAL(customContextMenuRequested(QPoint)),
            m_ui->sourceBrowser, SLOT(ShowContextMenu(QPoint)));

    //Connect clicking on file to opening it in textViewer
    connect(m_ui->sourceBrowser, SIGNAL(openFile()),
            this, SLOT(loadTextFile()));
    connect(m_ui->openButton, SIGNAL(clicked()),
            this, SLOT(loadTextFile()));
    connect(m_ui->sourceBrowser, SIGNAL(doubleClicked(QModelIndex)),
            this, SLOT(loadTextFile()));
}

void MainWindow::loadTextFile()
{
    FileLoader *floader = new FileLoader();
    QFileInfo fileInf = fileModel->fileInfo(m_ui->sourceBrowser->currentIndex());

    floader->openFile(fileInf.filePath());

    floader->loadToTextDoc(m_ui->textViewer->document());
    floader->deleteLater();
}

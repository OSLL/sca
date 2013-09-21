#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    //Set up file model
    fileModel = new QFileSystemModel(this);
    fileModel->setRootPath("");
    m_ui->sourceBrowser->setModel(fileModel);

    //Connect clicking on file to opening it in textViewer
    connect(m_ui->sourceBrowser, &SourceBrowser::clicked,
            this, &MainWindow::loadTextFile);
}

void MainWindow::loadTextFile()
{
    QFileInfo fileInf = fileModel->fileInfo(m_ui->sourceBrowser->currentIndex());
    if (fileInf.isDir() || fileInf.isRoot())
        return;
    QFile file(fileInf.filePath());

    if (!file.open(QFile::ReadOnly))
    {
        QMessageBox::information(this, "Can\'t open file.", "Error opening " + fileInf.filePath(), QMessageBox::Ok);
    }
    QTextDocument *doc = new QTextDocument(m_ui->textViewer);
    doc->setPlainText(file.readAll());
    m_ui->textViewer->setDocument(doc);
}

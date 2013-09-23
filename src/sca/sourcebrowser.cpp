#include "sourcebrowser.h"

SourceBrowser::SourceBrowser(QWidget *parent) :
    QTreeView(parent)
{
    menu = new QMenu(this);
    QAction *open = menu->addAction("Open in Text Viewer");
    menu->addAction("Open in Binary Viewer")->setEnabled(false);
    menu->addAction("Add to scene")->setEnabled(false);
}

void SourceBrowser::setMenu(QMenu *_menu)
{
    menu->deleteLater();
    menu = _menu;
}

void SourceBrowser::ShowContextMenu(const QPoint &pos)
{
    //Move menu
    QPoint globalPos = viewport()->mapToGlobal(pos);

    //Get current item selected and check if it is file
    QFileSystemModel *fileModel = dynamic_cast<QFileSystemModel *>(this->model());
    if (fileModel)
    {
        if (!fileModel->fileInfo(this->currentIndex()).isFile())
        {
            menu->actions().at(0)->setEnabled(false);
        }
        else
        {
            menu->actions().at(0)->setEnabled(true);
        }
    }

    //Show menu and process input
    QAction *action = menu->exec(globalPos);
    if (!action)
    {
        return;
    }

    int index = menu->actions().indexOf(action);
    switch(index)
    {
    case 0: //"Open in Text Viewer"
        emit openFile();
        break;
    case 1: //"Open in Binary Viewer"
        emit openBinaryFile();
        break;
    case 2: //"Add to scene"
        emit addToScene();
        break;
    default:
        QMessageBox::information(this, "Wrong menu index", "Got wrong index:" + QString::number(index), QMessageBox::Ok);
        break;
    }
}

#include "sourcebrowser.h"

SourceBrowser::SourceBrowser(QWidget *parent) :
    QTreeView(parent)
{

}

void SourceBrowser::ShowContextMenu(const QPoint &pos)
{
    //Init menu
    QPoint globalPos = viewport()->mapToGlobal(pos);
    QMenu menu;
    QAction *open = menu.addAction("Open in TextViewer");

    //Get current item selected and check if it is file
    QFileSystemModel *fileModel = dynamic_cast<QFileSystemModel *>(this->model());
    if (fileModel)
    {
        if (!fileModel->fileInfo(this->currentIndex()).isFile())
        {
            open->setEnabled(false);
        }
    }

    //Show menu and process input
    QAction *action = menu.exec(globalPos);
    if (!action)
    {
        return;
    }
    if (action->text() == "Open in TextViewer")
    {
        emit openFile();
    }
    else
    {
        //Do something?
    }
}

#include "sourcebrowser.h"

SourceBrowser::SourceBrowser(QWidget *parent) :
    QTreeView(parent)
{

}

void SourceBrowser::ShowContextMenu(const QPoint &pos)
{
    QPoint globalPos = viewport()->mapToGlobal(pos);
    QMenu menu;
    menu.addAction("Open in TextViewer");
    QAction *action = menu.exec(globalPos);
    if (action->text() == "Open in TextViewer")
    {
        emit openFile();
    }
    else
    {
        //Do something?
    }
}

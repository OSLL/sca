#include "objecttextviewer.h"

ObjectTextViewer::ObjectTextViewer(QWidget *parent) :
    QTextEdit(parent)
{
    setReadOnly(true);
    QFontMetrics metrics(currentFont());
    setTabStopWidth(4 * metrics.width(' '));
}

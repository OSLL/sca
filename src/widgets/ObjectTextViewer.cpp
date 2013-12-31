/*
 * Copyright 2013    exzo0mex@gmail.com
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 3. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior written
 *    permission.
 *
 * The advertising clause requiring mention in adverts must never be included.
 */

/*! ---------------------------------------------------------------
 *
 * \file ObjectTextViewer.cpp
 * \brief ObjectTextViewer implementation
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */


#include "ObjectTextViewer.h"
#include <QDrag>
#include <QMimeData>
#include <QUrl>
#include <QList>
#include <QDebug>
#include <QTextBlock>
#include <QObjectUserData>
#include <QDragLeaveEvent>
#include <QFileInfo>
#include "../common/IScaObject.h"
#include "../common/IScaObjectFile.h"
#include "../common/IScaObjectTextBlock.h"
#include "../common/IScaObjectDirectory.h"
#include "../common/IScaObjectSymbol.h"
#include "../common/IScaObjectLine.h"
#include "../common/IScaObjectIdentifier.h"
#include "../common/IScaObjectBinaryBlock.h"
#include "../FileLoader.h"
#include "../NumericalConstants.h"
#include "../StringConstants.h"

ObjectTextViewer::ObjectTextViewer(QWidget *parent) :
    QTextEdit(parent), m_currentPath("")
{
    setReadOnly(true);
    QFontMetrics metrics(currentFont());
    setTabStopWidth(4 * metrics.width(' '));
}

void ObjectTextViewer::goToTextBlock(IScaObjectTextBlock *object)
{
    int start = object->getOffset();
    int end = object->getEndOffset();
    QTextCursor cur = textCursor();
    cur.clearSelection();
    qDebug() << "[ObjectTextViewer]: moving to pos: " << start << end;
    cur.setPosition(start, QTextCursor::MoveAnchor);
    cur.setPosition(end, QTextCursor::KeepAnchor);
    setTextCursor(cur);
    ensureCursorVisible();
}

void ObjectTextViewer::goToSymbol(IScaObjectSymbol *object)
{
    int start = object->getOffset();
    int end = start + 1;
    QTextCursor cur = textCursor();
    cur.clearSelection();
    qDebug() << "[ObjectTextViewer]: moving to pos: " << start << end;
    cur.setPosition(start, QTextCursor::MoveAnchor);
    cur.setPosition(end, QTextCursor::KeepAnchor);
    setTextCursor(cur);
    ensureCursorVisible();
}

void ObjectTextViewer::goToIdentiifier(IScaObjectIdentifier *object)
{
    //Same logics as in goToTextBlock()
    int start = object->getOffset();
    int end = object->getEndOffset();
    QTextCursor cur = textCursor();
    cur.clearSelection();
    qDebug() << "[ObjectTextViewer]: moving to pos: " << start << end;
    cur.setPosition(start, QTextCursor::MoveAnchor);
    cur.setPosition(end, QTextCursor::KeepAnchor);
    setTextCursor(cur);
    ensureCursorVisible();
}

void ObjectTextViewer::goToLine(IScaObjectLine *line)
{
    int lineNumber = line->getLineNumber();
    QTextCursor cursor = textCursor();
    cursor.clearSelection();
    cursor.setPosition(0, QTextCursor::MoveAnchor);
    qDebug() << "[ObjectTextViewer]: moving to line: " << lineNumber;
    cursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, lineNumber-1);
    cursor.select(QTextCursor::LineUnderCursor);
    setTextCursor(cursor);
    ensureCursorVisible();
}

void ObjectTextViewer::goToBinaryBlock(IScaObjectBinaryBlock *object)
{
    int start = object->getOffset();
    int end = start + object->getLength();
    QTextCursor cur = textCursor();
    cur.clearSelection();
    qDebug() << "[ObjectTextViewer]: moving to pos: " << start << end;
    cur.setPosition(start, QTextCursor::MoveAnchor);
    cur.setPosition(end, QTextCursor::KeepAnchor);
    setTextCursor(cur);
    ensureCursorVisible();
}

QString ObjectTextViewer::getCurrentPath() const
{
    return m_currentPath;
}

void ObjectTextViewer::setCurrentPath(const QString &value)
{
    m_currentPath = value;
}
QString ObjectTextViewer::getCurrentEncoding() const
{
    return m_currentEncoding;
}

void ObjectTextViewer::setCurrentEncoding(const QString &value)
{
    m_currentEncoding = value;
}

int ObjectTextViewer::currentLineNumber() const
{
    QTextCursor cursor = textCursor();
    cursor.movePosition(QTextCursor::StartOfLine);

    int lines = 1;
    while(cursor.positionInBlock()>0) {
        cursor.movePosition(QTextCursor::Up);
        lines++;
    }
    QTextBlock block = cursor.block().previous();

    while(block.isValid()) {
        lines += block.lineCount();
        block = block.previous();
    }
    return lines;
}

int ObjectTextViewer::symbolsInCurrentLine() const
{
    QTextCursor cursor = textCursor();
    return cursor.block().length();
}

void ObjectTextViewer::loadFromFile(const QString &path, const QString &code)
{
    int fileSize = QFileInfo(path).size();
    if (fileSize > MAX_TEXT_FILE_SIZE)
    {
        QMessageBox::warning(this, ERROR_TOO_LARGE_TEXT_FILE_TITLE,
                             ERROR_TOO_LARGE_TEXT_FILE_MSG.arg(QString::number(fileSize)),
                             QMessageBox::Ok);
        return;
    }

    if(getCurrentPath() == path)
    {
        return;
    }

    FileLoader *fLoader = new FileLoader();

    fLoader->openFile(path);

    fLoader->loadToTextDoc(document());
    setCurrentPath(path);
    setCurrentEncoding(code);

    fLoader->deleteLater();
}

void ObjectTextViewer::goToObject(IScaObject *object)
{
    QString newPath = object->getFile().absoluteFilePath();
    if (newPath != m_currentPath)
    {
        loadFromFile(newPath);
    }
    switch (object->getType())
    {
    case IScaObject::FILE:
        {
            break;
        }
    case IScaObject::DIRECTORY:
        {
            break;
        }
    case IScaObject::TEXTBLOCK:
        {
            IScaObjectTextBlock *obj = static_cast<IScaObjectTextBlock *>(object);
            goToTextBlock(obj);
            break;
        }
    case IScaObject::BINARYBLOCK:
        {
            IScaObjectBinaryBlock *obj = static_cast<IScaObjectBinaryBlock *>(object);
            goToBinaryBlock(obj);
            break;
        }
    case IScaObject::LINE:
        {
            IScaObjectLine *obj = static_cast<IScaObjectLine *>(object);
            goToLine(obj);
            break;
        }
    case IScaObject::IDENTIFIER:
        {
            IScaObjectIdentifier *obj = static_cast<IScaObjectIdentifier *>(object);
            goToIdentiifier(obj);
            break;
        }
    case IScaObject::SYMBOL:
        {
            IScaObjectSymbol *obj = static_cast<IScaObjectSymbol *>(object);
            goToSymbol(obj);
            break;
        }
    case IScaObject::LINK:
        {
            break;
        }
    default:
        {
            qDebug() << "[ObjectTextViewer]: unknown type to go to.";
            break;
        }
    }
}

QMimeData *ObjectTextViewer::createMimeDataFromSelection() const
{
    QMimeData *mime = new QMimeData();
    QTextCursor cursor = textCursor();

    mime->setText(cursor.selectedText());
    mime->setProperty("fromPath", getCurrentPath());
    mime->setProperty("position", cursor.selectionStart());
    mime->setProperty("length", cursor.selectionEnd() - cursor.selectionStart());
    mime->setProperty("posInLine", cursor.positionInBlock());
    mime->setProperty("endOffset", cursor.selectionEnd());

    int line = currentLineNumber();
    mime->setProperty("line", line);
    mime->setProperty("lineLength", symbolsInCurrentLine() - 1);

    qDebug() << "FromPath: " << getCurrentPath();
    qDebug() << "Line: " << currentLineNumber();
    qDebug() << "Symbols: " << symbolsInCurrentLine();
    qDebug() << "Position in line: " << cursor.positionInBlock();
    qDebug() << "Pos: " << cursor.selectionStart();
    qDebug() << "Lenght: " << cursor.selectionEnd() - cursor.selectionStart();
    qDebug() << "Text: " << cursor.selectedText();
    return mime;
}

void ObjectTextViewer::dragEnterEvent(QDragEnterEvent *event)
{
    if (!event->mimeData()->hasUrls())
    {
        return;
    }
    QString path = event->mimeData()->urls().at(0).toLocalFile();
    event->setAccepted(QFileInfo(path).isFile());
}

void ObjectTextViewer::dragMoveEvent(QDragMoveEvent *)
{
}

void ObjectTextViewer::dropEvent(QDropEvent *event)
{
    const QMimeData *mime = event->mimeData();
    QString path = mime->urls().at(0).toLocalFile();
    loadFromFile(path);
}

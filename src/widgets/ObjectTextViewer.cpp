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
#include "FileLoader.h"
#include "NumericalConstants.h"
#include "StringConstants.h"

ObjectTextViewer::ObjectTextViewer(QWidget *parent) :
    QTextEdit(parent), m_currentPath("")
{
    setReadOnly(true);
    QFontMetrics metrics(currentFont());
    setTabStopWidth(4 * metrics.width(' '));
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

QMimeData *ObjectTextViewer::createMimeDataFromSelection() const
{
    QMimeData *mime = new QMimeData();
    QTextCursor cursor = textCursor();

    mime->setText(textCursor().selectedText());
    QList<QUrl> urls;
    urls.push_back(QUrl::fromLocalFile(getCurrentPath()));
    mime->setUrls(urls);
    mime->setText(cursor.selectedText());
    mime->setProperty("position", cursor.position());
    mime->setProperty("length", cursor.selectionEnd() - cursor.selectionStart());
    mime->setProperty("posInLine", cursor.positionInBlock());

    int line = currentLineNumber();
    mime->setProperty("line", line);
    mime->setProperty("lineLength", symbolsInCurrentLine() - 1);

    qDebug() << "Line: " << currentLineNumber();
    qDebug() << "Symbols: " << symbolsInCurrentLine();
    qDebug() << "Position in line: " << cursor.positionInBlock();
    qDebug() << "Pos: " << cursor.position();
    qDebug() << "Lenght: " << cursor.selectionEnd() - cursor.selectionStart();
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

void ObjectTextViewer::dragMoveEvent(QDragMoveEvent *event)
{
}

void ObjectTextViewer::dropEvent(QDropEvent *event)
{
    const QMimeData *mime = event->mimeData();
    QString path = mime->urls().at(0).toLocalFile();
    loadFromFile(path);
}

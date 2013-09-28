/*
 * Copyright 2013    
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
 * \file FileLoader.cpp
 * \brief FileLoader implementation
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */

#include "FileLoader.h"

FileLoader::FileLoader()
{
    m_file = 0;
}

FileLoader::~FileLoader()
{
    if (m_file != NULL)
    {
        qDebug() << "Deleting loader of " << QFileInfo(*m_file).filePath();
    }
    deletemFile();
}

void FileLoader::closeFile()
{
    if (m_file != NULL)
    {
        if (m_file->isOpen())
        {
            m_file->close();
        }
    }
}

void FileLoader::deletemFile()
{
    if (m_file != NULL)
    {
        closeFile();
        m_file->deleteLater();
    }
}

void FileLoader::openFile(const QString &path)
{
    deletemFile();
    if (!QFileInfo(path).isFile())
    {
        return;
    }
    m_file = new QFile(path);
    if (!m_file->open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(0, "Can\'t open file.",
                             "Error opening " + path, QMessageBox::Ok);
        return;
    }
}

void FileLoader::loadToTextDoc(QTextDocument *doc)
{
    if (m_file == NULL)
    {
        return;
    }
    if (!m_file->isReadable())
    {
        return;
    }
    doc->setPlainText(m_file->readAll());
}

QString FileLoader::getPath()
{
    if (!m_file)
        return 0;
    QFileInfo fileInfo(*m_file);
    return fileInfo.filePath();
}

FileLoader::FileLoader(const FileLoader &obj) :
   QObject(obj.parent()), m_file(obj.m_file)
{
}

FileLoader &FileLoader::operator=(const FileLoader &obj)
{
    deletemFile();
    m_file = obj.m_file;
    return *this;
}

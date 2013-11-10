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
 * \file ObjectTextViewer.h
 * \brief Header of ObjectTextViewer
 * \todo add comment here
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */


#ifndef _ObjectTextViewer_H_FD315731_667E_45A5_AA99_53E0B6BD49D1_INCLUDED_
#define _ObjectTextViewer_H_FD315731_667E_45A5_AA99_53E0B6BD49D1_INCLUDED_

/*!
 * Class description. May use HTML formatting
 *
 */

#include <QTextEdit>
class QDrag;

class ObjectTextViewer : public QTextEdit
{
    Q_OBJECT
public:
    explicit ObjectTextViewer(QWidget *parent = 0);
    
    QString getCurrentPath() const;
    void setCurrentPath(const QString &value);

    QString getCurrentEncoding() const;
    void setCurrentEncoding(const QString &value);

    int currentLineNumber() const;
    int symbolsInCurrentLine() const;
signals:
    
public slots:

protected:
    QMimeData *createMimeDataFromSelection() const;
private:
    QString m_currentPath;
    QString m_currentEncoding;
};

#endif //_ObjectTextViewer_H_FD315731_667E_45A5_AA99_53E0B6BD49D1_INCLUDED_

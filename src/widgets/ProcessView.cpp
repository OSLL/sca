/*
 * Copyright 2014  Zo0MER  exzo0mex@gmail.com
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

#include "ProcessView.h"

#include <QDebug>
#ifdef WIN32
#include <windows.h>
#endif
/*! ---------------------------------------------------------------
 *
 * \file ProcessView.cpp
 * \brief ProcessView implementation
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */


ProcessView::ProcessView(QWidget *parent):
    ObjectTextViewer(parent),
    m_process(new QProcess(this))
{
    connect(m_process, SIGNAL(readyRead()), this, SLOT(readProcessOutput()));
}

ProcessView::~ProcessView()
{
    m_process->terminate();
}

void ProcessView::execute(const QString &command)
{
    if(m_process->state() != QProcess::NotRunning)
    {
        return;
    }    
#ifdef WIN32
    m_process->start("cmd\n");
    m_process->write("chcp 65001\n");
    QString com = command;
    com.replace("/", "\\");
    m_process->write(QString(com + '\n').toStdString().c_str());
    m_process->closeWriteChannel();
#else
    m_process->start(command);
#endif

    qDebug() << "[ProcessView]: Runned command: " << command;
}

void ProcessView::readProcessOutput()
{
    QString processOut = QString::fromUtf8(m_process->readAllStandardOutput());
    qDebug() << "[Process]: " << processOut;
    append(processOut);
}

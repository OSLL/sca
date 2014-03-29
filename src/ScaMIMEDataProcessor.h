/*
 * Copyright 2013  Leonid Skorospelov  leosko94@gmail.com
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
 * \file ScaMIMEDataProcessor.h
 * \brief Header of ScaMIMEDataProcessor
 * \todo add comment here
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */


#ifndef _ScaMIMEDataProcessor_H_86D4F543_BF93_48CF_9046_4E6050001129_INCLUDED_
#define _ScaMIMEDataProcessor_H_86D4F543_BF93_48CF_9046_4E6050001129_INCLUDED_

/*!
 * Class description. May use HTML formatting
 *
 */

#include "common/IScaObject.h"
#include "ObjectCreator.h"
#include <QFileInfo>
class QMimeData;

class ScaMimeDataProcessor
{
public:
  ScaMimeDataProcessor(const QMimeData *mime);

  ~ScaMimeDataProcessor();
  
  const QMimeData *getData() const;
  void setData(const QMimeData *data);

  IScaObject *makeObject();

private:
  ObjectCreator *m_creator;
  const QMimeData *m_data;
  QString m_filePath;
  QFileInfo m_fileInfo;

}; // class ScaMIMEDataProcessor
  

#endif //_ScaMIMEDataProcessor_H_86D4F543_BF93_48CF_9046_4E6050001129_INCLUDED_


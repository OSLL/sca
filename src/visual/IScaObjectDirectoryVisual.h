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
 * \file IScaObjectDirectoryVisual.h
 * \brief Header of IScaObjectDirectoryVisual
 * \todo add comment here
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */


#ifndef _IScaObjectDirectoryVisual_H_6523A4C7_F3E6_4099_9DDC_CF5C5F83A687_INCLUDED_
#define _IScaObjectDirectoryVisual_H_6523A4C7_F3E6_4099_9DDC_CF5C5F83A687_INCLUDED_

#include "Node.h"
#include "common/IScaObjectDirectory.h"

/*!
 * Class description. May use HTML formatting
 *
 */
class IScaObjectDirectoryVisual : public Node
{
public:
  explicit IScaObjectDirectoryVisual(const QPointF &coords, IScaObjectDirectory *object);

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

  ~IScaObjectDirectoryVisual();
  
private:    
  IScaObjectDirectoryVisual(const IScaObjectDirectoryVisual& obj);
  IScaObjectDirectoryVisual &operator=(const IScaObjectDirectoryVisual& obj);

}; // class IScaObjectDirectoryVisual
  

#endif //_IScaObjectDirectoryVisual_H_6523A4C7_F3E6_4099_9DDC_CF5C5F83A687_INCLUDED_


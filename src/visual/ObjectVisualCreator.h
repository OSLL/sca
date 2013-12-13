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
 * \file VisualObjectCreator.h
 * \brief Header of VisualObjectCreator
 * \todo create comment here
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */


#ifndef _VisualObjectCreator_H_B48E3ABD_CC4B_4D94_8451_B779B955AD61_INCLUDED_
#define _VisualObjectCreator_H_B48E3ABD_CC4B_4D94_8451_B779B955AD61_INCLUDED_
#include "visual/ObjectVisual.h"
#include "visual/IScaObjectBinaryBlockVisual.h"
#include "visual/IScaObjectDirectoryVisual.h"
#include "visual/IScaObjectFileVisual.h"
#include "visual/IScaObjectIdentifierVisual.h"
#include "visual/IScaObjectLineVisual.h"
#include "visual/IScaObjectSymbolVisual.h"
#include "visual/IScaObjectTextBlockVisual.h"
#include "visual/LinkVisual.h"
/*!
 * Class description. May use HTML formatting
 *
 */
class ObjectVisualCreator
{
public:
    ObjectVisualCreator();

    ~ObjectVisualCreator();

    IScaObjectFileVisual *createFileVisual(IScaObject *object);
    IScaObjectSymbolVisual *createSymbolVisual(IScaObject *object);
    IScaObjectLineVisual *createLineVisual(IScaObject *object);
    IScaObjectBinaryBlockVisual *createBinaryBlockVisual(IScaObject *object);
    IScaObjectIdentifierVisual *createIdentifierVisual(IScaObject *object);
    IScaObjectDirectoryVisual *createDirVisual(IScaObject *object);
    IScaObjectTextBlockVisual *createTextBlockVisual(IScaObject *object);
    LinkVisual *createLinkVisual(IScaObject *object);
    ObjectVisual *createObjectVisual(IScaObject *object);
private:
}; // class VisualObjectCreator


#endif //_VisualObjectCreator_H_B48E3ABD_CC4B_4D94_8451_B779B955AD61_INCLUDED_

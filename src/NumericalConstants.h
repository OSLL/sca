/*! ---------------------------------------------------------------
 * \file NumericalConstants.h
 * \brief File of numerical constats
 * \todo add comment here
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */

#ifndef _NumericalConstants_H_B55D9E18_0180_4F9B_B243_BC6FD77B58FD_INCLUDED_
#define _NumericalConstants_H_B55D9E18_0180_4F9B_B243_BC6FD77B58FD_INCLUDED_

/* ---------------------------------------------------------------- *
*NumericalConstants.h
* ---------------------------------------------------------------- */
#include <QColor>
#include <QPen>

const qreal PI = 3.1415926;

//Alerts consts
const long MAX_BINARY_FILE_SIZE = 50*1024*1024;
const long MAX_TEXT_FILE_SIZE = 0.4*1024*1024;

//QHexEdit consts
const int HEXCHARS_IN_LINE = 47;
const int GAP_ADR_HEX = 10;
const int GAP_HEX_ASCII = 16;
const int BYTES_PER_LINE = 16;

//Visual consts
const int DEFAULT_SCENE_WIDTH = 2000;
const int DEFAULT_SCENE_HEIGHT = 1000;

const double SELECTION_COLOR_DELTA = 0.5;

const QColor DEFAULT_NODE_COLOR(150, 150, 150);
const QColor FILTERED_NODE_COLOR(Qt::red);
const int DEFAULT_NODE_WIDTH = 20;
const int DEFAULT_NODE_HEIGHT = 20;

const QColor DEFAULT_FILE_COLOR(30, 255, 255);
const QColor FILTERED_FILE_COLOR(Qt::red);
const int DEFAULT_FILE_VISUAL_WIDTH = 20;
const int DEFAULT_FILE_VISUAL_HEIGHT = 20;

const QColor DEFAULT_DIR_COLOR(30, 100, 255);
const QColor FILTERED_DIR_COLOR(Qt::red);
const int DEFAULT_DIR_VISUAL_WIDTH = 25;
const int DEFAULT_DIR_VISUAL_HEIGHT = 25;

const QColor DEFAULT_TEXT_BLOCK_COLOR(200, 100, 50);
const QColor FILTERED_TEXT_BLOCK_COLOR(Qt::red);
const int DEFAULT_TEXT_BLOCK_VISUAL_WIDTH = 20;
const int DEFAULT_TEXT_BLOCK_VISUAL_HEIGHT = 15;

const QColor DEFAULT_BINARY_BLOCK_COLOR(50, 200, 50);
const QColor FILTERED_BINARY_BLOCK_COLOR(Qt::red);
const int DEFAULT_BINARY_BLOCK_VISUAL_WIDTH = 20;
const int DEFAULT_BINARY_BLOCK_VISUAL_HEIGHT = 15;

const QColor DEFAULT_IDENTIFIER_COLOR(10, 100, 50);
const QColor FILTERED_IDENTIFIER_COLOR(Qt::red);
const int DEFAULT_IDENTIFIER_VISUAL_WIDTH = 15;
const int DEFAULT_IDENTIFIER_VISUAL_HEIGHT = 15;

const QColor DEFAULT_LINE_COLOR(70, 50, 100);
const QColor FILTERED_LINE_COLOR(Qt::red);
const int DEFAULT_LINE_VISUAL_WIDTH = 20;
const int DEFAULT_LINE_VISUAL_HEIGHT = 10;

const QColor DEFAULT_SYMBOL_COLOR(10, 200, 50);
const QColor FILTERED_SYMBOL_COLOR(Qt::red);
const int DEFAULT_SYMBOL_VISUAL_WIDTH = 10;
const int DEFAULT_SYMBOL_VISUAL_HEIGHT = 15;

const int MAX_TITLE_LENGTH = 15;

const int DEFAULT_ARROW_WIDTH  = 5;
const int DEFAULT_ARROW_HEIGHT = 8;

const int DEFAULT_LINK_WIDTH = 3;
const int LINE_SELECTION_DELTA = 15;

const qreal MIN_LINK_LENGTH = 15;

const QPen DEFAULT_LINK_PEN(QBrush(Qt::black), DEFAULT_LINK_WIDTH, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);
const QPen SELECTED_LINK_PEN(QBrush(QColor(80,80,80)), DEFAULT_LINK_WIDTH, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);
const QPen FILTERED_LINK_PEN(QBrush(QColor(155, 0, 186)), DEFAULT_LINK_WIDTH, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);

//Default export image size
const int DEFAULT_IMAGE_WIDTH = 800;
const int DEFAULT_IMAGE_HEIGHT = 600;

enum GraphModelRole{
    rawObjectRole = Qt::UserRole,
    highlightRole = Qt::UserRole + 1,
    objectIdListRole = Qt::UserRole + 2
};

const int GRAPH_TABLE_PROXY_COLUMN_COUNT = 5;
#endif //_NumericalConstants_H_B55D9E18_0180_4F9B_B243_BC6FD77B58FD_INCLUDED_

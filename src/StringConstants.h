/*! ---------------------------------------------------------------
 * \file StringConstats.h
 * /brief File of string constats
 * \todo add comment here
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */


#ifndef _StringConstats_H_B7EF2363_6151_4D99_88F1_D6C1BE57A090_INCLUDED_
#define _StringConstats_H_B7EF2363_6151_4D99_88F1_D6C1BE57A090_INCLUDED_

/* ---------------------------------------------------------------- *
*StringCostants.h
* ---------------------------------------------------------------- */

#include <QString>
#include "NumericalConstants.h"

//[Common context menu strings]
const QString OPEN_IN_TEXT_VIEWER = "Open in Text Viewer";
const QString OPEN_IN_TEXT_VIEWER_AS = "Open in Text Viewer As";
const QString OPEN_IN_BINARY_VIEWER = "Open in Binary Viewer";
const QString ADD_TO_SCENE = "Add to scene";
const QString ANNOTATE_OBJECT = "Edit annotation";
//[End common menu strings]

//[Error messages]
const QString ERROR_TOO_LARGE_BINARY_FILE_TITLE = "File is too large.";
const QString ERROR_TOO_LARGE_BINARY_FILE_MSG =
        QString("This file is too large to open. (%1 bytes)") +
        QString("\nConsider opening binary file no larger than %1 bytes.").arg(MAX_BINARY_FILE_SIZE);

const QString ERROR_TOO_LARGE_TEXT_FILE_TITLE = "File is too large.";
const QString ERROR_TOO_LARGE_TEXT_FILE_MSG =
        QString("This file is too large to open. (%1 bytes)") +
        QString("\nConsider opening text file no larger than %1 bytes.").arg(MAX_TEXT_FILE_SIZE);

const QString ERROR_OPENING_FILE_TITLE = "Can\'t open file.";
const QString ERROR_OPENING_FILE_MSG = "Error opening %1";
const QString LOG_PATTERN = "%1: %2\n";
//[End error messages]

//[GraphView context menu strings]
const QString CONNECT_OBJECTS = "Connect";
const QString TO_TEXT_BLOCK = "Set as text block";
const QString TO_IDENTIFIER = "Set as identifier";
const QString TO_BINARY_BLOCK = "Set as binary block";
const QString DELETE_ITEMS = "Delete selected";
const QString LEFT_ARROW = "Left arrow";
const QString RIGHT_ARROW = "Right arrow";
const QString EDIT_ANNOTATION = "Edit annotation";
const QString EDIT_ANNOTATION_LABEL = "Enter annotation: ";
//[End GraphView's strings]

//[Header data strings]
const QString OBJECT_TYPE = "Type";
const QString OBJECT_PATH = "Path";
const QString OBJECT_NAME = "Filename";
const QString OBJECT_CONTENT = "Content";
const QString OBJECT_ANNOTATION = "Annotation";
//[End header data strings]

//[Encoding list]
const QString UTF8 = "UTF-8";
const QString CP866 = "CP-866";
const QString ISO885915 = "ISO-8859-15";
//[End encoding list]

//[Preferences]
const QString DEFAULT_ENCODING = UTF8;
const QString APPLICATION_VERSION = "0.1";
const QString APPLICATION_AUTORS = QString("Kirill Krinkin\n") +
        QString("Mark Zaslavskiy\n") +
        QString("Leonid Skorospelov\n") +
        QString("Nikita Razdobreev");
const QString APPLICATION_NAME = "Source Code Analyzer";
const QString APPLICATION_COPYRIGHT = "\xA9 Open Source & Linux Lab, 2013";
const QString MAINWINDOW_TITLE = APPLICATION_NAME;
//[End preferences]

//[MIMEData]
const QString BINARY_DATA = "Binary Data";
const QString SCA_OBJECT = "Object";
const QString SCA_DIRECTORY = "Directory";
const QString SCA_FILE = "File";
const QString SCA_IDENTIFIER = "Identifier";
const QString SCA_TEXTBLOCK = "Textblock";
const QString SCA_BINARYBLOCK = "Binaryblock";
const QString SCA_LINE = "Line";
const QString SCA_SYMBOL = "Symbol";
const QString SCA_LINK = "Link";
const QString SCA_GROUP = "Group";
const QString SCA_UNKNOWN = "Unknown type";
//[End MIMEData]

//[About text]
const QString ABOUT_TITLE = QString("About %1").arg(APPLICATION_NAME);
const QString ABOUT_TEXT =
        QString("%1 - tool to maintain base of sources.\n").arg(APPLICATION_NAME) +
        QString("Current version: %1\n").arg(APPLICATION_VERSION) +
        QString("Made by: \n%2\n").arg(APPLICATION_AUTORS) +
        QString("%3").arg(APPLICATION_COPYRIGHT);
//[End About text]

//[Files paths]
const QString HELP_PATH = "/resources/sca_help.html";
const QString LOGO_PATH = ":logo/icons/logo.png";
const QString LOG_PATH = "log.txt";
//[End files paths]

//[GraphFilter strings]
const QString VALID_REGEXP_STATE = "RegExp: OK";
const QString INVALID_REGEXP_STATE = "RegExp: NOT OK";
const QString OBJECT_INFO_PATTERN = "Type:%1,Filename:%2,Abs.Path:%3,Annotation:%4,Content:%5";
const QString DEFAULT_FILTER_REGEXP = OBJECT_INFO_PATTERN.arg("*").arg("*").arg("*").arg("*").arg("*");
const QString GRAPH_FILTER_TITLE = "Advanced graph filter";
const QString BOOL_CONDITIONS("OR;AND;NOT");
//[End GraphFilter strings]

//[Object info patterns strings]
const QString OBJECT_TOOLTIP_PATTERN =  QString("Type: %1 <br />")
                                    + QString("Filename: %2 <br />")
                                    + QString("Path: %3 <br />")
                                    + QString("Annotation: %4 <br />")
                                    + QString("Content: %5");
//[End Object info patterns strings]

//[GraphSaver create tables strings]
const QString SQL_CREATE_NODE_TABLE = "CREATE TABLE node_table ("
        "id integer PRIMARY KEY, "
        "line integer,"
        "offset integer,"
        "endoffset integer,"
        "length integer,"
        "path TEXT, "
        "text TEXT, "
        "data BLOB, "
        "annotation TEXT"
        ");";
const QString SQL_CREATE_LINK_TABLE = "CREATE TABLE link_table ("
        "id integer PRIMARY KEY, "
        "source integer, "
        "destin integer, "
        "annotation TEXT, "
        "FOREIGN KEY(source) REFERENCES node_table(id), "
        "FOREIGN KEY(destin) REFERENCES node_table(id) "
        ");";
const QString SQL_CREATE_NODEVISUAL_TABLE = "CREATE TABLE nodeVisual_table ("
        "id integer PRIMARY KEY, "
        "posX real, "
        "posY real "
        ");";
const QString SQL_CREATE_LINKVISUAL_TABLE = "CREATE TABLE linkVisual_table ("
        "id integer PRIMARY KEY, "
        "sourceArrow BOOLEAN, "
        "destinArrow BOOLEAN"
        ");";
const QString SQL_CREATE_TYPE_TABLE = "CREATE TABLE type_table ("
        "id integer, "
        "type integer, "
        "FOREIGN KEY(id) REFERENCES node_table(id)"
        ");";
//[End GraphSaver create tables strings]

//[GraphSaver insert strings]
const QString SQL_INSERT_NODE_PATTERN = "INSERT INTO node_table VALUES("
        ":id,"
        ":line,"
        ":offset,"
        ":endoffset,"
        ":length,"
        ":path,"
        ":text,"
        ":data,"
        ":annotation"
        ");";
const QString SQL_INSERT_LINK_PATTERN = "INSERT INTO link_table VALUES("
        ":id,"
        ":source,"
        ":destin,"
        ":annotation"
        ");";
const QString SQL_INSERT_NODEVISUAL_PATTERN = "INSERT INTO nodeVisual_table VALUES("
        ":id,"
        ":posX,"
        ":posY"
        ");";
const QString SQL_INSERT_LINKVISUAL_PATTERN = "INSERT INTO linkVisual_table VALUES("
        ":id,"
        ":sourceArrow,"
        ":destinArrow"
        ");";
const QString SQL_INSERT_TYPE_PATTERN = "INSERT INTO type_table VALUES("
        ":id,"
        ":type"
        ");";
//[End GraphSaver insert strings]

//[GraphLoader select strings]
const QString SQL_SELECT_NODE_TABLE       = "SELECT * FROM node_table";
const QString SQL_SELECT_LINK_TABLE       = "SELECT * FROM link_table";
const QString SQL_SELECT_NODEVISUAL_TABLE = "SELECT * FROM nodeVisual_table";
const QString SQL_SELECT_LINKVISUAL_TABLE = "SELECT * FROM linkVisual_table";
const QString SQL_SELECT_TYPE_TABLE       = "SELECT * FROM type_table";
const QString SQL_SELECT_NODE_TYPE_TABLES = "SELECT * FROM node_table "
        " INNER JOIN type_table ON node_table.id = type_table.id";
//[GraphLoader select strings]


#endif // _StringConstats_H_B7EF2363_6151_4D99_88F1_D6C1BE57A090_INCLUDED_

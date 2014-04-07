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
const QString WARNING_LARGE_BINARY_FILE_TITLE = "Large binary file";
const QString WARNING_LARGE_BINARY_FILE_TEXT = "File is too big to show, only first 15 MB are shown.";
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
const QString CREATE_GROUP = "Create group";
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
const QString APPLICATION_VERSION = "0.1.5";
const QString APPLICATION_AUTORS =
        QString("Kirill Krinkin\n") +
        QString("Mark Zaslavskiy\n") +
        QString("Leonid Skorospelov\n") +
        QString("Nikita Razdobreev");
const QString APPLICATION_NAME = "Source Code Analyzer";
const QString APPLICATION_COPYRIGHT = "\xA9 Open Source & Linux Lab, 2013";
const QString MAINWINDOW_TITLE = "%1 - " + APPLICATION_NAME;
const QString DEFAULT_NEW_FILE_NAME = "New graph.gm";
const QString SAVE_CHANGED_FILE_QUESTION_TITLE = "Save changes?";
const QString SAVE_CHANGED_FILE_QUESTION_TEXT = "%1 has been changed. Do you want to save changes?";
const QString FILE_SAVE_SUCCESSFUL = "File saved successfully.";
//[End preferences]

//[MIMEData]
const QString BINARY_DATA = "Binary Data";
const QString POSITION = "position";
const QString LENGHT = "lenght";
const QString POS_IN_LINE = "posInLine";
const QString LINE_NUMBER = "line";
const QString LINE_LENGHT = "lineLenght";
const QString END_OFFSET = "endOffset";
const QString FROM_PATH = "fromPath";

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

//[Object info patterns strings]
const QString OBJECT_TOOLTIP_PATTERN =  QString("Type: %1 <br />")
                                    + QString("Filename: %2 <br />")
                                    + QString("Path: %3 <br />")
                                    + QString("Annotation: %4 <br />")
                                    + QString("Content: %5");
const QString OBJECT_INFO_PATTERN = "Type:%1,Filename:%2,Abs.Path:%3,Annotation:%4,Content:%5";
//[End Object info patterns strings]

//[GraphFilter strings]
const QString VALID_REGEXP_STATE = "RegExp: OK";
const QString INVALID_REGEXP_STATE = "RegExp: NOT OK";
const QString DEFAULT_FILTER_REGEXP = OBJECT_INFO_PATTERN.arg("*").arg("*").arg("*").arg("*").arg("*");
const QString GRAPH_FILTER_TITLE = "Advanced graph filter";
const QString BOOL_CONDITIONS("OR;AND;NOT");
//[End GraphFilter strings]

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
        "annotation TEXT, "
        "shown BOOLEAN,"
        "ids TEXT"
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
        "posY real, "
        "colorR integer, "
        "colorG integer, "
        "colorB integer, "
        "width integer, "
        "height integer, "
        "firstPosX, "
        "firstPosY "
        ");";
const QString SQL_CREATE_LINKVISUAL_TABLE = "CREATE TABLE linkVisual_table ("
        "id integer PRIMARY KEY, "
        "sourceArrow BOOLEAN, "
        "destinArrow BOOLEAN, "
        "colorR integer, "
        "colorG integer, "
        "colorB integer"
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
        ":annotation,"
        ":shown,"
        ":ids"
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
        ":posY,"
        ":colorR,"
        ":colorG,"
        ":colorB,"
        ":width,"
        ":height,"
        ":firstPosX,"
        ":firstPosY"
        ");";
const QString SQL_INSERT_LINKVISUAL_PATTERN = "INSERT INTO linkVisual_table VALUES("
        ":id,"
        ":sourceArrow,"
        ":destinArrow,"
        ":colorR,"
        ":colorG,"
        ":colorB"
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

//[Property browser string]
const QString PROPERTY_TYPE         = "Type";
const QString PROPERTY_FILEPATH     = "Path";
const QString PROPERTY_ANNOTATION   = "Annotation";
const QString PROPERTY_LENGTH       = "Length";
const QString PROPERTY_OFFSET       = "Offset";
const QString PROPERTY_DATA         = "Data";
const QString PROPERTY_ENDOFFSET    = "End offset";
const QString PROPERTY_TEXT         = "Text";
const QString PROPERTY_IDENTIFIER   = "Identifier";
const QString PROPERTY_SYMBOL       = "Symbol";
const QString PROPERTY_LINE_NUMBER  = "Line number";
const QString PROPERTY_LINE         = "Line";
const QString PROPERTY_POSITION_X   = "Position X";
const QString PROPERTY_POSITION_Y   = "Position Y";
const QString PROPERTY_COLOR        = "Color";
const QString PROPERTY_SIZE         = "Size";
const QString PROPERTY_OBJECT_FROM  = "Object #1";
const QString PROPERTY_OBJECT_TO    = "Object #2";
//[End property browser strings]

//[Run commands strings]
const QString RUN_CUSTOM_COMMAND_TITLE = "Run custom command";
const QString RUN_CUSTOM_COMMAND_TEXT = "Enter command: ";
const QString ADD_NEW_COMMAND_TITLE = "New command";
const QString EDIT_COMMAND_TITLE = "Edit command";
//[End run commands strings]

#endif // _StringConstats_H_B7EF2363_6151_4D99_88F1_D6C1BE57A090_INCLUDED_

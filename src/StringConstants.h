/*! ---------------------------------------------------------------
 * \file StringConstats.h
 * \brief File of string constats
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
//[End error messages]

//[GraphView context menu strings]
const QString TO_TEXT_BLOCK = "Set as text block";
const QString TO_IDENTIFIER = "Set as identifier";
const QString TO_BINARY_BLOCK = "Set as binary block";
//[End GraphView's strings]

//[Encoding list]
const QString UTF8 = "UTF-8";
const QString CP866 = "CP-866";
const QString ISO885915 = "ISO-8859-15";
//[End encoding list]

//[Preferences]
const QString DEFAULT_ENCODING = UTF8;
//[End preferences]

#endif // _StringConstats_H_B7EF2363_6151_4D99_88F1_D6C1BE57A090_INCLUDED_

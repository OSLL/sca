QT += core gui widgets declarative

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    sourcebrowser.cpp \
    objecttextviewer.cpp \
    FileLoader.cpp \
    SourceBrowserMenu.cpp \
    common/IScaObject.cpp \
    common/IScaObjectFile.cpp \
    common/IScaObjectBinary.cpp \
    common/IScaObjectSymbol.cpp \
    common/IScaObjectLine.cpp \
    common/IScaObjectBlock.cpp \
    common/IScaObjectIdentifier.cpp

HEADERS += \
    mainwindow.h \
    sourcebrowser.h \
    objecttextviewer.h \
    FileLoader.h \
    SourceBrowserMenu.h \
    StringConstants.h \
    common/IScaObject.h \
    common/IScaObjectFile.h \
    common/IScaObjectSymbol.h \
    common/IScaObjectLine.h \
    common/IScaObjectBlock.h \
    common/IScaObjectIdentifier.h

FORMS += \
    mainwindow.ui

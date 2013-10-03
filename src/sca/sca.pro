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
    common/IScaObjectText.cpp

HEADERS += \
    mainwindow.h \
    sourcebrowser.h \
    objecttextviewer.h \
    FileLoader.h \
    SourceBrowserMenu.h \
    StringConstants.h \
    common/IScaObject.h \
    common/IScaObjectFile.h \
    common/IScaObjectText.h

FORMS += \
    mainwindow.ui

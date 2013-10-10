QT += core gui declarative

SOURCES += \
    main.cpp \
    FileLoader.cpp \
    SourceBrowserMenu.cpp \
    common/IScaObject.cpp \
    common/IScaObjectFile.cpp \
    common/IScaObjectSymbol.cpp \
    common/IScaObjectLine.cpp \
    common/IScaObjectBlock.cpp \
    common/IScaObjectIdentifier.cpp \
    common/Link.cpp \
    MainWindow.cpp \
    ObjectTextViewer.cpp \
    SourceBrowser.cpp

HEADERS += \
    FileLoader.h \
    SourceBrowserMenu.h \
    StringConstants.h \
    common/IScaObject.h \
    common/IScaObjectFile.h \
    common/IScaObjectSymbol.h \
    common/IScaObjectLine.h \
    common/IScaObjectBlock.h \
    common/IScaObjectIdentifier.h \
    common/Link.h \
    MainWindow.h \
    ObjectTextViewer.h \
    SourceBrowser.h

FORMS += \
    mainwindow.ui

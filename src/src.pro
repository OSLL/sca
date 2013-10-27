TEMPLATE = app
TARGET = sca

target.path = /opt/sca/

INSTALLS += target


OBJECTS_DIR = .obj
MOC_DIR = .moc

QT += core gui declarative

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    main.cpp \
    FileLoader.cpp \
    common/IScaObject.cpp \
    common/IScaObjectFile.cpp \
    common/IScaObjectSymbol.cpp \
    common/IScaObjectLine.cpp \
    common/IScaObjectBlock.cpp \
    common/IScaObjectIdentifier.cpp \
    common/Link.cpp \
    MainWindow.cpp \
    widgets/SourceBrowser.cpp \
    widgets/ObjectTextViewer.cpp \
    widgets/xbytearray.cpp \
    widgets/qhexedit_p.cpp \
    widgets/qhexedit.cpp \
    widgets/commands.cpp \
    widgets/GraphView.cpp \
    common/IScaObjectDirectory.cpp \
    common/DataCache.cpp \
    GraphScene.cpp \
    visual/LinkVisual.cpp \
    visual/IScaObjectSymbolVisual.cpp \
    visual/IScaObjectLineVisual.cpp \
    visual/IScaObjectIdentifierVisual.cpp \
    visual/IScaObjectFileVisual.cpp \
    visual/IScaObjectDirectoryVisual.cpp \
    visual/IScaObjectBlockVisual.cpp \
    visual/Node.cpp \
    visual/ObjectVisual.cpp \
    widgets/ViewsTabWidget.cpp \
    ScaMIMEDataProcessor.cpp \
    widgets/GraphViewContextMenu.cpp \
    widgets/SourceBrowserMenu.cpp \
    widgets/ContextMenu.cpp \
    common/ScaObjectConverter.cpp


HEADERS += \
    FileLoader.h \
    StringConstants.h \
    common/IScaObject.h \
    common/IScaObjectFile.h \
    common/IScaObjectSymbol.h \
    common/IScaObjectLine.h \
    common/IScaObjectBlock.h \
    common/IScaObjectIdentifier.h \
    common/Link.h \
    MainWindow.h \
    widgets/SourceBrowser.h \
    widgets/ObjectTextViewer.h \
    widgets/xbytearray.h \
    widgets/qhexedit_p.h \
    widgets/qhexedit.h \
    widgets/commands.h \
    widgets/GraphView.h \
    NumericalConstants.h \
    common/IScaObjectDirectory.h \
    common/DataCache.h \
    GraphScene.h \
    visual/LinkVisual.h \
    visual/IScaObjectSymbolVisual.h \
    visual/IScaObjectLineVisual.h \
    visual/IScaObjectIdentifierVisual.h \
    visual/IScaObjectFileVisual.h \
    visual/IScaObjectDirectoryVisual.h \
    visual/IScaObjectBlockVisual.h \
    visual/Node.h \
    visual/ObjectVisual.h \
    widgets/ViewsTabWidget.h \
    ScaMIMEDataProcessor.h \
    widgets/GraphViewContextMenu.h \
    widgets/SourceBrowserMenu.h \
    widgets/ContextMenu.h \
    common/ScaObjectConverter.h

FORMS += \
    mainwindow.ui

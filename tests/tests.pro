TEMPLATE = app
TARGET = sca_tests

include(../src/qtpropertybrowser/qtpropertybrowser.pri)

QT += core testlib sql gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
#DEFINES += QT_NO_WARNING_OUTPUT QT_NO_DEBUG_OUTPUT

OBJECTS_DIR = .obj
MOC_DIR = .moc

win32: LIBS += -lsource-highlight-qt42 -lsource-highlight3
unix: LIBS += -lsource-highlight-qt4

SOURCES += \
    main.cpp \
    ../src/GraphScene.cpp \
    ../src/GraphModel.cpp \
    ../src/common/IScaObjectFile.cpp \
    ../src/common/IScaObject.cpp \
    ../src/common/IScaObjectBinaryBlock.cpp \
    ../src/common/IScaObjectDirectory.cpp \
    ../src/common/IScaObjectIdentifier.cpp \
    ../src/common/IScaObjectLine.cpp \
    ../src/common/IScaObjectSymbol.cpp \
    ../src/common/IScaObjectTextBlock.cpp \
    ../src/common/Link.cpp \
    ../src/common/SCAFileSystemModel.cpp \
    ../src/common/ScaObjectConverter.cpp \
    ../src/FileLoader.cpp \
    ../src/GraphFilter.cpp \
    ../src/GraphLoader.cpp \
    ../src/GraphSaver.cpp \
    ../src/GraphTableProxyModel.cpp \
    ../src/ObjectCreator.cpp \
    ../src/ScaMIMEDataProcessor.cpp \
    ../src/visual/IScaObjectBinaryBlockVisual.cpp \
    ../src/visual/IScaObjectDirectoryVisual.cpp \
    ../src/visual/IScaObjectFileVisual.cpp \
    ../src/visual/IScaObjectIdentifierVisual.cpp \
    ../src/visual/IScaObjectLineVisual.cpp \
    ../src/visual/IScaObjectSymbolVisual.cpp \
    ../src/visual/IScaObjectTextBlockVisual.cpp \
    ../src/visual/LinkVisual.cpp \
    ../src/visual/Node.cpp \
    ../src/visual/ObjectVisual.cpp \
    ../src/visual/ObjectVisualCreator.cpp \
    ../src/visual/IScaObjectGroupVisual.cpp \
    ../src/common/IScaObjectGroup.cpp \
    ../src/widgets/commands.cpp \
    ../src/widgets/ContextMenu.cpp \
    ../src/widgets/GraphView.cpp \
    ../src/widgets/ObjectTextViewer.cpp \
    ../src/widgets/ProcessView.cpp \
    ../src/widgets/PropertyBrowser.cpp \
    ../src/widgets/qhexedit.cpp \
    ../src/widgets/qhexedit_p.cpp \
    ../src/widgets/SettingsDialog.cpp \
    ../src/widgets/SourceBrowser.cpp \
    ../src/widgets/TableView.cpp \
    ../src/widgets/ToolsForm.cpp \
    ../src/widgets/xbytearray.cpp

HEADERS += \
    IScaObjectGroup_Test.h \
    ../src/GraphScene.h \
    ../src/GraphModel.h \
    ../src/common/IScaObjectFile.h \
    ../src/common/IScaObject.h \
    ../src/common/IScaObjectBinaryBlock.h \
    ../src/common/IScaObjectDirectory.h \
    ../src/common/IScaObjectIdentifier.h \
    ../src/common/IScaObjectLine.h \
    ../src/common/IScaObjectSymbol.h \
    ../src/common/IScaObjectTextBlock.h \
    ../src/common/Link.h \
    ../src/common/SCAFileSystemModel.h \
    ../src/common/ScaObjectConverter.h \
    ../src/FileLoader.h \
    ../src/GraphFilter.h \
    ../src/GraphLoader.h \
    ../src/GraphSaver.h \
    ../src/GraphTableProxyModel.h \
    ../src/NumericalConstants.h \
    ../src/ObjectCreator.h \
    ../src/ScaMIMEDataProcessor.h \
    ../src/StringConstants.h \
    ../src/visual/IScaObjectBinaryBlockVisual.h \
    ../src/visual/IScaObjectDirectoryVisual.h \
    ../src/visual/IScaObjectFileVisual.h \
    ../src/visual/IScaObjectIdentifierVisual.h \
    ../src/visual/IScaObjectLineVisual.h \
    ../src/visual/IScaObjectSymbolVisual.h \
    ../src/visual/IScaObjectTextBlockVisual.h \
    ../src/visual/LinkVisual.h \
    ../src/visual/Node.h \
    ../src/visual/ObjectVisual.h \
    ../src/visual/ObjectVisualCreator.h \
    ../src/visual/IScaObjectGroupVisual.h \
    ../src/common/IScaObjectGroup.h \
    GraphFilter_Test.h \
    GraphView_Test.h \
    ../src/widgets/commands.h \
    ../src/widgets/ContextMenu.h \
    ../src/widgets/GraphView.h \
    ../src/widgets/ObjectTextViewer.h \
    ../src/widgets/ProcessView.h \
    ../src/widgets/PropertyBrowser.h \
    ../src/widgets/qhexedit.h \
    ../src/widgets/qhexedit_p.h \
    ../src/widgets/SettingsDialog.h \
    ../src/widgets/SourceBrowser.h \
    ../src/widgets/TableView.h \
    ../src/widgets/ToolsForm.h \
    ../src/widgets/xbytearray.h

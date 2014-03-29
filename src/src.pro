TEMPLATE = app
TARGET = sca

include(qtpropertybrowser/qtpropertybrowser.pri)

unix {
target.path = /opt/extras.ubuntu.com/sca/

icon.files = ../publishing_materials/icon_512.png
icon.path = /opt/extras.ubuntu.com/sca/

desktop_file.files = ../scripts/extras-sca.desktop
desktop_file.path = /usr/share/applications/

INSTALLS += target icon desktop_file
}

win32 {
lang_files.files = ($COPY_DIR) $$PWD/resources/syntax_highlight
CONFIG(debug, debug|release): lang_files.path = $$OUT_PWD/debug/
CONFIG(release, debug|release): lang_files.path = $$OUT_PWD/release/

RC_FILE = resources/win_icon.rc
INSTALLS += lang_files
}

OBJECTS_DIR = .obj
MOC_DIR = .moc

QT += core gui declarative sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

win32: LIBS += -lsource-highlight-qt42 -lsource-highlight3
unix: LIBS += -lsource-highlight-qt4 -lOGDF -lpthread -lCOIN

SOURCES += \
    main.cpp \
    FileLoader.cpp \
    common/IScaObject.cpp \
    common/IScaObjectFile.cpp \
    common/IScaObjectSymbol.cpp \
    common/IScaObjectLine.cpp \
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
    visual/IScaObjectTextBlockVisual.cpp \
    visual/Node.cpp \
    visual/ObjectVisual.cpp \
    ScaMIMEDataProcessor.cpp \
    widgets/ContextMenu.cpp \
    common/ScaObjectConverter.cpp \
    common/IScaObjectBinaryBlock.cpp \
    visual/IScaObjectBinaryBlockVisual.cpp \
    GraphModel.cpp \
    common/IScaObjectTextBlock.cpp \
    GraphFilter.cpp \
    widgets/FilterDialog.cpp \
    visual/ObjectVisualCreator.cpp \
    GraphTableProxyModel.cpp \
    GraphSaver.cpp \
    GraphLoader.cpp \
    ObjectCreator.cpp \
    common/SCAFileSystemModel.cpp \
    widgets/TableView.cpp \
    widgets/PropertyBrowser.cpp \
    widgets/ProcessView.cpp \
    widgets/ToolsForm.cpp \
    widgets/SettingsDialog.cpp \
    GraphPlanarizer.cpp \
    OgdfConverter.cpp


HEADERS += \
    FileLoader.h \
    StringConstants.h \
    common/IScaObject.h \
    common/IScaObjectFile.h \
    common/IScaObjectSymbol.h \
    common/IScaObjectLine.h \
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
    visual/IScaObjectTextBlockVisual.h \
    visual/Node.h \
    visual/ObjectVisual.h \
    ScaMIMEDataProcessor.h \
    widgets/ContextMenu.h \
    common/ScaObjectConverter.h \
    common/IScaObjectTextBlock.h \
    common/IScaObjectBinaryBlock.h \
    visual/IScaObjectBinaryBlockVisual.h \
    GraphModel.h \
    GraphFilter.h \
    widgets/FilterDialog.h \
    visual/ObjectVisualCreator.h \
    GraphTableProxyModel.h \
    GraphSaver.h \
    GraphLoader.h \
    ObjectCreator.h \
    common/SCAFileSystemModel.h \
    widgets/TableView.h \
    widgets/PropertyBrowser.h \
    widgets/ProcessView.h \
    widgets/ToolsForm.h \
    widgets/SettingsDialog.h \
    GraphPlanarizer.h \
    OgdfConverter.h

FORMS += \
    mainwindow.ui \
    FilterDialog.ui \
    EditCommandDialog.ui \
    ToolsForm.ui \
    SettingsDialog.ui

RESOURCES += \
    resources/resources.qrc

OTHER_FILES += \
    qtpropertybrowser/qtpropertybrowser.pri

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
unix: LIBS += -lsource-highlight-qt4

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
    widgets/ViewsTabWidget.cpp \
    ScaMIMEDataProcessor.cpp \
    widgets/GraphViewContextMenu.cpp \
    widgets/SourceBrowserMenu.cpp \
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
    widgets/PropertyBrowser.cpp


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
    widgets/ViewsTabWidget.h \
    ScaMIMEDataProcessor.h \
    widgets/GraphViewContextMenu.h \
    widgets/SourceBrowserMenu.h \
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
    ../syntax_highlight/extreme_comment3.lang \
    ../syntax_highlight/extreme_comment4.lang

FORMS += \
    mainwindow.ui \
    FilterDialog.ui

RESOURCES += \
    resources/resources.qrc

OTHER_FILES += \
    qtpropertybrowser/qtpropertybrowser.pri \
    ../syntax_highlight/applescript.lang \
    ../syntax_highlight/asm.lang \
    ../syntax_highlight/awk.lang \
    ../syntax_highlight/bat.lang \
    ../syntax_highlight/bib.lang \
    ../syntax_highlight/bison.lang \
    ../syntax_highlight/c.lang \
    ../syntax_highlight/c_comment.lang \
    ../syntax_highlight/c_string.lang \
    ../syntax_highlight/caml.lang \
    ../syntax_highlight/changelog.lang \
    ../syntax_highlight/clike_vardeclaration.lang \
    ../syntax_highlight/clipper.lang \
    ../syntax_highlight/cobol.lang \
    ../syntax_highlight/coffeescript.lang \
    ../syntax_highlight/conf.lang \
    ../syntax_highlight/cpp.lang \
    ../syntax_highlight/csharp.lang \
    ../syntax_highlight/css.lang \
    ../syntax_highlight/d.lang \
    ../syntax_highlight/default.lang \
    ../syntax_highlight/default.style \
    ../syntax_highlight/desktop.lang \
    ../syntax_highlight/diff.lang \
    ../syntax_highlight/erlang.lang \
    ../syntax_highlight/errors.lang \
    ../syntax_highlight/esc.style \
    ../syntax_highlight/esc256.style \
    ../syntax_highlight/extreme_comment.lang \
    ../syntax_highlight/extreme_comment2.lang \
    ../syntax_highlight/fixed-fortran.lang \
    ../syntax_highlight/flex.lang \
    ../syntax_highlight/fortran.lang \
    ../syntax_highlight/function.lang \
    ../syntax_highlight/glsl.lang \
    ../syntax_highlight/haskell.lang \
    ../syntax_highlight/haskell_literate.lang \
    ../syntax_highlight/haxe.lang \
    ../syntax_highlight/html.lang \
    ../syntax_highlight/html_simple.lang \
    ../syntax_highlight/islisp.lang \
    ../syntax_highlight/java.lang \
    ../syntax_highlight/javalog.lang \
    ../syntax_highlight/javalog.style \
    ../syntax_highlight/javascript.lang \
    ../syntax_highlight/key_string.lang \
    ../syntax_highlight/lang.map \
    ../syntax_highlight/langdef.lang \
    ../syntax_highlight/latex.lang \
    ../syntax_highlight/ldap.lang \
    ../syntax_highlight/lilypond.lang \
    ../syntax_highlight/lilypond.style \
    ../syntax_highlight/lisp.lang \
    ../syntax_highlight/log.lang \
    ../syntax_highlight/logtalk.lang \
    ../syntax_highlight/lsm.lang \
    ../syntax_highlight/lua.lang \
    ../syntax_highlight/m4.lang \
    ../syntax_highlight/makefile.lang \
    ../syntax_highlight/manifest.lang \
    ../syntax_highlight/nohilite.lang \
    ../syntax_highlight/number.lang \
    ../syntax_highlight/opa.lang \
    ../syntax_highlight/outlang.lang \
    ../syntax_highlight/outlang.map \
    ../syntax_highlight/oz.lang \
    ../syntax_highlight/pascal.lang \
    ../syntax_highlight/pc.lang \
    ../syntax_highlight/perl.lang \
    ../syntax_highlight/php.lang \
    ../syntax_highlight/po.lang \
    ../syntax_highlight/postscript.lang \
    ../syntax_highlight/prolog.lang \
    ../syntax_highlight/properties.lang \
    ../syntax_highlight/proto.lang \
    ../syntax_highlight/python.lang \
    ../syntax_highlight/ruby.lang \
    ../syntax_highlight/scala.lang \
    ../syntax_highlight/scheme.lang \
    ../syntax_highlight/script_comment.lang \
    ../syntax_highlight/sh.lang \
    ../syntax_highlight/simple.lang \
    ../syntax_highlight/slang.lang \
    ../syntax_highlight/sml.lang \
    ../syntax_highlight/spec.lang \
    ../syntax_highlight/sql.lang \
    ../syntax_highlight/style.lang \
    ../syntax_highlight/style2.style \
    ../syntax_highlight/style3.style \
    ../syntax_highlight/symbols.lang \
    ../syntax_highlight/tcl.lang \
    ../syntax_highlight/texinfo.lang \
    ../syntax_highlight/texinfo.style \
    ../syntax_highlight/tml.lang \
    ../syntax_highlight/tml_formatting.lang \
    ../syntax_highlight/tml_formatting_all.lang \
    ../syntax_highlight/tml_glue.lang \
    ../syntax_highlight/tml_macrolinks.lang \
    ../syntax_highlight/tml_macros.lang \
    ../syntax_highlight/tml_macros1.lang \
    ../syntax_highlight/tml_macros2.lang \
    ../syntax_highlight/tml_macrosdelayed1.lang \
    ../syntax_highlight/tml_macrosdelayed2.lang \
    ../syntax_highlight/tml_macrosdelayed3.lang \
    ../syntax_highlight/tml_macrotokens.lang \
    ../syntax_highlight/todo.lang \
    ../syntax_highlight/upc.lang \
    ../syntax_highlight/url.lang \
    ../syntax_highlight/vala.lang \
    ../syntax_highlight/vbscript.lang \
    ../syntax_highlight/xml.lang \
    ../syntax_highlight/xorg.lang

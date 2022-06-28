QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    editor/markdownhighlighter.cpp \
    editor/textedit.cpp \
    items/treeitem.cpp \
    main.cpp \
    mainwindow.cpp \
    models/cardmodel.cpp \
    utils/itemutility.cpp \
    views/corkboardview.cpp \
    views/drafttree.cpp \
    views/viewchanger.cpp \
    views/basetreeview.cpp \
    xmls/xmlreader.cpp

HEADERS += \
    editor/markdownhighlighter.h \
    editor/textedit.h \
    enums/generaltypes.h \
    items/treeitem.h \
    mainwindow.h \
    models/cardmodel.h \
    utils/itemutility.h \
    views/corkboardview.h \
    views/drafttree.h \
    views/viewchanger.h \
    views/basetreeview.h \
    xmls/xmlreader.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

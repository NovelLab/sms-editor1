QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    editor/mdhighlighter.cpp \
    editor/textedit.cpp \
    items/itemdata.cpp \
    main.cpp \
    mainwindow.cpp \
    models/baseviewmodel.cpp \
    models/datamodel.cpp \
    models/personmodel.cpp \
    models/plotmodel.cpp \
    tools/datacounter.cpp \
    tools/itemchecker.cpp \
    tools/itemdatareader.cpp \
    tools/itemdatawriter.cpp \
    tools/novelbuilder.cpp \
    views/basemainview.cpp \
    views/dataview.cpp \
    views/generalview.cpp \
    views/maintabview.cpp \
    views/outlineview.cpp \
    views/personview.cpp \
    views/plotview.cpp \
    xmls/xmlreader.cpp \
    xmls/xmlwriter.cpp

HEADERS += \
    editor/mdhighlighter.h \
    editor/textedit.h \
    items/dataenums.h \
    items/itemdata.h \
    mainwindow.h \
    models/baseviewmodel.h \
    models/datamodel.h \
    models/personmodel.h \
    models/plotmodel.h \
    tools/datacounter.h \
    tools/itemchecker.h \
    tools/itemdatareader.h \
    tools/itemdatawriter.h \
    tools/novelbuilder.h \
    views/basemainview.h \
    views/dataview.h \
    views/generalview.h \
    views/maintabview.h \
    views/outlineview.h \
    views/personview.h \
    views/plotview.h \
    xmls/xmlreader.h \
    xmls/xmlwriter.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

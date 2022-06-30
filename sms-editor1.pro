QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    editor/markdownhighlighter.cpp \
    editor/textedit.cpp \
    items/bookinfoitem.cpp \
    items/treeitem.cpp \
    main.cpp \
    mainwindow.cpp \
    models/basetablemodel.cpp \
    models/cardmodel.cpp \
    models/personsmodel.cpp \
    models/worldsmodel.cpp \
    saveload/savedatafiler.cpp \
    utils/itemutility.cpp \
    views/bookinfoview.cpp \
    views/corkboardview.cpp \
    views/drafttree.cpp \
    views/notestree.cpp \
    views/personstableview.cpp \
    views/persontree.cpp \
    views/plottree.cpp \
    views/researchtree.cpp \
    views/rubitree.cpp \
    views/viewchanger.cpp \
    views/basetreeview.cpp \
    views/worldstableview.cpp \
    views/worldtree.cpp \
    xmls/xmlreader.cpp \
    xmls/xmlwriter.cpp

HEADERS += \
    common/appsettings.h \
    editor/markdownhighlighter.h \
    editor/textedit.h \
    enums/bookinfotypes.h \
    enums/generaltypes.h \
    items/bookinfoitem.h \
    items/treeitem.h \
    mainwindow.h \
    models/basetablemodel.h \
    models/cardmodel.h \
    models/personsmodel.h \
    models/worldsmodel.h \
    saveload/savedatafiler.h \
    utils/itemutility.h \
    views/bookinfoview.h \
    views/corkboardview.h \
    views/drafttree.h \
    views/notestree.h \
    views/personstableview.h \
    views/persontree.h \
    views/plottree.h \
    views/researchtree.h \
    views/rubitree.h \
    views/viewchanger.h \
    views/basetreeview.h \
    views/worldstableview.h \
    views/worldtree.h \
    xmls/xmlreader.h \
    xmls/xmlwriter.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

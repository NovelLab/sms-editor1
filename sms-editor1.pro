QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    builder/novelbuilder.cpp \
    configs/configdialog.cpp \
    configs/configmodel.cpp \
    configs/globalsetting.cpp \
    editor/bookinfoeditor.cpp \
    editor/drafteditor.cpp \
    editor/markdownhighlighter.cpp \
    editor/personeditor.cpp \
    editor/ploteditor.cpp \
    editor/rubieditor.cpp \
    editor/textedit.cpp \
    editor/worldeditor.cpp \
    items/bookinfoitem.cpp \
    items/configitem.cpp \
    items/treeitem.cpp \
    main.cpp \
    mainwindow.cpp \
    models/basetablemodel.cpp \
    models/cardmodel.cpp \
    models/personsmodel.cpp \
    models/rubismodel.cpp \
    models/worldsmodel.cpp \
    saveload/savedatafiler.cpp \
    utils/itemutility.cpp \
    views/corkboardview.cpp \
    views/drafttree.cpp \
    views/notestree.cpp \
    views/personstableview.cpp \
    views/persontree.cpp \
    views/plottree.cpp \
    views/researchtree.cpp \
    views/rubitableview.cpp \
    views/rubitree.cpp \
    views/trashtree.cpp \
    views/viewchanger.cpp \
    views/basetreeview.cpp \
    views/worldstableview.cpp \
    views/worldtree.cpp \
    xmls/xmlreader.cpp \
    xmls/xmlwriter.cpp

HEADERS += \
    builder/novelbuilder.h \
    common/appsettings.h \
    common/configenums.h \
    common/generalenums.h \
    common/itemkeys.h \
    configs/configdialog.h \
    configs/configmodel.h \
    configs/globalsetting.h \
    editor/bookinfoeditor.h \
    editor/drafteditor.h \
    editor/markdownhighlighter.h \
    editor/personeditor.h \
    editor/ploteditor.h \
    editor/rubieditor.h \
    editor/textedit.h \
    editor/worldeditor.h \
    items/bookinfoitem.h \
    items/configitem.h \
    items/treeitem.h \
    mainwindow.h \
    models/basetablemodel.h \
    models/cardmodel.h \
    models/personsmodel.h \
    models/rubismodel.h \
    models/worldsmodel.h \
    saveload/savedatafiler.h \
    utils/itemutility.h \
    views/corkboardview.h \
    views/drafttree.h \
    views/notestree.h \
    views/personstableview.h \
    views/persontree.h \
    views/plottree.h \
    views/researchtree.h \
    views/rubitableview.h \
    views/rubitree.h \
    views/trashtree.h \
    views/viewchanger.h \
    views/basetreeview.h \
    views/worldstableview.h \
    views/worldtree.h \
    xmls/xmlreader.h \
    xmls/xmlwriter.h

FORMS += \
    configs/configdialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

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
    delegate/centerboarddelegate.cpp \
    editor/bookinfoeditor.cpp \
    editor/drafteditor.cpp \
    editor/markdownhighlighter.cpp \
    editor/personeditor.cpp \
    editor/ploteditor.cpp \
    editor/rubieditor.cpp \
    editor/textedit.cpp \
    editor/worldeditor.cpp \
    items/configitem.cpp \
    items/countitem.cpp \
    items/treeitem.cpp \
    main.cpp \
    mainwindow.cpp \
    models/modeldatafactory.cpp \
    models/tableitemmodel.cpp \
    saveload/savedatafiler.cpp \
    tools/counter.cpp \
    utils/itemutility.cpp \
    views/centerboardview.cpp \
    views/itemfactory.cpp \
    views/outlineview.cpp \
    views/viewchanger.cpp \
    xmls/xmlreader.cpp \
    xmls/xmlwriter.cpp

HEADERS += \
    builder/novelbuilder.h \
    common/appsettings.h \
    common/configenums.h \
    common/generalenums.h \
    common/itemkeys.h \
    delegate/centerboarddelegate.h \
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
    items/configitem.h \
    items/countitem.h \
    items/treeitem.h \
    mainwindow.h \
    models/modeldatafactory.h \
    models/tableitemmodel.h \
    saveload/savedatafiler.h \
    tools/counter.h \
    utils/itemutility.h \
    views/centerboardview.h \
    views/itemfactory.h \
    views/outlineview.h \
    views/viewchanger.h \
    xmls/xmlreader.h \
    xmls/xmlwriter.h

FORMS += \
    configs/configdialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets/assets.qrc

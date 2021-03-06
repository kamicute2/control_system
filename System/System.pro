QT       += core gui sql network widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Kitsune
TEMPLATE = app
CONFIG += c++11
win32:RC_ICONS += ./images./icon.ico

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    database.cpp \
    form.cpp \
    main.cpp \
    mainwindow.cpp \
    manualbox.cpp \
    report.cpp \
    visitor.cpp

HEADERS += \
    database.h \
    form.h \
    mainwindow.h \
    manualbox.h \
    report.h \
    visitor.h

FORMS += \
    form.ui \
    mainwindow.ui \
    report.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KZPaint #might need to delete this line and template = app if the code does not want to run
TEMPLATE = app

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    drawingspace.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    drawingspace.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

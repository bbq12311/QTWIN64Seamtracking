#-------------------------------------------------
#
# Project created by QtCreator 2020-06-10T22:02:43
#
#-------------------------------------------------

QT       += core gui printsupport
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyWeldSeamTrack
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    camera.cpp \
    manual.cpp \
    offlinetrack.cpp \
    simplecalibration.cpp \
    weld.cpp \
    imageacqusition.cpp \
    dip.cpp \
    onlinetrack.cpp \
    motion.cpp \
    qcustomplot.cpp \
    pidcurve.cpp

HEADERS += \
        mainwindow.h \
    camera.h \
    manual.h \
    offlinetrack.h \
    simplecalibration.h \
    weld.h \
    var.h \
    imageacqusition.h \
    JHCap.h \
    dip.h \
    onlinetrack.h \
    motion.h \
    qcustomplot.h \
    pidcurve.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    Mainwindow.ui \
    camera.ui \
    manual.ui \
    offlinetrack.ui \
    offlinetrack.ui \
    simplecalibration.ui \
    weld.ui \
    pidcurve.ui


INCLUDEPATH += G:/MyWeldSeamTrack/MyWeldSeamTrack   \
E:/opencv3.4.10/opencv-3.4.10/build/install/include/opencv2 \
E:/opencv3.4.10/opencv-3.4.10/build/install/include/opencv \
E:/opencv3.4.10/opencv-3.4.10/build/install/include

LIBS += E:/opencv3.4.10/opencv-3.4.10/build/install/x64/vc15/lib/opencv_world3410d.lib \

unix|win32: LIBS += -L$$PWD/./ -lJHCap2

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

DISTFILES +=

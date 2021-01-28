QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    decodec.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    decodec.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += $$PWD/FFmpeg4
include ($$PWD/FFmpeg4/ffmpeg.pri)

INCLUDEPATH += $$PWD/bitmap
include ($$PWD/bitmap/bitmap.pri)

INCLUDEPATH += $$PWD/OpenCV
include ($$PWD/OpenCV/OpenCV.pri)

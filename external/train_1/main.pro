QT       += core
QT       -= gui
QT += core network

CONFIG   += console
CONFIG   -= app_bundle

SOURCES += main.cpp \
        train_1_handle.cpp\
        ../api/src_winterface/winterface-api.cpp\
        ../api/src_winterface/winterface.cpp

HEADERS +=  train_1_handle.h\
        ../api/src_winterface/winterface-api.h\
        ../api/src_winterface/winterface.h\
        ../../src/config/config.h

TARGET = train1

DESTDIR = /home/urs/uni/cpp-gui/qt_project/build/Api-Build/

# Optional: Zusätzliche Compiler-Optionen
# QMAKE_CXXFLAGS += -Wall -Wextra

######################################################################
# Automatically generated by qmake (3.1) Mon Dec 23 00:47:21 2024
######################################################################

TEMPLATE = app
TARGET = project
INCLUDEPATH += .
QT += widgets
QT += gui
QT += core network

# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the doc    umentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS +=  src/pro.h \
            src/api/apihandler.h\
            src/button/modbutton.h \
            src/led/ledcontrol.h \
            src/led/ledgrid.h \
            src/switch/switchcontrol.h \
            src/train/accslider.h \
            src/train/traincontrol.h \
            src/train/veloslider.h \
            src/turbine/turbinecontrol.h \
            src/config/config.h\
            src/config/style_config.h\
            src/config/fonts/fonts.h \
            external/api/src_winterface/winterface.h \
            external/api/src_winterface/winterface-api.h\
            external/api/src_winterface/winterface-config.h

SOURCES +=  src/main.cpp\
            src/led/ledgrid.cpp \
            src/pro.cpp \
            src/api/apihandler.cpp \
            src/button/modbutton.cpp \
            src/led/ledcontrol.cpp \
            src/switch/switchcontrol.cpp \
            src/train/accslider.cpp \
            src/train/traincontrol.cpp \
            src/train/veloslider.cpp \
            src/turbine/turbinecontrol.cpp \
            external/api/src_winterface/winterface.cpp \
            external/api/src_winterface/winterface-api.cpp\
            src/config/fonts/fonts.cpp

RESOURCES += \
    resources/res.qrc

INCLUDEPATH +=  external/api/src_winterface\
                src/train\
                src/led\
                src/turbine\
                src/switch\
                src/config\
                src/config/fonts\
                src/button\
                src/api



TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        oculus.cpp

INCLUDEPATH += "$$PWD/include"

LIBS += "$$PWD/lib/LibOVR.lib"

HEADERS += \
    oculus.h

QT += core
QT -= gui
QT += websockets network
CONFIG += c++11

TARGET = QRouterCore
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    core.cpp \
    cbor.cpp

HEADERS += \
    core.h \
    cbor.h

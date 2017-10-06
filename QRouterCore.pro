QT += core
QT -= gui
QT += websockets network
CONFIG += c++11

TARGET = QRouterCore
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app
include (../QRouterLib/qrouterlib.pri)

SOURCES += main.cpp \
    core.cpp \
    cbor.cpp

HEADERS += \
    core.h \
    cbor.h

DISTFILES +=

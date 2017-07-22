QT += core gui qml quick network

CONFIG += c++17

TARGET = harkach
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

VERSION = 0.0.1

SOURCES += main.cpp \
    MainApp.cpp \
    BoardModel.cpp \
    Board.cpp \
    Attachment.cpp \
    ThreadsView.cpp \
    ThreadObject.cpp \
    ThreadModel.cpp \
    PostsView.cpp \
    PostObject.cpp \
    PostModel.cpp

DEFINES += QT_DEPRECATED_WARNINGS

DEFINES += "PROJECT_ROOT=\\\"$$_PRO_FILE_PWD_/\\\""

DISTFILES += \
    qml/main.qml \
    qml/Ttest.qml \
    qml/ThreadsViewPage.qml \
    qml/LoadSplash.qml \
    qml/PostsViewPage.qml \
    qml/PostDelegate.qml \
    qml/ImgDescription.qml \
    qml/TextOnly.qml \
    qml/TopToolBar.qml \
    qml/PostPanel.qml \
    qml/BoardsView.qml \
    qml/BoardDelegate.qml \
    qml/BoardSection.qml

HEADERS += \
    MainApp.h \
    BoardModel.h \
    Board.h \
    Attachment.h \
    ThreadsView.h \
    ThreadObject.h \
    ThreadModel.h \
    PostsView.h \
    PostObject.h \
    PostModel.h

RESOURCES += \
    pic/pic.qrc

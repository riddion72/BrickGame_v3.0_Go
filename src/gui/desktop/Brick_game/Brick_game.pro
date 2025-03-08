QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 strict_c++

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
QMAKE_MACOSX_DEPLOYMENT_TARGET = 13.0

INCLUDEPATH += ../../../brick_game/race
LIBS += -L../../../brick_game/race -ls21_backend_race

SOURCES += \
    ../../../brick_game/controller/s21_controller.cc \
    ../../../brick_game/snake/s21_apple.cc \
    ../../../brick_game/snake/s21_backend_snake.cc \
    ../../../brick_game/snake/s21_snake.cc \
    ../../../brick_game/tetris/s21_backend_tetris.c \
    ../../../brick_game/tetris/s21_helper.c \
    ../../../brick_game/tetris/s21_singletones.c \
    main.cpp \
    mainwindow.cpp \
    secondwindow.cpp

HEADERS += \
    ../../../brick_game/controller/s21_controller.h \
    ../../../brick_game/snake/s21_apple.h \
    ../../../brick_game/snake/s21_backend.h \
    ../../../brick_game/snake/s21_snake.h \
    ../../../brick_game/tetris/s21_backend.h \
    ../../../brick_game/tetris/s21_helper.h \
    ../../../brick_game/tetris/s21_singletones.h \
    ../../../brick_game/race/libs21_backend_race.h \
    ../../../common/header.h \
    mainwindow.h \
    secondwindow.h

FORMS += \
    mainwindow.ui \
    secondwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc

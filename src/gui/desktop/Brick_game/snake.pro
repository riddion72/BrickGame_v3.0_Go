QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../Desktop/projects/YandexHandbook/src/brick_game/controller/s21_controller.cc \
    ../Desktop/projects/YandexHandbook/src/brick_game/snake/s21_apple.cc \
    ../Desktop/projects/YandexHandbook/src/brick_game/snake/s21_backend_snake.cc \
    ../Desktop/projects/YandexHandbook/src/brick_game/snake/s21_snake.cc \
    ../Desktop/projects/YandexHandbook/src/brick_game/tetris/s21_backend_tetris.c \
    ../Desktop/projects/YandexHandbook/src/brick_game/tetris/s21_helper.c \
    ../Desktop/projects/YandexHandbook/src/brick_game/tetris/s21_singletones.c \
    main.cpp \
    mainwindow.cpp \
    secondwindow.cpp

HEADERS += \
    ../Desktop/projects/YandexHandbook/src/brick_game/controller/s21_controller.h \
    ../Desktop/projects/YandexHandbook/src/brick_game/snake/s21_apple.h \
    ../Desktop/projects/YandexHandbook/src/brick_game/snake/s21_backend.h \
    ../Desktop/projects/YandexHandbook/src/brick_game/snake/s21_snake.h \
    ../Desktop/projects/YandexHandbook/src/brick_game/tetris/s21_backend.h \
    ../Desktop/projects/YandexHandbook/src/brick_game/tetris/s21_helper.h \
    ../Desktop/projects/YandexHandbook/src/brick_game/tetris/s21_singletones.h \
  ../Desktop/projects/YandexHandbook/src/common/header.h \
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

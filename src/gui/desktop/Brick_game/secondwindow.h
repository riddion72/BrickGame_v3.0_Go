#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QDialog>
#include <QPainter>
#include "QKeyEvent"
#include <QTimer>
#include <QApplication>
#include <QLabel>
#include <QPropertyAnimation>

#include "../../../common/header.h"
#include "../../../brick_game/controller/s21_controller.h"

#define W_SIZE_G 301
#define H_SIZE_G 401

namespace Ui {
class SecondWindow;
}

class SecondWindow : public QDialog
{
    Q_OBJECT

public:
    SecondWindow(QWidget *parent = nullptr, gameName_t gameName = Not_a_game);
    ~SecondWindow();
protected:
    void paintEvent(QPaintEvent *event);
   void keyPressEvent( QKeyEvent* e);
   void timerEvent(QTimerEvent *e);
private:
    Ui::SecondWindow *ui;
    s21::gameController *controller;
    int timer_id;
    void drawMenu(const int &score);
    void drawGameField(int **field, const int &score, const int &high_score, const int &lvl);
    void nextFigure(int **next);
    void pauseMenu(int **field);
};



#endif // SECONDWINDOW_H

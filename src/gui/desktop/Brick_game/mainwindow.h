#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QRect>
#include <QBrush>
#include <QPalette>
#include <QPixmap>
#include "../../../brick_game/controller/s21_controller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
//    void game(gameName_t gameName);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();



private:
    Ui::MainWindow *ui;
//    gameName_t gameName = Not_a_game;
};

#endif // MAINWINDOW_H



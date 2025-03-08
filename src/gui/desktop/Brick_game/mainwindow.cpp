#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "secondwindow.h"
#include <QPalette>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gameName_t gameName = Not_a_game;
    s21::gameController controller(gameName);
}
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    // gameName_t gameName = Snake;
    // game(gameName);

    SecondWindow window(this,Snake);

    window.setModal(true);
    window.exec();


}


void MainWindow::on_pushButton_2_clicked()
{
SecondWindow window(this,Tetris);

window.setModal(true);
window.exec();

}


void MainWindow::on_pushButton_4_clicked()
{
    SecondWindow window(this,Race);

    window.setModal(true);
    window.exec();

}


void MainWindow::on_pushButton_3_clicked()
{
    QApplication::quit();
}


//void game(gameName_t gameName){
//    UserAction_t action;
//    s21::gameController coontroller(gameName);
//}



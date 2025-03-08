#include "secondwindow.h"
#include "ui_secondwindow.h"
#include "mainwindow.h"
SecondWindow::SecondWindow(QWidget *parent, gameName_t gameName) :
    QDialog(parent),
    ui(new Ui::SecondWindow)
{
    ui->setupUi(this);
    this->resize(W_SIZE_G, H_SIZE_G);
    controller = new s21::gameController(gameName);
    timer_id = startTimer(controller->getGameInfo().speed * 100);
    setFocus();
}

SecondWindow::~SecondWindow()
{
    delete ui;
    delete controller;
}

void SecondWindow::timerEvent(QTimerEvent *) {
    controller->makeStep();
    controller->updateUserAction(Nothing, false);
    repaint();
    killTimer(timer_id);
    timer_id = startTimer(controller->getGameInfo().speed * 100);
}

void SecondWindow::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    controller->getUserInput();
    controller->updateState();
    GameInfo_t game = controller->getGameInfo();

    if (game.pause == 0) {

        if(game.field) {
            //draw game screen
        drawGameField(game.field, game.score, game.high_score, game.level);
     if(game.next) {
          nextFigure(game.next);
     }

        } else {
        drawMenu(game.score);
        }
        // game menu
    } else if(game.pause == 1) {
        //pause
    pauseMenu(game.field);
    nextFigure(game.next);
    } else if(game.pause == 2) {
        //win menu
        painter.drawText(100, 100, QString("YOU WIN"));
        painter.drawText(100, 200, QString("PRESS Q TO EXIT"));
    } else if (game.pause == 3) {
        //lose menu
        painter.drawText(100, 100, QString("YOU LOSE"));
        painter.drawText(100, 200, QString("PRESS Q TO EXIT"));
    }


}

void SecondWindow::keyPressEvent(QKeyEvent *e) {

    switch(e->key()) {
    case Qt::Key_Left:
        controller->updateUserAction(Left, e->isAutoRepeat());
        break;
     case Qt::Key_Right:
         controller->updateUserAction(Right, e->isAutoRepeat());
        break;
     case Qt::Key_Up:
         controller->updateUserAction(Up, e->isAutoRepeat());
        break;
     case Qt::Key_Down:
         controller->updateUserAction(Down, e->isAutoRepeat());
        break;
     case Qt::Key_Return:
         controller->updateUserAction(Start, e->isAutoRepeat());
        break;
     case Qt::Key_P:
         controller->updateUserAction(Pause, e->isAutoRepeat());
        break;
     case Qt::Key_Q:
         controller->updateUserAction(Terminate, e->isAutoRepeat());
//         QApplication::quit();
         close();
        break;
     case Qt::Key_E:
         controller->updateUserAction(Exit_game, e->isAutoRepeat());
        break;
    case Qt::Key_Space:
        controller->updateUserAction(Action, e->isAutoRepeat());
       break;
     default:
         controller->updateUserAction(Nothing, e->isAutoRepeat());
    }
    repaint();
}

void SecondWindow::drawMenu(const int &score) {
 QPainter painter(this);
 painter.drawText(201,200 , QString("Press ENTER to START"));
 painter.drawText(201, 220, QString("Press Q to EXIT"));
 for(int i = 0; i < H_SIZE; ++i) {
     for(int j = 0; j < W_SIZE; ++j) {
         painter.drawRect(1+ j*20, 1+ i*20, 20, 20);
     }
 }

         painter.drawRect(201 ,1 , 100, 400);
         painter.drawText(201, 250,QString::number(score));

// painter.drawRect(50, 40, 100, 50);
}
void SecondWindow::drawGameField(int **field,  const int &score, const int &high_score, const int &lvl)
{
QPainter painter(this);
for(int i = 0; i < H_SIZE; ++i) {
    for(int j = 0; j < W_SIZE; ++j) {
        painter.drawRect(1 +j*20, 1 + i*20, 20, 20);
        if(field[i][j]){
            painter.fillRect(1 + j*20, 1 + i*20, 20, 20, QColor(200,200,200));
        }
    }
}
painter.drawText(201, 250,QString("SCORE: "));
painter.drawText(201, 265,QString("HIGH: "));
painter.drawText(201, 280, QString("LEVEL: "));
 painter.drawText(250, 250,QString::number(score));
 painter.drawText(250, 265,QString::number(high_score));
 painter.drawText(250, 280, QString::number(lvl));
 painter.drawText(201, 300, QString("P FOR PAUSE"));
}

void SecondWindow::nextFigure(int **next){
QPainter painter(this);
for(int i = 0; i < 4; ++i) {
    for(int j = 0; j < 4; ++j) {
        if(next[i][j]) {
            painter.drawRect(201 + j*20,1 + i*20, 20,20 );
        }
    }
}

}

void SecondWindow::pauseMenu(int **field) {
    QPainter painter(this);
    for(int i = 0; i < H_SIZE; ++i) {
        for(int j = 0; j < W_SIZE; ++j) {
            painter.drawRect(1+ j*20, 1+ i*20, 20, 20);
            if(field[i][j]){
                painter.fillRect(1 + j*20, 1 + i*20, 20, 20, QColor(200,200,200));
            }
        }
    }

            painter.drawRect(201 ,1 , 100, 400);
}

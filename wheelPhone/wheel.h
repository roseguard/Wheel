#ifndef WHEEL_H
#define WHEEL_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QTcpSocket>
#include <QTcpServer>
#include <QTextStream>
#include <QDesktopWidget>
#include <QKeyEvent>
#include <QTimer>

#define stepVal 5
#define changeTurn 10

class Wheel : public QGraphicsView
{
    Q_OBJECT
public:
    Wheel(QWidget *parent = 0);
    ~Wheel();

    QTcpSocket *socket;
    QTcpServer *server;

    QDesktopWidget      *desk;
    QGraphicsScene      *scene;

    QGraphicsPixmapItem *background;
    QGraphicsPixmapItem *wheelItem;
    QVector<QGraphicsRectItem*> leftBorders;
    QVector<QGraphicsRectItem*> rightBorders;
    QTimer  *borderStep;

    QTimer *timer;
    qint64 rotarget = 0;
    qint64 rotnow = 0;

    bool turnRight = false;
    int wasTurns = 1;
    int turner = 0;

    float validX, validY;
public slots:
    void newSocket();
    void newMessage();
    void rotateToTarget();
    void makeBorderStep();
};

#endif // WHEEL_H

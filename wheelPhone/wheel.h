#ifndef WHEEL_H
#define WHEEL_H

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QDesktopWidget>
#include <QAccelerometer>
#include <QAccelerometerReading>
#include <QDebug>

#include <time.h>

#define stepVal 5
#define changeTurn 10

class Wheel : public QGraphicsView
{
    Q_OBJECT
public:
    Wheel(QWidget *parent = 0);
    ~Wheel();

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
    void rotateToTarget();
    void makeBorderStep();

public:
    QAccelerometer *obj;
    QAccelerometerReading *reader;
    bool needSend = false;

public slots:
    void newDatas();
};

#endif // WHEEL_H

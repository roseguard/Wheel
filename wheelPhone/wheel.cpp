#include "wheel.h"
#include <QCursor>
#include <QGraphicsItemAnimation>
#include <QDesktopWidget>
#include <QThread>
#include <time.h>

#define baseLeft 30
#define baseRight 70

Wheel::Wheel(QWidget *parent)
    : QGraphicsView(parent)
{
    qsrand(time(NULL));

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    desk = new QDesktopWidget;
    validX = desk->width()/100;
    validY = desk->height()/100;

    scene = new QGraphicsScene(this);
    setScene(scene);

    background = new QGraphicsPixmapItem(QPixmap("/home/arhcitect/back.jpg").scaled(desk->width(), desk->height()));
    scene->addItem(background);

    wheelItem = new QGraphicsPixmapItem(QPixmap("/home/arhcitect/wheel.png").scaled(validY*20, validY*20));
    wheelItem->setPos(validX*50, desk->height()-wheelItem->pixmap().height()*1.2);
    scene->addItem(wheelItem);

    QGraphicsRectItem * tempBorder;
    tempBorder = new QGraphicsRectItem(validX*baseLeft, 0, validY*10, validX*5);
    tempBorder->setBrush(Qt::black);
    leftBorders.append(tempBorder);
    scene->addItem(tempBorder);


    tempBorder = new QGraphicsRectItem(validX*baseRight, 0, validY*10, validX*5);
    tempBorder->setBrush(Qt::black);
    rightBorders.append(tempBorder);
    scene->addItem(tempBorder);



    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(newSocket()));
    socket = Q_NULLPTR;
    server->listen(QHostAddress::Any, 31034);

    showFullScreen();
}

Wheel::~Wheel()
{
    delete wheelItem;
    if(socket)
        delete socket;
    delete desk;
    delete background;
    foreach (QGraphicsRectItem * ditem, leftBorders) {
        delete ditem;
    }
    foreach (QGraphicsRectItem * ditem, rightBorders) {
        delete ditem;
    }
}

void Wheel::newSocket()
{
    if(socket)
        delete socket;
    socket = server->nextPendingConnection();
    connect(socket, SIGNAL(readyRead()), this, SLOT(newMessage()));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(rotateToTarget()));
    timer->start(3);

    borderStep = new QTimer(this);
    connect(borderStep, SIGNAL(timeout()), this, SLOT(makeBorderStep()));
    borderStep->start(10);
}

void Wheel::newMessage()
{
    QTextStream stream(socket);
    QVector<QString> datas;
    QString tempDat;
    stream >> tempDat;
    while(!tempDat.isEmpty())
    {
        datas.append(tempDat);
        stream >> tempDat;
        if(tempDat == "end")
            break;
    }
        rotarget = datas.at(0).toInt();
        return;
}

void Wheel::rotateToTarget()
{
    QTransform trans = wheelItem->transform();
    QPixmap pix = wheelItem->pixmap();
    trans.translate(pix.width()/2.0 , pix.height()/2.0);
    if(rotarget<rotnow)
    {
        cursor().setPos(cursor().pos().x()-1, cursor().pos().y());
        rotnow--;
        trans.rotate(wheelItem->rotation()-1);
    }
    else if(rotarget>rotnow)
    {
        rotnow++;
        cursor().setPos(cursor().pos().x()+1, cursor().pos().y());
        trans.rotate(wheelItem->rotation()+1);
    }
    trans.translate(-pix.width()/2.0 , -pix.height()/2.0);
    wheelItem->setTransform(trans);
}

void Wheel::makeBorderStep()
{
    for(int i = 0; i < leftBorders.length(); i++)
    {
        leftBorders.at(i)->moveBy(-(rotnow/2), stepVal);
        rightBorders.at(i)->moveBy(-(rotnow/2), stepVal);
    }
    if(leftBorders.first()->y() > (desk->height()-wheelItem->pixmap().height()))
    {
        if(abs(leftBorders.first()->pos().x()) > (validX*baseLeft/2))
        {
            close();
        }
        scene->removeItem(leftBorders.first());
        delete leftBorders.first();
        leftBorders.removeFirst();
        scene->removeItem(rightBorders.first());
        delete rightBorders.first();
        rightBorders.removeFirst();
    }
    if(leftBorders.last()->y() > leftBorders.last()->rect().height())
    {
        if(turnRight)
            turner+= qrand()%(int)validX*8;
        else
            turner+= -(qrand()%(int)validX*8);
        int tempRand = qrand()%wasTurns;
        qDebug()<< "turns " << wasTurns;
        qDebug()<< "rand " << tempRand;
        if (tempRand > changeTurn)
        {
            turnRight=!turnRight;
            wasTurns=1;
        }
        else
            wasTurns++;

        QGraphicsRectItem * tempBorder;
        tempBorder = new QGraphicsRectItem(validX*baseLeft, validY, validY*10, validX*5);
        tempBorder->setBrush(Qt::black);
        tempBorder->moveBy(turner, 0);
        leftBorders.append(tempBorder);
        scene->addItem(tempBorder);

        tempBorder = new QGraphicsRectItem(validX*baseRight, 0, validY*10, validX*5);
        tempBorder->moveBy(turner, 0);
        tempBorder->setBrush(Qt::black);
        rightBorders.append(tempBorder);
        scene->addItem(tempBorder);
    }
}

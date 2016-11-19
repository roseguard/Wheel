#include "wheelcontrol.h"
#include <QLayout>
#include <QHBoxLayout>
#include <QHostAddress>

WheelControl::WheelControl(QWidget *parent)
    : QWidget(parent)
{
    obj = new QAccelerometer(this);
    connect(obj, SIGNAL(readingChanged()), this, SLOT(newDatas()));
    obj->start();
    text = new QTextBrowser(this);
    text->append("test");
    QHBoxLayout *lay;
    lay = new QHBoxLayout(this);
    setLayout(lay);
    lay->addWidget(text);
    socket = new QTcpSocket(this);
    socket->connectToHost(QHostAddress("192.168.0.104"), 31034);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(setSend()));
    timer->start(1);
}

WheelControl::~WheelControl()
{

}

void WheelControl::newDatas()
{
    if(needSend)
    {
        reader = obj->reading();
        int tx = (int)reader->x();
        int ty = (int)reader->y();
        int tz = (int)reader->z();
        text->append(" x : " + QString::number(tx) +
                     " y : " + QString::number(ty) +
                     " z : " + QString::number(tz));
        QTextStream stream(socket);
        stream << QString::number(ty*10);
        needSend = false;
    }
}

void WheelControl::setSend()
{
    needSend = true;
}

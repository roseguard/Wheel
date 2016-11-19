#ifndef WHEELCONTROL_H
#define WHEELCONTROL_H

#include <QWidget>
#include <QTcpSocket>
#include <QAccelerometer>
#include <QAccelerometerReading>
#include <QTextStream>
#include <QTextBrowser>
#include <QTimer>

class WheelControl : public QWidget
{
    Q_OBJECT

public:
    WheelControl(QWidget *parent = 0);
    ~WheelControl();

    QTextBrowser *text;
    QTcpSocket *socket;
    QAccelerometer *obj;
    QAccelerometerReading *reader;
    QTimer *timer;
    bool needSend = false;

public slots:
    void setSend();
    void newDatas();
};

#endif // WHEELCONTROL_H

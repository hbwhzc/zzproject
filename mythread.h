#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <qobject.h>
#include <qserialport.h>
#include <qserialportinfo.h>
#include <QDebug>
class mythread :public QObject
{
    Q_OBJECT
public:
    mythread(){
        qDebug()<<tr("thread OK")<<endl;
    }


    QSerialPort *myserial = new QSerialPort;
public slots:
    void write(QByteArray);
    void read();
    void open(QString,QString);
    void scan();
    void close();
signals:
    void sendtocontrol(QString);
    void sendportname(QString);
};

#endif // MYTHREAD_H

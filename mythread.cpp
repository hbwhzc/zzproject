#include "mythread.h"
#include <qtextcodec.h>
void mythread::scan()
{
    if(myserial!=nullptr)
    {

        foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        {
            QSerialPort mycom;
            mycom.setPort(info);
            if(mycom.open(QIODevice::ReadWrite))
            {

                  QString portname = mycom.portName();
                  emit sendportname(portname);
                  qDebug()<<portname<<endl;
                  mycom.close();
            }
        }
    }
}

void mythread::close()
{
    myserial->close();
}

void mythread::write(QByteArray msg)
{
    qDebug()<<tr("write OK")<<endl;
    myserial->write(msg);
    myserial->write("\r\n");
}

void mythread::read()
{
    QTextCodec *codec = QTextCodec::codecForName("gb18030");
    QByteArray data = myserial->readAll();
    QString str = codec->toUnicode(data);
    emit sendtocontrol(str);
    data.clear();
    myserial->readAll().clear();
}

void mythread::open(QString boxname,QString baud)
{
    qDebug()<<tr("open OK")<<endl;
    myserial->setPortName(boxname);
    myserial->setBaudRate(baud.toInt());
    myserial->setDataBits(QSerialPort::Data8);
    myserial->setParity(QSerialPort::NoParity);
    myserial->setStopBits(QSerialPort::OneStop);
    myserial->setFlowControl(QSerialPort::NoFlowControl);
    myserial->setReadBufferSize(1024);
    myserial->open(QIODevice::ReadWrite);
    myserial->setDataTerminalReady(true);
    QObject::connect(myserial,&QSerialPort::readyRead,this,&mythread::read);

}

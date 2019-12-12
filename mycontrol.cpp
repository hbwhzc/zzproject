#include "mycontrol.h"




mycontrol::mycontrol()
{
    qDebug()<<tr("control OK")<<endl;
}

void mycontrol::revread(QString str)
{
    emit sendtoui(str);
}

void mycontrol::revuibtn(QByteArray msg)
{
    qDebug()<<tr("revbtn OK")<<endl;
    emit sendtocom(msg);
}

void mycontrol::init()
{
    mythread *serial = new mythread;
    serial->moveToThread(&Tserial);
    connect(serial,SIGNAL(sendtocontrol(QString)),this,SLOT(revread(QString)));
    connect(this,SIGNAL(sendtocom(QByteArray)),serial,SLOT(write(QByteArray)));
    connect(serial,SIGNAL(sendportname(QString)),this,SLOT(readportname(QString)));
    connect(this,SIGNAL(sendportnametocom(QString,QString)),serial,SLOT(open(QString,QString)));
    connect(this,SIGNAL(startscan()),serial,SLOT(scan()));
    connect(this,SIGNAL(closecom()),serial,SLOT(close()));
    connect(serial,SIGNAL(finished()),serial,SLOT(deleteLater()));
    qDebug()<<tr("init OK")<<endl;
    Tserial.start();
    emit startscan();
}

void mycontrol::readportname(QString portname)
{
    qDebug()<<portname<<endl;
    emit sendportnametoui(portname);
}

void mycontrol::readuicom(QString boxname,QString baud)
{
    emit sendportnametocom(boxname,baud);
}

void mycontrol::uishutdown()
{
    emit closecom();
    Tserial.exit();
}

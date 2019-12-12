#ifndef MYCONTROL_H
#define MYCONTROL_H
#include <QObject>
#include <QThread>
#include <mythread.h>
#include <QDebug>
class mycontrol : public QObject
{
    Q_OBJECT
    QThread Tserial;

public:
    mycontrol();
public slots:
    void revread(QString);
    void revuibtn(QByteArray);
    void init();
    void readportname(QString);
    void readuicom(QString,QString);
    void uishutdown();
signals:
    void sendtoui(QString);
    void sendtocom(QByteArray);
    void sendportnametoui(QString);
    void sendportnametocom(QString,QString);
    void startscan();
    void closecom();


};

#endif // MYCONTROL_H

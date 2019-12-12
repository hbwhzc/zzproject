#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <mycontrol.h>
#include <mythread.h>
#include <qmessagebox.h>
int debug=0;
//程序应该比较简洁吧==然后我没写注释哈哈
//顺着信号从ui到串口以及从串口到ui这样来读程序应该要更容易理解
//有没有其他的问题我也不知道啊，哈哈
//created by zz
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_open->setEnabled(false);
    /*以下内容不属于程序框架*/
    ui->pushButton_d->setEnabled(false);
    ui->pushButton_u->setEnabled(false);
    ui->pushButton_l->setEnabled(false);
    ui->pushButton_right->setEnabled(false);
    ui->pushButton_lu->setEnabled(false);
    ui->pushButton_ld->setEnabled(false);
    ui->pushButton_lround->setEnabled(false);
    ui->pushButton_rd->setEnabled(false);
    ui->pushButton_ru->setEnabled(false);
    ui->pushButton_rround->setEnabled(false);
    ui->pushButton_redroad->setEnabled(false);
    ui->pushButton_stop->setEnabled(false);
    ui->pushButton_pin_1->setEnabled(false);
    ui->pushButton_pin_2->setEnabled(false);
    ui->pushButton_board_1->setEnabled(false);
    ui->pushButton_board_2->setEnabled(false);
    ui->pushButton_debug_on->setEnabled(false);
    /*-------------------*/
    ui->textEdit_read->setReadOnly(true);
    ui->lineEdit_debug->setReadOnly(true);
    mycontrol *commander;
    commander = new mycontrol;
    connect(this,SIGNAL(scancom()),commander,SLOT(init()));
    connect(commander,SIGNAL(sendtoui(QString)),this,SLOT(uirev(QString)));
    connect(this,SIGNAL(send(QByteArray)),commander,SLOT(revuibtn(QByteArray)));
    connect(commander,SIGNAL(sendportnametoui(QString)),this,SLOT(portname(QString)));
    connect(this,SIGNAL(opencom(QString,QString)),commander,SLOT(readuicom(QString,QString)));
    connect(this,SIGNAL(shutdown()),commander,SLOT(uishutdown()));

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::uirev(QString str)
{
    ui->textEdit_read->append(str);
}

void MainWindow::portname(QString portname)
{
    ui->comboBox_com->addItem(portname);
    ui->pushButton_open->setEnabled(true);
    /*以下内容不属于程序框架*/
    ui->pushButton_d->setEnabled(true);
    ui->pushButton_u->setEnabled(true);
    ui->pushButton_l->setEnabled(true);
    ui->pushButton_right->setEnabled(true);
    ui->pushButton_lu->setEnabled(true);
    ui->pushButton_ld->setEnabled(true);
    ui->pushButton_lround->setEnabled(true);
    ui->pushButton_rd->setEnabled(true);
    ui->pushButton_ru->setEnabled(true);
    ui->pushButton_rround->setEnabled(true);
    ui->pushButton_redroad->setEnabled(true);
    ui->pushButton_stop->setEnabled(true);
    ui->pushButton_pin_1->setEnabled(true);
    ui->pushButton_pin_2->setEnabled(true);
    ui->pushButton_board_1->setEnabled(true);
    ui->pushButton_board_2->setEnabled(true);
    /*-------------------*/
    ui->pushButton_debug_on->setEnabled(true);
}

void MainWindow::on_pushButton_open_clicked()
{
    qDebug()<<tr("btn OK")<<endl;
    QString boxname = ui->comboBox_com->currentText();
    QString baud = ui->textEdit_baud->toPlainText();
    emit opencom(boxname,baud);
}

void MainWindow::on_pushButton_scan_clicked()
{
    emit scancom();
}

/*以下内容不属于程序框架*/
void MainWindow::on_pushButton_lu_clicked()
{
    QByteArray msg = "1011";
    emit send(msg);
}

void MainWindow::on_pushButton_ru_clicked()
{
    QByteArray msg = "1101";
    emit send(msg);
}

void MainWindow::on_pushButton_ld_clicked()
{
    QByteArray msg = "1000";
    emit send(msg);
}

void MainWindow::on_pushButton_rd_clicked()
{
    QByteArray msg = "1001";
    emit send(msg);
}

void MainWindow::on_pushButton_u_clicked()
{
    QByteArray msg = "111";
    emit send(msg);
}

void MainWindow::on_pushButton_l_clicked()
{
    QByteArray msg = "110";
    emit send(msg);
}

void MainWindow::on_pushButton_right_clicked()
{
    QByteArray msg = "101";
    emit send(msg);
}

void MainWindow::on_pushButton_d_clicked()
{
    QByteArray msg = "100";
    emit send(msg);
}

void MainWindow::on_pushButton_lround_clicked()
{
    QByteArray msg = "2010";
    emit send(msg);
}

void MainWindow::on_pushButton_rround_clicked()
{
    QByteArray msg = "2001";
    emit send(msg);
}
/*----------------*/
void MainWindow::on_pushButton_debug_on_clicked()
{
    if(debug==0)
    {
        ui->lineEdit_debug->setReadOnly(false);
        ui->textEdit_read->append("进入命令调试模式");
        ui->textEdit_read->append("输入help以获得可用命令");
        ui->pushButton_debug_on->setText("关闭命令调试");
        debug=1;
    }
    else
    {
        ui->lineEdit_debug->setReadOnly(true);
        ui->textEdit_read->append("关闭命令调试模式");
        ui->pushButton_debug_on->setText("开启命令调试");
        debug=0;
    }
}

void MainWindow::on_lineEdit_debug_returnPressed()
{
    QString cmd = ui->lineEdit_debug->text();
    QString checkwrite = cmd.mid(0,5);
    ui->lineEdit_debug->clear();
    qDebug()<<cmd<<endl;
    qDebug()<<checkwrite<<endl;
    if(checkwrite=="write" && cmd!="write")
    {
        QString writething = cmd.mid(6);
        QByteArray msg = writething.toLatin1();
        emit send(msg);
    }
    else if (cmd=="help")
    {
        ui->textEdit_read->append("输入write xxx向串口发送信息");
        ui->textEdit_read->append("输入shutdown来安全关闭程序");
        ui->textEdit_read->append("输入reset向单片机发送复位指令");
        ui->textEdit_read->append("输入clear来清空信息框");
    }
    else if (cmd=="reset")
    {
        QByteArray msg = "reset";
        emit send(msg);
    }
    else if (cmd=="clear")
    {
        ui->textEdit_read->clear();
    }
    else if (cmd=="shutdown")
    {
        ui->textEdit_read->clear();
        emit shutdown();
        ui->comboBox_com->clear();
        close();


    }
    else
    {
        ui->textEdit_read->append("unknown command");
    }

}

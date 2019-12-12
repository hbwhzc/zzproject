#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QDebug>
#include <mythread.h>
extern int debug;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void btnwrite();
public slots:
    void uirev(QString);
    void portname(QString);
private slots:


    //void on_pushButton_stop_clicked();

    void on_pushButton_open_clicked();

    void on_pushButton_scan_clicked();

    void on_pushButton_lu_clicked();

    void on_pushButton_ru_clicked();

    void on_pushButton_ld_clicked();

    void on_pushButton_rd_clicked();

    void on_pushButton_u_clicked();

    void on_pushButton_l_clicked();

    void on_pushButton_right_clicked();

    void on_pushButton_d_clicked();

    void on_pushButton_lround_clicked();

    void on_pushButton_rround_clicked();

    void on_pushButton_debug_on_clicked();

    void on_lineEdit_debug_returnPressed();

private:
    Ui::MainWindow *ui;
signals:
    void send(QByteArray);
    void opencom(QString,QString);
    void scancom();
    void shutdown();

};

#endif // MAINWINDOW_H

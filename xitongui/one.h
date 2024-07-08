#ifndef ONE_H
#define ONE_H
#include <QDialog>
#include "widget.h"
#include "mqtt/qmqtt.h"
#include "qcustomplot.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>
#include <QPainter>
#include <QMessageBox>
#include <QMouseEvent>

class Widget; // 前向声明

namespace Ui {
class one;
}

class one : public QDialog
{
    Q_OBJECT

public:
    explicit one(QWidget *parent = nullptr);
    ~one();
    QString Dir;
    void paintEvent(QPaintEvent * event);
    void setPreviousWidget(QWidget *widget); // 添加这个方法

private slots:
    void on_pushButton_clicked();
    void insert_table1(QString date, QString tp1, QString ph1, QString zd1,QString dd1, QString dc1);
    void insert_table2(QString date, QString tp2, QString ph2, QString zd2,QString dd2, QString dc2);
    void insert_table3(QString date, QString tp3, QString ph3, QString zd3,QString dd3, QString dc3);
    void customsplot_init();
    //double wendu1,wendu2;

    void on_xieru_clicked();

    void on_stop_clicked();

    void on_qc_clicked();

    void on_qc_2_clicked();

    void on_qc_3_clicked();

    void on_save_clicked();

    void on_save_2_clicked();

    void on_save_3_clicked();

private:
    Ui::one *ui;
    QWidget *previousWidget; // 添加这个成员变量
    QTimer *_pTimerUpdate,*dingshiqi;
    QElapsedTimer _elapsedTimer;        //之间计时
};

#endif // ONE_H

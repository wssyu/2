#ifndef TWO_H
#define TWO_H

#include <QDialog>
#include "widget.h"
#include "qcustomplot.h"

class Widget; // 前向声明
namespace Ui {
class two;
}

class two : public QDialog
{
    Q_OBJECT

public:
    explicit two(QWidget *parent = nullptr);
    ~two();
    void paintEvent(QPaintEvent * event);
    void setPreviousWidget1(QWidget *widget); // 添加这个方法

private slots:
    void on_fanhui_clicked();
    void customsplot_init();   //绘图
    //QCustomPlot *customPlot, *customPlot1, *customPlot2, *customPlot3;

    void on_fanhui_2_clicked();

    void on_fanhui_3_clicked();

private:
    Ui::two *ui;

    QCustomPlot *customPlot1,*customPlot2,*customPlot3,*customPlot4;
    QWidget *previousWidget; // 添加这个成员变量
    QTimer *_pTimerUpdate,*dingshiqi;
    QElapsedTimer _elapsedTimer;        //之间计时
};

#endif // TWO_H

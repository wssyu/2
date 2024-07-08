#ifndef THREE_H
#define THREE_H

#include <QDialog>
#include "widget.h"
#include <QCheckBox>
#include <QSpinBox>
#include <QTimer>
class Widget; // 前向声明
namespace Ui {
class three;
}

class three : public QDialog
{
    Q_OBJECT

public:
    explicit three(QWidget *parent = nullptr);
    ~three();
    void paintEvent(QPaintEvent * event);
    void setPreviousWidget2(QWidget *widget); // 添加这个方法
    static int tpx1,tpx2,tpx3;
    static int phx1,phx2,phx3;
    static int zdx1,zdx2,zdx3;
    static int ddx1,ddx2,ddx3;

private slots:
    void on_fanhui_clicked();
    void onYuzhiStateChanged(int state);
    void compareValue();
    void yichang();
    void yuce();
    void xunlian();
    //void on_yuzhi_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_checkBox_3_stateChanged(int arg1);

    void on_xunlian_stateChanged(int arg1);

    void on_close_serialport_clicked();

    void on_pushButton_13_clicked();

private:
    Ui::three *ui;
    QWidget *previousWidget; // 添加这个成员变量
    int zdmax,ddmax;
    int zdmin,ddmin;
    double tpmax,phmax;
    double tpmin,phmin;
    QTimer *comparisonTimer;  // 定时器
    QTimer *comparisonTimer1;  // 定时器
    QTimer *comparisonTimer2;  // 定时器
    QTimer *comparisonTimer3;  // 定时器
    // 数据存储向量
    std::vector<double> tp1Data;
    std::vector<double> tp2Data;
    std::vector<double> tp3Data;

    std::vector<double> ph1Data;
    std::vector<double> ph2Data;
    std::vector<double> ph3Data;

    std::vector<double> zd1Data;
    std::vector<double> zd2Data;
    std::vector<double> zd3Data;

    std::vector<int> dd1Data;
    std::vector<int> dd2Data;
    std::vector<int> dd3Data;

    QString lastLoggedDate;

    // 辅助函数
    double calculateMean(const std::vector<double> &data);
    double calculateStdDev(const std::vector<double> &data, double mean);
    //void detectSingleOutlier(const std::vector<double> &data, const QString &varName);
    void detectSingleOutlier(const std::vector<double> &data, const QString &varName, double sum, int count);
    double linearRegressionPredict(const std::vector<double> &data);
    // 静态变量用于保存总和和计数
    double tp1Sum;
    int tp1Count;
    double tp2Sum;
    int tp2Count;
    double tp3Sum;
    int tp3Count;
    double ph1Sum;
    int ph1Count;
    double ph2Sum;
    int ph2Count;
    double ph3Sum;
    int ph3Count;
    double zd1Sum;
    int zd1Count;
    double zd2Sum;
    int zd2Count;
    double zd3Sum;
    int zd3Count;
    double dd1Sum;
    int dd1Count;
    double dd2Sum;
    int dd2Count;
    double dd3Sum;
    int dd3Count;

};

#endif // THREE_H

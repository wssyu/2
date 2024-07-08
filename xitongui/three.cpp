#include "three.h"
#include "ui_three.h"
#include "widget.h"
#include <QPainter>
#include <QDebug>
#include <vector>
#include <numeric>
#include <cmath>


int three::tpx1;int three::tpx2;int three::tpx3;
int three::phx1;int three::phx2;int three::phx3;
int three::zdx1;int three::zdx2;int three::zdx3;
int three::ddx1;int three::ddx2;int three::ddx3;

three::three(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::three),
    tp1Sum(0.0),
        tp1Count(0),
        tp2Sum(0.0),
        tp2Count(0),
        tp3Sum(0.0),
        tp3Count(0),
        ph1Sum(0.0),
        ph1Count(0),
        ph2Sum(0.0),
        ph2Count(0),
        ph3Sum(0.0),
        ph3Count(0),
        zd1Sum(0.0),
        zd1Count(0),
        zd2Sum(0.0),
        zd2Count(0),
        zd3Sum(0.0),
        zd3Count(0),
        dd1Sum(0.0),
        dd1Count(0),
        dd2Sum(0.0),
        dd2Count(0),
        dd3Sum(0.0),
        dd3Count(0)
{
    ui->setupUi(this);
    // 初始化定时器
    comparisonTimer = new QTimer(this);
    comparisonTimer->setInterval(500); // 设置定时器间隔为1秒
    comparisonTimer1 = new QTimer(this);
    comparisonTimer1->setInterval(2000); // 设置定时器间隔为1秒
    comparisonTimer2 = new QTimer(this);
    comparisonTimer2->setInterval(2000); // 设置定时器间隔为1秒
    comparisonTimer3 = new QTimer(this);
    comparisonTimer3->setInterval(2000); // 设置定时器间隔为1秒
    connect(comparisonTimer, &QTimer::timeout, this, &three::compareValue);
    connect(comparisonTimer1, &QTimer::timeout, this, &three::yichang);
    connect(comparisonTimer2, &QTimer::timeout, this, &three::yuce);
    connect(comparisonTimer3, &QTimer::timeout, this, &three::xunlian);
    ui->checkBox_2->setEnabled(false); // 禁用复选框 xunlian
    ui->checkBox_3->setEnabled(false); // 禁用复选框 xunlian
    // 连接yuzhi控件的stateChanged信号到槽函数
    connect(ui->yuzhi, &QCheckBox::stateChanged, this, &three::onYuzhiStateChanged);



}
three::~three()
{
    delete ui;
}

void three::onYuzhiStateChanged(int state)
{
    if (state == Qt::Checked)
    {
        // 用户选中复选框时启动定时器
        comparisonTimer->start();

    }
    else
    {
        // 用户取消选中复选框时停止定时器
        comparisonTimer->stop();
    }
}

void three::compareValue()
{
    if (ui->yuzhi->isChecked())
    {
        tpmax = ui->tpmax->value();
        phmax = ui->phmax->value();
        zdmax = ui->zdmax->value();
        ddmax = ui->ddmax->value();
        tpmin = ui->tpmin->value();
        phmin = ui->phmin->value();

        tpx1=0;tpx2=0;tpx3=0;
        phx1=0;phx2=0;phx3=0;
        zdx1=0;zdx2=0;zdx3=0;
        ddx1=0;ddx2=0;ddx3=0;
        if (Widget::tp1 > tpmax)
        {
            tpx1=1;
        }
        if (Widget::tp1 < tpmin)
        {
            tpx1=-1;

        }
        if (Widget::tp2 > tpmax)
        {
            tpx2=1;

        }
        if (Widget::tp2 < tpmin)
        {
            tpx2=-1;

        }
        if (Widget::tp3 > tpmax)
        {
            tpx3=1;

        }
        if (Widget::tp3 < tpmin)
        {
            tpx3=-1;

        }
        if (Widget::ph1 > phmax)
        {
            phx1=1;
        }
        if (Widget::ph1 < phmin)
        {
            phx1=-1;

        }
        if (Widget::ph2 > phmax)
        {
            phx2=1;

        }
        if (Widget::ph2 < phmin)
        {
            phx2=-1;

        }
        if (Widget::ph3 > phmax)
        {
            phx3=1;

        }
        if (Widget::ph3 < phmin)
        {
            phx3=-1;

        }
        if (Widget::zd1 > zdmax)
        {
            zdx1=1;
        }

        if (Widget::zd2 > zdmax)
        {
            zdx2=1;

        }
        if (Widget::zd3 > zdmax)
        {
            zdx3=1;

        }

        if (Widget::dd1 > ddmax)
        {
            ddx1=1;
        }

        if (Widget::dd2 > ddmax)
        {
            ddx2=1;

        }
        if (Widget::dd3 > ddmax)
        {
            ddx3=1;
        }

    }
    else
    {
        // 如果yuzhi复选框未选中，不进行比较
        //qDebug() << "Checkbox is unchecked. Comparison skipped.";
    }
}

void three::on_checkBox_2_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked)
    {
        // 用户选中复选框时启动定时器
        comparisonTimer1->start();

    }
    else
    {
        // 用户取消选中复选框时停止定时器
        comparisonTimer1->stop();

    }
}


// 计算均值
double three::calculateMean(const std::vector<double> &data) {
    return std::accumulate(data.begin(), data.end(), 0.0) / data.size();
}

// 计算标准差
double three::calculateStdDev(const std::vector<double> &data, double mean) {
    double sum = 0.0;
    for (const auto &value : data) {
        sum += std::pow(value - mean, 2);
    }
    return std::sqrt(sum / data.size());
}

// 检测单个变量的异常值
//    qDebug() << "变量" << varName << "数据:" << data;
//    qDebug() << "变量" << varName << "均值:" << dataMean;
//    qDebug() << "变量" << varName << "标准差:" << dataStdDev;

void three::detectSingleOutlier(const std::vector<double> &data, const QString &varName, double sum, int count) {
    if (data.size() < 2) return;  // 确保有足够的数据点进行计算
    double dataMean = sum / count;
    double dataStdDev = calculateStdDev(data, dataMean);
    double threshold = 3.0; // 通常选择2或3倍标准差作为阈值

    QString current_date = ui->textEdit1->toPlainText();
    QDateTime current_date_time = QDateTime::currentDateTime();
    current_date += current_date_time.toString("hh:mm:ss");
    current_date += varName;
    current_date += "出现异常值: ";

    bool isFirstValue = true;  // 标记是否是第一个异常值

    for (const auto &value : data) {
        if (std::abs(value - dataMean) > threshold * dataStdDev) {
            qDebug() << "变量" << varName << "的异常值:" << value;

            // 判断是否和上次记录的内容一样
            if (!isFirstValue && current_date == lastLoggedDate) {
                continue;  // 如果和上一次一样，则跳过显示
            }

            current_date += QString::number(value);
            current_date += "\n";
            ui->textEdit1->setText(current_date);
            ui->textEdit1->moveCursor(QTextCursor::End); // 移动到最后一行

            // 更新上一次记录的内容
            lastLoggedDate = current_date;
            isFirstValue = false;
        }
    }
}

void three::xunlian()
{
    ui->checkBox_2->setEnabled(true); // 禁用复选框 xunlian
    ui->checkBox_3->setEnabled(true); // 禁用复选框 xunlian
    // 接收新数据
    double newTp1 = Widget::tp1;
    double newTp2 = Widget::tp2;
    double newTp3 = Widget::tp3;
    double newph1 = Widget::ph1;
    double newph2 = Widget::ph2;
    double newph3 = Widget::ph3;
    double newzd1 = Widget::zd1;
    double newzd2 = Widget::zd2;
    double newzd3 = Widget::zd3;
    int newdd1 = Widget::dd1;
    int newdd2 = Widget::dd2;
    int newdd3 = Widget::dd3;

    // 更新总和和计数
    tp1Sum += newTp1;
    tp1Count++;
    tp2Sum += newTp2;
    tp2Count++;
    tp3Sum += newTp3;
    tp3Count++;
    ph1Sum += newph1;
    ph1Count++;
    ph2Sum += newph2;
    ph2Count++;
    ph3Sum += newph3;
    ph3Count++;
    zd1Sum += newzd1;
    zd1Count++;
    zd2Sum += newzd2;
    zd2Count++;
    zd3Sum += newzd3;
    zd3Count++;
    dd1Sum += newdd1;
    dd1Count++;
    dd2Sum += newdd2;
    dd2Count++;
    dd3Sum += newdd3;
    dd3Count++;

    // 将新数据添加到存储向量中
    tp1Data.push_back(newTp1);
    tp2Data.push_back(newTp2);
    tp3Data.push_back(newTp3);
    ph1Data.push_back(newph1);
    ph2Data.push_back(newph2);
    ph3Data.push_back(newph3);
    zd1Data.push_back(newzd1);
    zd2Data.push_back(newzd2);
    zd3Data.push_back(newzd3);
    dd1Data.push_back(newdd1);
    dd2Data.push_back(newdd2);
    dd3Data.push_back(newdd3);

}



void three::yichang() {
    // 静态变量用于保存总和和计数


    // 输出存储向量的内容
//    qDebug() << "当前 tp1Data 数据: " << tp1Data;
//    qDebug() << "当前 ph1Data 数据: " << ph1Data;
//    qDebug() << "当前 zd1Data 数据: " << zd1Data;
//    qDebug() << "当前 dd1Data 数据: " << dd1Data;


    // 检测异常值
    detectSingleOutlier(tp1Data, "节点一水温", tp1Sum, tp1Count);
    detectSingleOutlier(tp2Data, "节点二水温", tp2Sum, tp2Count);
    detectSingleOutlier(tp3Data, "节点三水温", tp3Sum, tp3Count);
    detectSingleOutlier(ph1Data, "节点一pH值", ph1Sum, ph1Count);
    detectSingleOutlier(ph2Data, "节点二pH值", ph2Sum, ph2Count);
    detectSingleOutlier(ph3Data, "节点三pH值", ph3Sum, ph3Count);
    detectSingleOutlier(zd1Data, "节点一浊度", zd1Sum, zd1Count);
    detectSingleOutlier(zd2Data, "节点二浊度", zd2Sum, zd2Count);
    detectSingleOutlier(zd3Data, "节点三浊度", zd3Sum, zd3Count);
    detectSingleOutlier(std::vector<double>(dd1Data.begin(), dd1Data.end()), "节点一电导率", dd1Sum, dd1Count);
    detectSingleOutlier(std::vector<double>(dd2Data.begin(), dd2Data.end()), "节点二电导率", dd2Sum, dd2Count);
    detectSingleOutlier(std::vector<double>(dd3Data.begin(), dd3Data.end()), "节点三电导率", dd3Sum, dd3Count);
}

// 线性回归预测函数
double three::linearRegressionPredict(const std::vector<double> &data)
{
    int n = data.size();
    if (n < 2) return 0.0; // 需要至少两个点进行预测

    double xSum = 0.0;
    double ySum = 0.0;
    double xySum = 0.0;
    double xxSum = 0.0;

    for (int i = 0; i < n; ++i) {
        xSum += i;
        ySum += data[i];
        xySum += i * data[i];
        xxSum += i * i;
    }

    double slope = (n * xySum - xSum * ySum) / (n * xxSum - xSum * xSum);
    double intercept = (ySum - slope * xSum) / n;

    return slope * n + intercept; // 预测下一个时间点的值
}

void three::yuce()
{
//    qDebug() << "当前 tp1Data 数据: " << tp1Data;

    // 预测下一个时间点的值
    double tp1Prediction = linearRegressionPredict(tp1Data);
    double tp2Prediction = linearRegressionPredict(tp2Data);
    double tp3Prediction = linearRegressionPredict(tp3Data);
    double ph1Prediction = linearRegressionPredict(ph1Data);
    double ph2Prediction = linearRegressionPredict(ph2Data);
    double ph3Prediction = linearRegressionPredict(ph3Data);
    double zd1Prediction = linearRegressionPredict(zd1Data);
    double zd2Prediction = linearRegressionPredict(zd2Data);
    double zd3Prediction = linearRegressionPredict(zd3Data);
    double dd1Prediction = linearRegressionPredict(std::vector<double>(dd1Data.begin(), dd1Data.end()));
    double dd2Prediction = linearRegressionPredict(std::vector<double>(dd2Data.begin(), dd2Data.end()));
    double dd3Prediction = linearRegressionPredict(std::vector<double>(dd3Data.begin(), dd3Data.end()));
    ui->lcdNumber_11->display(QString::number(tp1Prediction, 'f', 1));
    ui->lcdNumber_12->display(QString::number(ph1Prediction, 'f', 1));
    ui->lcdNumber_13->display(QString::number(zd1Prediction, 'f', 1));
    ui->lcdNumber_14->display(QString::number(static_cast<int>(dd1Prediction)));

    ui->lcdNumber_21->display(QString::number(tp2Prediction, 'f', 1));
    ui->lcdNumber_22->display(QString::number(ph2Prediction, 'f', 1));
    ui->lcdNumber_23->display(QString::number(zd2Prediction, 'f', 1));
    ui->lcdNumber_24->display(QString::number(static_cast<int>(dd2Prediction)));

    ui->lcdNumber_31->display(QString::number(tp3Prediction, 'f', 1));
    ui->lcdNumber_32->display(QString::number(ph3Prediction, 'f', 1)); // 显示整数
    ui->lcdNumber_33->display(QString::number(zd3Prediction, 'f', 1)); // 显示整数
    ui->lcdNumber_34->display(QString::number(static_cast<int>(dd3Prediction)));

//    qDebug() << "预测 tp1 的下一个值: " << tp1Prediction;
//    qDebug() << "预测 ph1 的下一个值: " << ph1Prediction;
//    qDebug() << "预测 zd1 的下一个值: " << zd1Prediction;
//    qDebug() << "预测 dd1 的下一个值: " << dd1Prediction;
}





void three::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, width(), height(), QPixmap(":/321.jpg"));
}

void three::setPreviousWidget2(QWidget *widget)
{
    previousWidget = widget; // 设置前一个窗口
}

void three::on_fanhui_clicked()
{
    if (previousWidget) {
        previousWidget->show();
    }
    this->hide();
}


void three::on_checkBox_3_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked)
    {
        // 用户选中复选框时启动定时器
        comparisonTimer2->start();

    }
    else
    {
        // 用户取消选中复选框时停止定时器
        comparisonTimer2->stop();

    }


}

void three::on_xunlian_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked)
    {
        // 用户选中复选框时启动定时器
        comparisonTimer3->start();
        ui->checkBox_2->setEnabled(true); // 禁用复选框 xunlian
        ui->checkBox_3->setEnabled(true); // 禁用复选框 xunlian

    }
    else
    {
        // 用户取消选中复选框时停止定时器
        comparisonTimer3->stop();
        ui->checkBox_2->setEnabled(false); // 禁用复选框 xunlian
        ui->checkBox_3->setEnabled(false); // 禁用复选框 xunlian
    }
}

void three::on_close_serialport_clicked()
{
    tp1Data.clear();
    tp2Data.clear();
    tp3Data.clear();
    ph1Data.clear();
    ph2Data.clear();
    ph3Data.clear();
    zd1Data.clear();
    zd2Data.clear();
    zd3Data.clear();
    dd1Data.clear();
    dd2Data.clear();
    dd3Data.clear();
    tp1Sum = 0.0;
    tp1Count = 0;
    tp2Sum = 0.0;
    tp2Count = 0;
    tp3Sum = 0.0;
    tp3Count = 0;
    ph1Sum = 0.0;
    ph1Count = 0;
    ph2Sum = 0.0;
    ph2Count = 0;
    ph3Sum = 0.0;
    ph3Count = 0;
    zd1Sum = 0.0;
    zd1Count = 0;
    zd2Sum = 0.0;
    zd2Count = 0;
    zd3Sum = 0.0;
    zd3Count = 0;
    dd1Sum = 0.0;
    dd1Count = 0;
    dd2Sum = 0.0;
    dd2Count = 0;
    dd3Sum = 0.0;
    dd3Count = 0;
}

void three::on_pushButton_13_clicked()
{
    ui->textEdit1->clear();
}

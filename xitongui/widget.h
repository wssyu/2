#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "one.h"
#include "mqtt/qmqtt.h"
#include "qcustomplot.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>
#include <QPainter>
#include <QMessageBox>
#include <QMouseEvent>
// 前向声明 one 类
class one;
class two;
class three;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void windows_init();
    void serialport_init();
    void find_serialport();     //查找串口
    void read_serialport();     //读串口数据
    void paintEvent(QPaintEvent * event);

    QString Dir;
    static int dd1,pct1;
    static int dd2,pct2;
    static int dd3,pct3;
    static  int a;
    static  double tp1,ph1,tp2,ph2,tp3,ph3,zd1,zd2,zd3;

private:
    Ui::Widget *ui;
    one *oneWindow; // 添加这个成员变量
    two *twoWindow; // 添加这个成员变量
    three *threeWindow; // 添加这个成员变量
    //one *oneWidget;
    QCustomPlot *customPlot, *customPlot1, *customPlot2, *customPlot3;
    QTimer dataTimer;           //时间
    QSerialPort *serialport, *m_serial;    //串口类
    QMQTT::Client *mqtt_client;
     QString m_strProductKey,m_strDeviceName,m_strDeviceSecret,m_strHostName,m_strRegionId,m_strPubTopic,m_strSubTopic,message;
    //double temp1,humi;
    bool flag1 = false;
    QString temp1,humi1,gz1,dc1;
    QString temp2,humi2,gz2,dc2;
    QString temp3,humi3,gz3,dc3;
    int lenght1 = 0,lenght2 = 0,lenght3 = 0;
    QCPItemText *textItem;
//    持久的缓冲区用于存储串口数据
    bool isRecording; // 标志是否已经接收到帧头
    bool str=false; // 标志数据是否已经接收完成

    // 定时器
    QTimer *_pTimerUpdate,*dingshiqi;
    QElapsedTimer _elapsedTimer;        //之间计时
    int _fps;
    int _interval;
    bool _pause;
    double _lastPointKey;


    QVector<double> x; //存储一个double类型的数据，可以动态的增加删除元素
    QVector<double> y;

    int counter=0;

private slots:
    //void pushData();
    void on_open_serialport_clicked();
    void on_close_serialport_clicked();
    void on_clear_serialport_clicked();

    void doDataReceived(QMQTT::Message msg);
    void doConnected();
    void doDisconnected();
    void doSubscribed(QString,quint8);
    void doPublished(QMQTT::Message,quint16);
    void led(QLabel* label,int color,int size);  //绘制指示灯

    void on_start_send_clicked();
    void on_close_send_clicked();
    void on_pushButton_13_clicked();
    void on_pushButton_14_clicked();
    void on_sousuo_clicked();
    void on_pushButton_15_clicked();
    void on_pushButton_16_clicked();
};
#endif // WIDGET_H

#include "widget.h"
#include "one.h"
#include "two.h"
#include "three.h"
#include "ui_widget.h"

double Widget::tp1;double Widget::ph1;double Widget::zd1;int Widget::dd1;int Widget::pct1;
double Widget::tp2;double Widget::ph2;double Widget::zd2;int Widget::dd2;int Widget::pct2;
double Widget::tp3;double Widget::ph3;double Widget::zd3;int Widget::dd3;int Widget::pct3;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget),
    oneWindow(nullptr),twoWindow(nullptr),threeWindow(nullptr)// 初始化为 nullptr

{

    ui->setupUi(this);
    //this->setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint);
    mqtt_client = new QMQTT::Client;
    m_strSubTopic = "/iot/5810/sub/123";
    m_strPubTopic = "/iot/5810/pub/123";
    mqtt_client->setHostName("t.yoyolife.fun");
    //mqtt_client->setHostName("8.148.7.210");
    mqtt_client->setPort(1883);
    mqtt_client->setUsername("771b32d0d2d575fb6b9f3c1bcacd11d6");
    mqtt_client->setPassword("123456");
    mqtt_client->setKeepAlive(30);
    serialport = new QSerialPort; //创建一个新的串口对象
    //windows_init();
    ui->batteryBar1->setValue(0);
    ui->batteryBar1_2->setValue(0);
    ui->batteryBar1_3->setValue(0);
    Dir=QCoreApplication::applicationDirPath();
    connect(mqtt_client,SIGNAL(connected()),this,SLOT(doConnected()));//连接成功
    /*获取时间*/
    ui->label_time_1->setText(QTime::currentTime().toString("hh:mm"));
    ui->label_time_2->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd ddd"));

}

Widget::~Widget()
{
    delete ui,serialport;
     delete oneWindow; // 确保删除窗口对象
}


//页面初始化
void Widget::windows_init()
{
    //int temp2=2;
}

//LED绘制函数
void Widget::led(QLabel* label,int color,int size)
{
    QString min_width = QString("min-width: %1px;").arg(size);              // 最小宽度：size
        QString min_height = QString("min-height: %1px;").arg(size);            // 最小高度：size
        QString max_width = QString("max-width: %1px;").arg(size);              // 最小宽度：size
        QString max_height = QString("max-height: %1px;").arg(size);            // 最小高度：size
        // 再设置边界形状及边框
        QString border_radius = QString("border-radius: %1px;").arg(size/2);    // 边框是圆角，半径为size/2
        QString border = QString("border:1px solid black;");                    // 边框为1px黑色
        // 最后设置背景颜色
        QString background = "background-color:";

    switch(color)
    {
     case 0: background +="rgb(190,190,190)"; break;   //灰色
     case 1: background +="rgb(255,0,0)"; break;       //红色
     case 2: background +="rgb(0,255,0)"; break;        //绿色
     case 3: background +="rgb(25,34,196)";break;      //蓝色

    }
    const QString SheetStyle = min_width + min_height + max_width + max_height + border_radius + border + background;
    label->setStyleSheet(SheetStyle);
}

//打开串口
void Widget::on_open_serialport_clicked()
{
    ui->close_serialport->setEnabled(true);
    ui->open_serialport->setEnabled(false);
    ui->start_send->setEnabled(true);
    ui->close_send->setEnabled(true);
    //mqtt_client->connectToHost();
    if(ui->com->count() != 0)   //不为空时
    //初始化串口
    serialport->setPortName(ui->com->currentText());//设置串口名
        if(serialport->open(QIODevice::ReadWrite)) //打开串口成功
        {

            serialport->setBaudRate(9600);       //设置波特率
            serialport->setDataBits(QSerialPort::Data8); //设置数据位
            serialport->setParity(QSerialPort::NoParity); //设置校验位
            serialport->setStopBits(QSerialPort::OneStop); //设置停止位
            QMessageBox::information(this,tr("提示"),tr("串口打开成功"),QMessageBox::Ok);
            QObject::connect(serialport, &QSerialPort::readyRead, this, &Widget::read_serialport); //读数据，如果不加这一行代码的话，数据不能正常显示
//QObject::connect(m_serial, &QSerialPort::readyRead, this, &Widget::jeidianshuju);
//这行代码使用了Qt的信号与槽机制，将serialport对象的readyRead信号连接到Widget对象的read_serialport槽函数上，意味着当serialport对象接收到数据时，
//会自动触发read_serialport函数进行处理。其中，&QSerialPort::readyRead表示readyRead信号的地址，this表示Widget对象的指针，&Widget::read_serialport表示read_serialport槽函数的地址。
            //操作 记录
            QString current_date = ui->textEdit->toPlainText();
            QDateTime current_date_time =QDateTime::currentDateTime();
            current_date +=current_date_time.toString("yyyy.MM.dd hh:mm");
            current_date += " 打开串口" ;
            current_date += "\n";
            ui->textEdit->setText(current_date);
            ui->textEdit->moveCursor(QTextCursor::End); //移动到最后一行

            //显示日志
            //操作 记录
            QString current_date1 = ui->textEdit1->toPlainText();
            QDateTime current_date_time1 =QDateTime::currentDateTime();
            current_date1 +=current_date_time1.toString("hh:mm:ss");
            current_date1 += "打开串口 开始接收设备一数据" ;
            current_date1 += "\n";
            ui->textEdit1->setText(current_date1);
            ui->textEdit1->moveCursor(QTextCursor::End); //移动到最后一行

            //显示日志
            //操作 记录
            QString current_date2 = ui->textEdit2->toPlainText();
            QDateTime current_date_time2 =QDateTime::currentDateTime();
            current_date2 +=current_date_time2.toString("hh:mm:ss");
            current_date2 += "打开串口 开始接收设备二数据" ;
            current_date2+= "\n";
            ui->textEdit2->setText(current_date2);
            ui->textEdit2->moveCursor(QTextCursor::End); //移动到最后一行

            //显示日志
            //操作 记录
            QString current_date3 = ui->textEdit3->toPlainText();
            QDateTime current_date_time3 =QDateTime::currentDateTime();
            current_date3 +=current_date_time3.toString("hh:mm:ss");
            current_date3 += "打开串口 开始接收设备三数据" ;
            current_date3+= "\n";
            ui->textEdit3->setText(current_date3);
            ui->textEdit3->moveCursor(QTextCursor::End); //移动到最后一行
        }
        else //串口打开失败
        {
            QMessageBox::information(this,tr("错误"),tr("串口打开失败"),QMessageBox::Ok);
            //操作 记录
            QString current_date = ui->textEdit->toPlainText();
            QDateTime current_date_time =QDateTime::currentDateTime();
            current_date +=current_date_time.toString("yyyy.MM.dd hh:mm");
            current_date += "串口未打开" ;
            current_date += "\n";
            ui->textEdit->setText(current_date);
            ui->textEdit->moveCursor(QTextCursor::End); //移动到最后一行
        }

}

// 处理串口数据
void Widget::read_serialport()
{
    static QByteArray dataBuffer; // 新创建的数组用于存放数据
    QByteArray buf,buffer;
    buf = serialport->readAll();
    buffer.append(buf);
    for (int i = 0; i < buffer.size(); ++i)
    {
        if (buffer.at(i) == 'E')
        {
            isRecording = true;
            dataBuffer.clear();             // 清空数据数组，准备接收新的数据
            // 将 'E' 后面的数据存放到数据数组中
            for (int j = i + 1; j < buffer.size(); ++j) {
                dataBuffer.append(buffer.at(j));
            }
            buffer.clear();                 // 清空缓冲区
            break;                          // 跳出当前循环，因为已经找到 'E'，无需继续遍历缓冲区
        }
        else if (buffer.at(i) == 'F' && isRecording)
        {
            // 如果检测到 'F' 且正在记录中，则表示数据接收完整
            qDebug() << "Complete data:" << dataBuffer;

            isRecording = false;
            // 清空缓冲区，准备接收新的数据
            buffer.clear();
            break;                          // 跳出当前循环，因为已经找到 'F'，无需继续遍历缓冲区
        }
        else if (isRecording)
        {
            // 如果正在记录中，则将当前字符存储在缓冲区中
             dataBuffer.append(buffer.at(i));
        }
    }
    if(isRecording == false)
    {
        qDebug() << "Complete data1:" << dataBuffer;
        // 解析并提取数据
        QList<QByteArray> dataList = dataBuffer.split(',');
        QMap<QString, QString> dataMap;
        foreach (const QByteArray &item, dataList) {
            QList<QByteArray> keyValue = item.split(':');
            if (keyValue.size() == 2) {
                QString key = QString::fromUtf8(keyValue[0]).trimmed();
                QString value = QString::fromUtf8(keyValue[1]).trimmed();
                dataMap[key] = value;
            }
        }
//        打印一下节点是否来了
        if (dataBuffer.left(3) == "tp1")
        {
            tp1 = dataMap.value("tp1").toDouble();
            ph1 = dataMap.value("ph1").toDouble();
            zd1 = dataMap.value("zd1").toDouble();
            dd1 = dataMap.value("dd1").toInt();
            pct1 = dataMap.value("pct1").toInt();
            // 清空缓冲区，准备接收新的数据
            buffer.clear();
            // 阈值比较
            if (three::tpx1 == 1)
            {
                ui->tplab1->setText("水温过高");
                QString current_date = ui->textEdit1->toPlainText();
                QDateTime current_date_time =QDateTime::currentDateTime();
                current_date +=current_date_time.toString("hh:mm:ss");
                current_date += "节点一水温过高" ;
                current_date += "\n";
                ui->textEdit1->setText(current_date);
                ui->textEdit1->moveCursor(QTextCursor::End); //移动到最后一行
            }
            else if (three::tpx1 == -1)
            {
                ui->tplab1->setText("水温过低");
                QString current_date = ui->textEdit1->toPlainText();
                QDateTime current_date_time =QDateTime::currentDateTime();
                current_date +=current_date_time.toString("hh:mm:ss");
                current_date += "节点一水温过低" ;
                current_date += "\n";
                ui->textEdit1->setText(current_date);
                ui->textEdit1->moveCursor(QTextCursor::End); //移动到最后一行
            }
            else if (three::tpx1 == 0)
            {
                ui->tplab1->setText("");
            }
            if (three::phx1 == 1)
            {
                ui->phlab1->setText("pH过高");
                QString current_date = ui->textEdit1->toPlainText();
                QDateTime current_date_time =QDateTime::currentDateTime();
                current_date +=current_date_time.toString("hh:mm:ss");
                current_date += "节点一pH过高" ;
                current_date += "\n";
                ui->textEdit1->setText(current_date);
                ui->textEdit1->moveCursor(QTextCursor::End); //移动到最后一行
            }
            else if (three::phx1 == -1)
            {
                ui->phlab1->setText("pH过低");
                QString current_date = ui->textEdit1->toPlainText();
                QDateTime current_date_time =QDateTime::currentDateTime();
                current_date +=current_date_time.toString("hh:mm:ss");
                current_date += "节点一pH过低" ;
                current_date += "\n";
                ui->textEdit1->setText(current_date);
                ui->textEdit1->moveCursor(QTextCursor::End); //移动到最后一行
            }
            else if (three::phx1 == 0)
            {
                ui->phlab1->setText("");
            }
            if (three::zdx1 == 1)
            {
                ui->zdlab1->setText("水质浑浊");
                QString current_date = ui->textEdit1->toPlainText();
                QDateTime current_date_time =QDateTime::currentDateTime();
                current_date +=current_date_time.toString("hh:mm:ss");
                current_date += "节点一水质浑浊" ;
                current_date += "\n";
                ui->textEdit1->setText(current_date);
                ui->textEdit1->moveCursor(QTextCursor::End); //移动到最后一行
            }

            else if (three::zdx1 == 0)
            {
                ui->zdlab1->setText("");
            }
            if (three::ddx1 == 1)
            {
                ui->ddlab1->setText("重金属含量高");
                QString current_date = ui->textEdit1->toPlainText();
                QDateTime current_date_time =QDateTime::currentDateTime();
                current_date +=current_date_time.toString("hh:mm:ss");
                current_date += "节点一重金属含量高" ;
                current_date += "\n";
                ui->textEdit1->setText(current_date);
                ui->textEdit1->moveCursor(QTextCursor::End); //移动到最后一行
            }

            else if (three::ddx1 == 0)
            {
                ui->ddlab1->setText("");
            }


            //qDebug() <<"收到节点一";
            //显示日志
            //操作 记录
            QString current_date = ui->textEdit1->toPlainText();
            QDateTime current_date_time =QDateTime::currentDateTime();
            current_date +=current_date_time.toString("hh:mm:ss");
            current_date += "收到节点一" ;
            current_date += "\n";
            ui->textEdit1->setText(current_date);
            ui->textEdit1->moveCursor(QTextCursor::End); //移动到最后一行
            ui->lcdNumber_11->display(tp1);
            ui->lcdNumber_12->display(ph1);
            ui->lcdNumber_13->display(zd1);
            ui->lcdNumber_14->display(dd1);
            ui->batteryBar1->setValue(pct1);//lcd  显示电量
            led(ui->LED_1,2,30);   //绿色
            //pub
            char mes[100];
            memset(mes,0,sizeof(mes));
            sprintf(mes,"{\"tp1\":%.1f,\"ph1\":%.1f,\"zd1\":%.1f,\"dd1\":%d,\"dc1\":%d}",tp1,ph1,zd1,dd1,pct1);
            message = mes;
            QMQTT::Message send_msg(136,m_strPubTopic,message.toLocal8Bit());
            if(str == true)
            {
                 mqtt_client->publish(send_msg);
            }


        }
        else
        {
            //指示灯
            led(ui->LED_1,0,30);   //灰色
        }
        if (dataBuffer.left(3) == "tp2")
        {
            tp2 = dataMap.value("tp2").toDouble();
            ph2 = dataMap.value("ph2").toDouble();
            zd2 = dataMap.value("zd2").toDouble();
            dd2 = dataMap.value("dd2").toInt();
            pct2 = dataMap.value("pct2").toInt();
            // 清空缓冲区，准备接收新的数据
            buffer.clear();
            // 阈值比较
            if (three::tpx2 == 1)
            {
                ui->tplab2->setText("水温过高");
                QString current_date = ui->textEdit2->toPlainText();
                QDateTime current_date_time =QDateTime::currentDateTime();
                current_date +=current_date_time.toString("hh:mm:ss");
                current_date += "节点一水温过高" ;
                current_date += "\n";
                ui->textEdit2->setText(current_date);
                ui->textEdit2->moveCursor(QTextCursor::End); //移动到最后一行
            }
            else if (three::tpx2 == -1)
            {
                ui->tplab2->setText("水温过低");
                QString current_date = ui->textEdit2->toPlainText();
                QDateTime current_date_time =QDateTime::currentDateTime();
                current_date +=current_date_time.toString("hh:mm:ss");
                current_date += "节点一水温过低" ;
                current_date += "\n";
                ui->textEdit2->setText(current_date);
                ui->textEdit2->moveCursor(QTextCursor::End); //移动到最后一行
            }
            else if (three::tpx2 == 0)
            {
                ui->tplab2->setText("");
            }
            if (three::phx2 == 1)
            {
                ui->phlab2->setText("pH过高");
                QString current_date = ui->textEdit2->toPlainText();
                QDateTime current_date_time =QDateTime::currentDateTime();
                current_date +=current_date_time.toString("hh:mm:ss");
                current_date += "节点一pH过高" ;
                current_date += "\n";
                ui->textEdit2->setText(current_date);
                ui->textEdit2->moveCursor(QTextCursor::End); //移动到最后一行
            }
            else if (three::phx2 == -1)
            {
                ui->phlab2->setText("pH过低");
                QString current_date = ui->textEdit2->toPlainText();
                QDateTime current_date_time =QDateTime::currentDateTime();
                current_date +=current_date_time.toString("hh:mm:ss");
                current_date += "节点一pH过低" ;
                current_date += "\n";
                ui->textEdit2->setText(current_date);
                ui->textEdit2->moveCursor(QTextCursor::End); //移动到最后一行

            }
            else if (three::phx2 == 0)
            {
                ui->phlab2->setText("");
            }
            if (three::zdx2 == 1)
            {
                ui->zdlab2->setText("水质浑浊");
                QString current_date = ui->textEdit2->toPlainText();
                QDateTime current_date_time =QDateTime::currentDateTime();
                current_date +=current_date_time.toString("hh:mm:ss");
                current_date += "节点一水质浑浊" ;
                current_date += "\n";
                ui->textEdit2->setText(current_date);
                ui->textEdit2->moveCursor(QTextCursor::End); //移动到最后一行
            }

            else if (three::zdx2 == 0)
            {
                ui->zdlab2->setText("");
            }
            if (three::ddx2 == 1)
            {
                ui->ddlab2->setText("重金属含量高");
                QString current_date = ui->textEdit2->toPlainText();
                QDateTime current_date_time =QDateTime::currentDateTime();
                current_date +=current_date_time.toString("hh:mm:ss");
                current_date += "节点一重金属含量高" ;
                current_date += "\n";
                ui->textEdit2->setText(current_date);
                ui->textEdit2->moveCursor(QTextCursor::End); //移动到最后一行
            }

            else if (three::ddx2 == 0)
            {
                ui->ddlab2->setText("");
            }
            //qDebug() <<"收到节点一";
            //显示日志
            //操作 记录
            QString current_date = ui->textEdit2->toPlainText();
            QDateTime current_date_time =QDateTime::currentDateTime();
            current_date +=current_date_time.toString("hh:mm:ss");
            current_date += "收到节点二" ;
            current_date += "\n";
            ui->textEdit2->setText(current_date);
            ui->textEdit2->moveCursor(QTextCursor::End); //移动到最后一行
            ui->lcdNumber_21->display(tp2);
            ui->lcdNumber_22->display(ph2);
            ui->lcdNumber_23->display(zd2);
            ui->lcdNumber_24->display(dd2);
            ui->batteryBar1_2->setValue(pct2);//lcd  显示电量
            led(ui->LED_2,2,30);   //绿色
            //pub
            char mes[100];
            memset(mes,0,sizeof(mes));
            sprintf(mes,"{\"tp2\":%.1f,\"ph2\":%.1f,\"zd2\":%.1f,\"dd2\":%d,\"dc2\":%d}",tp2,ph2,zd2,dd2,pct2);
            message = mes;
            QMQTT::Message send_msg(136,m_strPubTopic,message.toLocal8Bit());
            if(str == true)
            {
            mqtt_client->publish(send_msg);
            }

        }
        else
        {
            //指示灯
            led(ui->LED_2,0,30);   //灰色
        }
        if (dataBuffer.left(3) == "tp3")
        {
            tp3 = dataMap.value("tp3").toDouble();
            ph3 = dataMap.value("ph3").toDouble();
            zd3 = dataMap.value("zd3").toDouble();
            dd3 = dataMap.value("dd3").toInt();
            pct3 = dataMap.value("pct3").toInt();
            // 清空缓冲区，准备接收新的数据
            buffer.clear();
            if (three::tpx3 == 1)
            {
                ui->tplab3->setText("水温过高");
                QString current_date = ui->textEdit3->toPlainText();
                QDateTime current_date_time =QDateTime::currentDateTime();
                current_date +=current_date_time.toString("hh:mm:ss");
                current_date += "节点三水温过高" ;
                current_date += "\n";
                ui->textEdit3->setText(current_date);
                ui->textEdit3->moveCursor(QTextCursor::End); //移动到最后一行
            }
            else if (three::tpx3 == -1)
            {
                ui->tplab3->setText("水温过低");
                QString current_date = ui->textEdit3->toPlainText();
                QDateTime current_date_time =QDateTime::currentDateTime();
                current_date +=current_date_time.toString("hh:mm:ss");
                current_date += "节点三水温过低" ;
                current_date += "\n";
                ui->textEdit3->setText(current_date);
                ui->textEdit3->moveCursor(QTextCursor::End); //移动到最后一行
            }
            else if (three::tpx3 == 0)
            {
                ui->tplab3->setText("");
            }
            if (three::phx3 == 1)
            {
                ui->phlab3->setText("pH过高");
                QString current_date = ui->textEdit3->toPlainText();
                QDateTime current_date_time =QDateTime::currentDateTime();
                current_date +=current_date_time.toString("hh:mm:ss");
                current_date += "节点三pH过高" ;
                current_date += "\n";
                ui->textEdit3->setText(current_date);
                ui->textEdit3->moveCursor(QTextCursor::End); //移动到最后一行
            }
            else if (three::phx3 == -1)
            {
                ui->phlab3->setText("pH过低");
                QString current_date = ui->textEdit3->toPlainText();
                QDateTime current_date_time =QDateTime::currentDateTime();
                current_date +=current_date_time.toString("hh:mm:ss");
                current_date += "节点三pH过低" ;
                current_date += "\n";
                ui->textEdit3->setText(current_date);
                ui->textEdit3->moveCursor(QTextCursor::End); //移动到最后一行
            }
            else if (three::phx3 == 0)
            {
                ui->phlab3->setText("");
            }
            if (three::zdx3 == 1)
            {
                ui->zdlab3->setText("水质浑浊");
                QString current_date = ui->textEdit3->toPlainText();
                QDateTime current_date_time =QDateTime::currentDateTime();
                current_date +=current_date_time.toString("hh:mm:ss");
                current_date += "节点三水质浑浊" ;
                current_date += "\n";
                ui->textEdit3->setText(current_date);
                ui->textEdit3->moveCursor(QTextCursor::End); //移动到最后一行
            }

            else if (three::zdx3 == 0)
            {
                ui->zdlab3->setText("");
            }
            if (three::ddx3 == 1)
            {
                ui->ddlab3->setText("重金属含量高");
                QString current_date = ui->textEdit3->toPlainText();
                QDateTime current_date_time =QDateTime::currentDateTime();
                current_date +=current_date_time.toString("hh:mm:ss");
                current_date += "节点三重金属含量高" ;
                current_date += "\n";
                ui->textEdit3->setText(current_date);
                ui->textEdit3->moveCursor(QTextCursor::End); //移动到最后一行
            }

            else if (three::ddx3 == 0)
            {
                ui->ddlab3->setText("");
            }
            //qDebug() <<"收到节点一";
            //显示日志
            //操作 记录
            QString current_date = ui->textEdit3->toPlainText();
            QDateTime current_date_time =QDateTime::currentDateTime();
            current_date +=current_date_time.toString("hh:mm:ss");
            current_date += "收到节点三" ;
            current_date += "\n";
            ui->textEdit3->setText(current_date);
            ui->textEdit3->moveCursor(QTextCursor::End); //移动到最后一行
            ui->lcdNumber_31->display(tp3);
            ui->lcdNumber_32->display(ph3);
            ui->lcdNumber_33->display(zd3);
            ui->lcdNumber_34->display(dd3);
            ui->batteryBar1_3->setValue(pct3);//lcd  显示电量
            led(ui->LED_3,2,30);   //绿色
            //pub
            char mes[100];
            memset(mes,0,sizeof(mes));
            sprintf(mes,"{\"tp3\":%.1f,\"ph3\":%.1f,\"zd3\":%.1f,\"dd3\":%d,\"dc3\":%d}",tp3,ph3,zd3,dd3,pct3);
            message = mes;
            QMQTT::Message send_msg(136,m_strPubTopic,message.toLocal8Bit());
            if(str == true)
            {
               mqtt_client->publish(send_msg);
            }


        }
        else
        {

            //指示灯
            led(ui->LED_3,0,30);   //灰色
        }

    }
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0, width(),height(),QPixmap(":/321.jpg"));
}

//查找串口
void Widget::find_serialport()
{

    //查找可用串口
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);   //设置串口
        if(serial.open(QIODevice::ReadWrite))
        {
            ui->com->addItem(serial.portName());        //显示串口name
            serial.close();
        }
    }
}
//关闭串口
void Widget::on_close_serialport_clicked()
{
    //关闭串口
    ui->close_serialport->setEnabled(false);
    ui->open_serialport->setEnabled(true);
    ui->start_send->setEnabled(false);
    ui->close_send->setEnabled(false);
    serialport->clear();   //清空缓存区
    serialport->close();   //关闭串口
    //清空串口名字
    ui->com->clear();
    //on_pause_clicked();    //停止绘图

    // 操作记录
    QString current_date = ui->textEdit->toPlainText();
    QDateTime current_date_time =QDateTime::currentDateTime();   //获取当前时间
    current_date +=current_date_time.toString("yyyy.MM.dd hh:mm");
    current_date += " 关闭串口\r\n" ;

    ui->textEdit->setText(current_date);
    ui->textEdit->moveCursor(QTextCursor::End); //移动到最后一行

    //关闭所有信号灯
    led(ui->LED_1,0,30);   //灰色
    led(ui->LED_2,0,30);   //灰色
    led(ui->LED_3,0,30);   //灰色
     //关闭电池
    ui->batteryBar1->setValue(0);
    ui->batteryBar1_2->setValue(0);
    ui->batteryBar1_3->setValue(0);

    //显示日志
    //操作 记录
    QString current_date1 = ui->textEdit1->toPlainText();
    QDateTime current_date_time1 =QDateTime::currentDateTime();
    current_date1 +=current_date_time1.toString("hh:mm:ss");
    current_date1 += "关闭串口 停止接收设备一数据!" ;
    current_date1 += "\n";
    ui->textEdit1->setText(current_date1);
    ui->textEdit1->moveCursor(QTextCursor::End); //移动到最后一行

    //显示日志
    //操作 记录
    QString current_date2 = ui->textEdit2->toPlainText();
    QDateTime current_date_time2 =QDateTime::currentDateTime();
    current_date2 +=current_date_time2.toString("hh:mm:ss");
    current_date2 += "关闭串口 停止接收设备二数据!" ;
    current_date2+= "\n";
    ui->textEdit2->setText(current_date2);
    ui->textEdit2->moveCursor(QTextCursor::End); //移动到最后一行

    //显示日志
    //操作 记录
    QString current_date3 = ui->textEdit3->toPlainText();
    QDateTime current_date_time3 =QDateTime::currentDateTime();
    current_date3 +=current_date_time3.toString("hh:mm:ss");
    //current_date3 +='['+"关闭串口 停止接收设备三数据!"+']';
    current_date3 +="关闭串口 停止接收设备一数据" ;
    current_date3+= "\n";
    ui->textEdit3->setText(current_date3);
    ui->textEdit3->moveCursor(QTextCursor::End); //移动到最后一行

}
//刷新串口
void Widget::on_clear_serialport_clicked()
{
}

void Widget::doConnected()
{
    qDebug("连接成功");
    //绑定槽函数(槽函数的形参要和绑定的信号一样)
    connect(mqtt_client,SIGNAL(received(QMQTT::Message)),this,SLOT(doDataReceived(QMQTT::Message)));//接收到订阅的消息
    connect(mqtt_client,SIGNAL(disconnected()),this,SLOT(doDisconnected()));//断开连接
    connect(mqtt_client,SIGNAL(subscribed(QString,quint8)),this,SLOT(doSubscribed(QString,quint8)));//订阅成功
    connect(mqtt_client,SIGNAL(published(QMQTT::Message,quint16)),this,SLOT(doPublished(QMQTT::Message,quint16)));//发布成功
    mqtt_client->subscribe(m_strSubTopic);

}


void Widget::doDisconnected()
{
    QMessageBox::information(this,"提示","服务器断开");
    qDebug("断开连接");
}

void Widget::doPublished(QMQTT::Message, quint16)
{

    qDebug("发送消息");
}

void Widget::doSubscribed(QString, quint8)
{
    QMessageBox::information(this,"上传提示","正在上传");
    qDebug("订阅成功");
}

void Widget::doDataReceived(QMQTT::Message msg)
{
    QString data = msg.payload();
    qDebug()<<"===== received data:"<<data;
}

//开启子节点发送数据
void Widget::on_start_send_clicked()
{
    mqtt_client->connectToHost();
    ui->start_send->setEnabled(false);
    ui->close_send->setEnabled(true);
    str = true;
    auto arr3 = "999\r\n";
    serialport->write(arr3);
    QString current_date = ui->textEdit->toPlainText();
    QDateTime current_date_time =QDateTime::currentDateTime();
    current_date +=current_date_time.toString("yyyy.MM.dd hh:mm");
    current_date += " 数据上传云端" ;
    current_date += "\n";
    ui->textEdit->setText(current_date);
    ui->textEdit->moveCursor(QTextCursor::End); //移动到最后一行
}
//关闭子节点发送数据
void Widget::on_close_send_clicked()
{
    QMessageBox::information(this,"上传提示","停止上传");
    ui->start_send->setEnabled(true);
    ui->close_send->setEnabled(false);
    auto arr3 = "888\r\n";
    serialport->write(arr3);
    str = false;
    QString current_date = ui->textEdit->toPlainText();
    QDateTime current_date_time =QDateTime::currentDateTime();
    current_date +=current_date_time.toString("yyyy.MM.dd hh:mm");
    current_date += " 停止数据上传云端" ;
    current_date += "\n";
    ui->textEdit->setText(current_date);
    ui->textEdit->moveCursor(QTextCursor::End); //移动到最后一行
}
//清空日志
void Widget::on_pushButton_13_clicked()
{
    ui->textEdit->clear();
}


void Widget::on_sousuo_clicked()
{

    ui->close_serialport->setEnabled(false);
    ui->open_serialport->setEnabled(true);
    ui->start_send->setEnabled(false);
    ui->close_send->setEnabled(false);
    //清空串口名字
    ui->com->clear();
    //遍历串口信息
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
        ui->com->addItem(info.portName());
    // 操作记录
    QString current_date = ui->textEdit->toPlainText();
    QDateTime current_date_time =QDateTime::currentDateTime();   //获取当前时间
    current_date +=current_date_time.toString("yyyy.MM.dd hh:mm");
    current_date += " 刷新串口\r\n" ;
    ui->textEdit->setText(current_date);
    ui->textEdit->moveCursor(QTextCursor::End); //移动到最后一行
}

void Widget::on_pushButton_14_clicked()
{
    if (!oneWindow) {
        oneWindow = new one();
        oneWindow->setPreviousWidget(this); // 设置上一个窗口
    }
    this->hide();
    oneWindow->show();

}

void Widget::on_pushButton_15_clicked()
{
    if (!twoWindow) {
        twoWindow = new two();
        twoWindow->setPreviousWidget1(this); // 设置上一个窗口
    }
    this->hide();
    twoWindow->show();
}

void Widget::on_pushButton_16_clicked()
{
    if (!threeWindow) {
        threeWindow = new three();
        threeWindow->setPreviousWidget2(this); // 设置上一个窗口
    }
    this->hide();
    threeWindow->show();
}

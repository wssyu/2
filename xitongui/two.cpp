#include "two.h"
#include "ui_two.h"
#include "widget.h"

two::two(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::two)
{
    ui->setupUi(this);
    customPlot1 = ui->widget1;  //widget1页面  节点一
    customPlot2 = ui->widget2;  //widget1页面  节点一
    customPlot3 = ui->widget3;  //widget1页面  节点一
    customPlot4 = ui->widget4;  //widget1页面  节点一
    //绘图初始化
//////////////////////水温////////////////////////////////////////
    //添加曲线1 水温
    customPlot1->setBackground(Qt::transparent);
    customPlot1->axisRect()->setBackground(Qt::transparent);
    // 设置每个轴的背景为透明
    customPlot1->xAxis->setBasePen(QPen(Qt::transparent));
    customPlot1->yAxis->setBasePen(QPen(Qt::transparent));
    customPlot1->xAxis->setTickPen(QPen(Qt::transparent));
    customPlot1->yAxis->setTickPen(QPen(Qt::transparent));
    customPlot1->xAxis->setSubTickPen(QPen(Qt::transparent));
    customPlot1->yAxis->setSubTickPen(QPen(Qt::transparent));
    // 设置绘图图例背景为透明
    customPlot1->legend->setBrush(Qt::NoBrush);
    // 设置轴标签字体颜色
    QColor axisLabelColor(18, 150, 219);
    customPlot1->xAxis->setTickLabelColor(axisLabelColor); // 设置X轴标签字体颜色为黑色
    customPlot1->yAxis->setTickLabelColor(axisLabelColor); // 设置Y轴标签字体颜色为黑色
    // 设置轴标题字体颜色
    customPlot1->xAxis->setLabelColor(axisLabelColor); // 设置X轴标题字体颜色为黑色
    customPlot1->yAxis->setLabelColor(axisLabelColor); // 设置Y轴标题字体颜色为黑色
    // 设置图例字体颜色
    QFont legendFont = font();
    legendFont.setPointSize(10); // 设置图例字体大小
    customPlot1->legend->setFont(legendFont);
    customPlot1->legend->setTextColor(axisLabelColor); // 设置图例字体颜色为黑色

    QCPScatterStyle scatterStyle;
    customPlot1->addGraph();  // 增加图层
    customPlot1->graph(0)->setAntialiasedFill(false);  // 设置图层反锯齿：关闭
    customPlot1->graph(0)->setPen(QPen(Qt::blue,1));   // 设置笔的颜色  3是指线条宽度
    scatterStyle.setShape(QCPScatterStyle::ssDisc); // 设置点的形状为圆盘
    scatterStyle.setSize(3); // 设置点的大小为10像素
    customPlot1->graph(0)->setScatterStyle(scatterStyle);
    //添加曲线2 ph
    customPlot1->addGraph();  // 增加图层
    customPlot1->graph(1)->setAntialiasedFill(false);  // 设置图层反锯齿：关闭
    customPlot1->graph(1)->setPen(QPen(Qt::green,1));   // 设置笔的颜色
    scatterStyle.setShape(QCPScatterStyle::ssDisc); // 设置点的形状为圆盘
    scatterStyle.setSize(3); // 设置点的大小为10像素
    customPlot1->graph(1)->setScatterStyle(scatterStyle);
    //添加曲线3 浊度
    customPlot1->addGraph();  // 增加图层
    customPlot1->graph(2)->setAntialiasedFill(false);  // 设置图层反锯齿：关闭
    customPlot1->graph(2)->setPen(QPen(Qt::red,1));   // 设置笔的颜色
    scatterStyle.setShape(QCPScatterStyle::ssDisc); // 设置点的形状为圆盘
    scatterStyle.setSize(3); // 设置点的大小为10像素
    customPlot1->graph(2)->setScatterStyle(scatterStyle);
    //设置曲线1图例
    customPlot1->graph(0)->setName("节点一");
    customPlot1->graph(0)->setPen(QPen(Qt::blue,1));
    //设置曲线2图例
    customPlot1->graph(1)->setName("节点二");
    customPlot1->graph(1)->setPen(QPen(Qt::green,1));
    //设置曲线3图例
    customPlot1->graph(2)->setName("节点三");
    customPlot1->graph(2)->setPen(QPen(Qt::red,1));
    customPlot1->xAxis->setLabel("时间(单位s)");         // 设置横轴标签
    customPlot1->yAxis->setRange(-10,50);       //设置温度范围
    customPlot1->xAxis->setLabel("时间");
    customPlot1->yAxis->setLabel("水温(℃))");
//////////////////////水温////////////////////////////////////////
//////////////////////pH值////////////////////////////////////////
        //添加曲线1 水温
        customPlot2->setBackground(Qt::transparent);
        customPlot2->axisRect()->setBackground(Qt::transparent);
        // 设置每个轴的背景为透明
        customPlot2->xAxis->setBasePen(QPen(Qt::transparent));
        customPlot2->yAxis->setBasePen(QPen(Qt::transparent));
        customPlot2->xAxis->setTickPen(QPen(Qt::transparent));
        customPlot2->yAxis->setTickPen(QPen(Qt::transparent));
        customPlot2->xAxis->setSubTickPen(QPen(Qt::transparent));
        customPlot2->yAxis->setSubTickPen(QPen(Qt::transparent));
        // 设置绘图图例背景为透明
        customPlot2->legend->setBrush(Qt::NoBrush);
        // 设置轴标签字体颜色
        QColor axisLabelColor1(26, 250, 41);
        customPlot2->xAxis->setTickLabelColor(axisLabelColor1); // 设置X轴标签字体颜色为黑色
        customPlot2->yAxis->setTickLabelColor(axisLabelColor1); // 设置Y轴标签字体颜色为黑色
        // 设置轴标题字体颜色
        customPlot2->xAxis->setLabelColor(axisLabelColor1); // 设置X轴标题字体颜色为黑色
        customPlot2->yAxis->setLabelColor(axisLabelColor1); // 设置Y轴标题字体颜色为黑色
        // 设置图例字体颜色
        QFont legendFont1 = font();
        legendFont.setPointSize(10); // 设置图例字体大小
        customPlot2->legend->setFont(legendFont1);
        customPlot2->legend->setTextColor(axisLabelColor1); // 设置图例字体颜色为黑色

        customPlot2->addGraph();  // 增加图层
        customPlot2->graph(0)->setAntialiasedFill(false);  // 设置图层反锯齿：关闭
        customPlot2->graph(0)->setPen(QPen(Qt::blue,1));   // 设置笔的颜色  3是指线条宽度
        scatterStyle.setShape(QCPScatterStyle::ssDisc); // 设置点的形状为圆盘
        scatterStyle.setSize(3); // 设置点的大小为10像素
        customPlot2->graph(0)->setScatterStyle(scatterStyle);
        //添加曲线2 ph
        customPlot2->addGraph();  // 增加图层
        customPlot2->graph(1)->setAntialiasedFill(false);  // 设置图层反锯齿：关闭
        customPlot2->graph(1)->setPen(QPen(Qt::green,1));   // 设置笔的颜色
        scatterStyle.setShape(QCPScatterStyle::ssDisc); // 设置点的形状为圆盘
        scatterStyle.setSize(3); // 设置点的大小为10像素
        customPlot2->graph(1)->setScatterStyle(scatterStyle);
        //添加曲线3 浊度
        customPlot2->addGraph();  // 增加图层
        customPlot2->graph(2)->setAntialiasedFill(false);  // 设置图层反锯齿：关闭
        customPlot2->graph(2)->setPen(QPen(Qt::red,1));   // 设置笔的颜色
        scatterStyle.setShape(QCPScatterStyle::ssDisc); // 设置点的形状为圆盘
        scatterStyle.setSize(3); // 设置点的大小为10像素
        customPlot2->graph(2)->setScatterStyle(scatterStyle);
        //设置曲线1图例
        customPlot2->graph(0)->setName("节点一");
        customPlot2->graph(0)->setPen(QPen(Qt::blue,1));
        //设置曲线2图例
        customPlot2->graph(1)->setName("节点二");
        customPlot2->graph(1)->setPen(QPen(Qt::green,1));
        //设置曲线3图例
        customPlot2->graph(2)->setName("节点三");
        customPlot2->graph(2)->setPen(QPen(Qt::red,1));
        customPlot2->xAxis->setLabel("时间(单位s)");         // 设置横轴标签
        customPlot2->yAxis->setRange(0,14);       //设置温度范围
        customPlot2->xAxis->setLabel("时间");
        customPlot2->yAxis->setLabel("pH值");
//////////////////////pH值////////////////////////////////////////
/// //////////////////////pH值////////////////////////////////////////
        //添加曲线1 水温
        customPlot3->setBackground(Qt::transparent);
        customPlot3->axisRect()->setBackground(Qt::transparent);
        // 设置每个轴的背景为透明
        customPlot3->xAxis->setBasePen(QPen(Qt::transparent));
        customPlot3->yAxis->setBasePen(QPen(Qt::transparent));
        customPlot3->xAxis->setTickPen(QPen(Qt::transparent));
        customPlot3->yAxis->setTickPen(QPen(Qt::transparent));
        customPlot3->xAxis->setSubTickPen(QPen(Qt::transparent));
        customPlot3->yAxis->setSubTickPen(QPen(Qt::transparent));
        // 设置绘图图例背景为透明
        customPlot3->legend->setBrush(Qt::NoBrush);

        // 设置轴标签字体颜色
        QColor axisLabelColor2(244, 234, 42);
        customPlot3->xAxis->setTickLabelColor(axisLabelColor2); // 设置X轴标签字体颜色为黑色
        customPlot3->yAxis->setTickLabelColor(axisLabelColor2); // 设置Y轴标签字体颜色为黑色
        // 设置轴标题字体颜色
        customPlot3->xAxis->setLabelColor(axisLabelColor2); // 设置X轴标题字体颜色为黑色
        customPlot3->yAxis->setLabelColor(axisLabelColor2); // 设置Y轴标题字体颜色为黑色
        // 设置图例字体颜色
        QFont legendFont2 = font();
        legendFont.setPointSize(8); // 设置图例字体大小
        customPlot3->legend->setFont(legendFont2);
        customPlot3->legend->setTextColor(axisLabelColor2); // 设置图例字体颜色为黑色

        customPlot3->addGraph();  // 增加图层
        customPlot3->graph(0)->setAntialiasedFill(false);  // 设置图层反锯齿：关闭
        customPlot3->graph(0)->setPen(QPen(Qt::blue,1));   // 设置笔的颜色  3是指线条宽度
        scatterStyle.setShape(QCPScatterStyle::ssDisc); // 设置点的形状为圆盘
        scatterStyle.setSize(3); // 设置点的大小为10像素
        customPlot3->graph(0)->setScatterStyle(scatterStyle);
        //添加曲线2 ph
        customPlot3->addGraph();  // 增加图层
        customPlot3->graph(1)->setAntialiasedFill(false);  // 设置图层反锯齿：关闭
        customPlot3->graph(1)->setPen(QPen(Qt::green,1));   // 设置笔的颜色
        scatterStyle.setShape(QCPScatterStyle::ssDisc); // 设置点的形状为圆盘
        scatterStyle.setSize(3); // 设置点的大小为10像素
        customPlot3->graph(1)->setScatterStyle(scatterStyle);
        //添加曲线3 浊度
        customPlot3->addGraph();  // 增加图层
        customPlot3->graph(2)->setAntialiasedFill(false);  // 设置图层反锯齿：关闭
        customPlot3->graph(2)->setPen(QPen(Qt::red,1));   // 设置笔的颜色
        scatterStyle.setShape(QCPScatterStyle::ssDisc); // 设置点的形状为圆盘
        scatterStyle.setSize(3); // 设置点的大小为10像素
        customPlot3->graph(2)->setScatterStyle(scatterStyle);
        //设置曲线1图例
        customPlot3->graph(0)->setName("节点一");
        customPlot3->graph(0)->setPen(QPen(Qt::blue,1));
        //设置曲线2图例
        customPlot3->graph(1)->setName("节点二");
        customPlot3->graph(1)->setPen(QPen(Qt::green,1));
        //设置曲线3图例
        customPlot3->graph(2)->setName("节点三");
        customPlot3->graph(2)->setPen(QPen(Qt::red,1));
        customPlot3->xAxis->setLabel("时间(单位s)");         // 设置横轴标签
        customPlot3->yAxis->setRange(0,50);       //设置温度范围
        customPlot3->xAxis->setLabel("时间");
        customPlot3->yAxis->setLabel("浊度(NTU)");
//////////////////////pH值////////////////////////////////////////
/// //////////////////////pH值////////////////////////////////////////
        //添加曲线1 水温
        customPlot4->setBackground(Qt::transparent);
        customPlot4->axisRect()->setBackground(Qt::transparent);
        // 设置每个轴的背景为透明
        customPlot4->xAxis->setBasePen(QPen(Qt::transparent));
        customPlot4->yAxis->setBasePen(QPen(Qt::transparent));
        customPlot4->xAxis->setTickPen(QPen(Qt::transparent));
        customPlot4->yAxis->setTickPen(QPen(Qt::transparent));
        customPlot4->xAxis->setSubTickPen(QPen(Qt::transparent));
        customPlot4->yAxis->setSubTickPen(QPen(Qt::transparent));
        // 设置绘图图例背景为透明
        customPlot4->legend->setBrush(Qt::NoBrush);
        // 设置轴标签字体颜色
        QColor axisLabelColor3(239, 41, 41);
        customPlot4->xAxis->setTickLabelColor(axisLabelColor3); // 设置X轴标签字体颜色为黑色
        customPlot4->yAxis->setTickLabelColor(axisLabelColor3); // 设置Y轴标签字体颜色为黑色
        // 设置轴标题字体颜色
        customPlot4->xAxis->setLabelColor(axisLabelColor3); // 设置X轴标题字体颜色为黑色
        customPlot4->yAxis->setLabelColor(axisLabelColor3); // 设置Y轴标题字体颜色为黑色
        // 设置图例字体颜色
        QFont legendFont3 = font();
        legendFont.setPointSize(6); // 设置图例字体大小
        customPlot4->legend->setFont(legendFont3);
        customPlot4->legend->setTextColor(axisLabelColor3); // 设置图例字体颜色为黑色


        customPlot4->addGraph();  // 增加图层
        customPlot4->graph(0)->setAntialiasedFill(false);  // 设置图层反锯齿：关闭
        customPlot4->graph(0)->setPen(QPen(Qt::blue,1));   // 设置笔的颜色  3是指线条宽度
        //customPlot4->graph(0)->setScatterStyle(QCPScatterStyle::ssDisc);   // 设置点的形状
        scatterStyle.setShape(QCPScatterStyle::ssDisc); // 设置点的形状为圆盘
        scatterStyle.setSize(3); // 设置点的大小为10像素
        customPlot4->graph(0)->setScatterStyle(scatterStyle);


        //添加曲线2 ph
        customPlot4->addGraph();  // 增加图层
        customPlot4->graph(1)->setAntialiasedFill(false);  // 设置图层反锯齿：关闭
        customPlot4->graph(1)->setPen(QPen(Qt::green,1));   // 设置笔的颜色
        scatterStyle.setShape(QCPScatterStyle::ssDisc); // 设置点的形状为圆盘
        scatterStyle.setSize(3); // 设置点的大小为10像素
        customPlot4->graph(1)->setScatterStyle(scatterStyle);


        //添加曲线3 浊度
        customPlot4->addGraph();  // 增加图层
        customPlot4->graph(2)->setAntialiasedFill(false);  // 设置图层反锯齿：关闭
        customPlot4->graph(2)->setPen(QPen(Qt::red,1));   // 设置笔的颜色
        customPlot4->graph(2)->setScatterStyle(QCPScatterStyle::ssDisc);   // 设置点的形状
        scatterStyle.setShape(QCPScatterStyle::ssDisc); // 设置点的形状为圆盘
        scatterStyle.setSize(3); // 设置点的大小为10像素
        customPlot4->graph(2)->setScatterStyle(scatterStyle);


        //设置曲线1图例
        customPlot4->graph(0)->setName("节点一");
        customPlot4->graph(0)->setPen(QPen(Qt::blue,1));
        //设置曲线2图例
        customPlot4->graph(1)->setName("节点二");
        customPlot4->graph(1)->setPen(QPen(Qt::green,1));
        //设置曲线3图例
        customPlot4->graph(2)->setName("节点三");
        customPlot4->graph(2)->setPen(QPen(Qt::red,1));
        customPlot4->xAxis->setLabel("时间(单位s)");         // 设置横轴标签
        customPlot4->yAxis->setRange(0,5000);       //设置温度范围
        customPlot4->xAxis->setLabel("时间");
        customPlot4->yAxis->setLabel("电导率(us/cm)");
//////////////////////电导率////////////////////////////////////////


    _pTimerUpdate = new QTimer(this);
    dingshiqi = new QTimer(this);
    connect(_pTimerUpdate, SIGNAL(timeout()), this, SLOT(customsplot_init()));

}

two::~two()
{
    delete ui;
}


void two::customsplot_init()
{
    static QTime time(QTime::currentTime());        //获取当前时间
    //计算新的数据点
    double key = time.elapsed()/1000.0;
    static double lastPointKey = 0;
    if (key-lastPointKey > 0.002) //大于2ms添加一个数据
       {
           //水温
           customPlot1->graph(0)->addData(key,Widget::tp1);  //温度加到数据中,这个只有点，没有线
           customPlot1->graph(1)->addData(key,Widget::tp2);
           customPlot1->graph(2)->addData(key,Widget::tp3);
           //pH值
           customPlot2->graph(0)->addData(key,Widget::ph1);
           customPlot2->graph(1)->addData(key,Widget::ph2);
           customPlot2->graph(2)->addData(key,Widget::ph3);
           //浊度
           customPlot3->graph(0)->addData(key,Widget::zd1);
           customPlot3->graph(1)->addData(key,Widget::zd2);
           customPlot3->graph(2)->addData(key,Widget::zd3);
           //电导率
           customPlot4->graph(0)->addData(key,Widget::dd1);
           customPlot4->graph(1)->addData(key,Widget::dd2);
           customPlot4->graph(2)->addData(key,Widget::dd3);
           lastPointKey = key;
       }
      customPlot1->xAxis->setRange(key, 30, Qt::AlignRight);        //设置x轴范围
      customPlot1->legend->setVisible(true); //显示图例
      customPlot1->replot();       //画图
      customPlot2->xAxis->setRange(key, 30, Qt::AlignRight);        //设置x轴范围
      customPlot2->legend->setVisible(true); //显示图例
      customPlot2->replot();       //画图
      customPlot3->xAxis->setRange(key, 30, Qt::AlignRight);        //设置x轴范围
      customPlot3->legend->setVisible(true); //显示图例
      customPlot3->replot();       //画图
      customPlot4->xAxis->setRange(key, 30, Qt::AlignRight);        //设置x轴范围
      customPlot4->legend->setVisible(true); //显示图例
      customPlot4->replot();       //画图


}



void two::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0, width(),height(),QPixmap(":/321.jpg"));
}

void two::setPreviousWidget1(QWidget *widget)
{
    previousWidget = widget; // 设置前一个窗口
}

void two::on_fanhui_clicked()
{
    if (previousWidget) {
        previousWidget->show();
    }
    this->hide();
}

void two::on_fanhui_2_clicked()
{
    _pTimerUpdate->start(1000); //1s更新一次
}







void two::on_fanhui_3_clicked()
{
    _pTimerUpdate->stop();
}

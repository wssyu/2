#include "one.h"
#include "widget.h"
#include "ui_one.h"
#include "ui_widget.h"



one::one(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::one),
   previousWidget(nullptr) // 初始化指针为 nullptr
{

    ui->setupUi(this);
    ui->stop->setEnabled(false);
    Dir=QCoreApplication::applicationDirPath();
    // 实时更新槽函数
    _pTimerUpdate = new QTimer(this);
    dingshiqi = new QTimer(this);
    connect(_pTimerUpdate, SIGNAL(timeout()), this, SLOT(customsplot_init()));
    QStringList header;//设置表头
    header<<tr("时间")<<tr("水温")<<tr("pH值")<<tr("浊度")<<tr("电导率")<<tr("电量");
    ui->text1->setColumnCount(6);
    //ui->text1->setAlternatingRowColors(true);     //设置隔行变颜色
    ui->text1->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->text1->setHorizontalHeaderLabels(header); //可以将其设置为tableWidget控件的水平表头标签
//    ui->text1->setStyleSheet("QTableWidget { background-color: transparent; }"
//                               "QTableWidget::item { background-color: transparent; }"
//                               "QTableWidget::header { background-color: transparent; }");
    ui->text1->setColumnWidth(0,70); //设置第0列的宽度
    ui->text1->setColumnWidth(1,59); //设置第1列的宽度
    ui->text1->setColumnWidth(2,50); //设置第2列的宽度
    ui->text1->setColumnWidth(3,50); //设置第3列的宽度
    ui->text1->setColumnWidth(4,50); //设置第4列的宽度
    ui->text1->setColumnWidth(5,50); //设置第5列的宽度
    ui->text2->setColumnCount(6);
    //ui->text1->setAlternatingRowColors(true);     //设置隔行变颜色
    ui->text2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->text2->setHorizontalHeaderLabels(header); //可以将其设置为tableWidget控件的水平表头标签
    //ui->text2->setStyleSheet("QTableWidget { background-color: transparent; }");
    ui->text2->setColumnWidth(0,70); //设置第0列的宽度
    ui->text2->setColumnWidth(1,59); //设置第1列的宽度
    ui->text2->setColumnWidth(2,50); //设置第2列的宽度
    ui->text2->setColumnWidth(3,50); //设置第3列的宽度
    ui->text2->setColumnWidth(4,50); //设置第4列的宽度
    ui->text2->setColumnWidth(5,50); //设置第5列的宽度
    ui->text3->setColumnCount(6);
    //ui->text1->setAlternatingRowColors(true);     //设置隔行变颜色
    ui->text3->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->text3->setHorizontalHeaderLabels(header); //可以将其设置为tableWidget控件的水平表头标签
    //ui->text3->setStyleSheet("QTableWidget { background-color: transparent; }");
    ui->text3->setColumnWidth(0,70); //设置第0列的宽度
    ui->text3->setColumnWidth(1,59); //设置第1列的宽度
    ui->text3->setColumnWidth(2,50); //设置第2列的宽度
    ui->text3->setColumnWidth(3,50); //设置第3列的宽度
    ui->text3->setColumnWidth(4,50); //设置第4列的宽度
    ui->text3->setColumnWidth(5,50); //设置第5列的宽度
}

one::~one()
{
    delete ui;
}
void one::customsplot_init()
{
    static QTime time(QTime::currentTime());        //获取当前时间
    //计算新的数据点
    double key = time.elapsed()/1000.0;
    static double lastPointKey = 0;
    if (key-lastPointKey > 0.002) //大于2ms添加一个数据
    {
        lastPointKey = key;
        QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
        QString date = time.toString("hh:mm:ss"); //设置显示格式
       // QString date = time.toString("MM.dd hh:mm:ss"); //设置显示格式
        QString tp1,ph1,zd1,dd1,dc1;  //节点一
        QString tp2,ph2,zd2,dd2,dc2;
        QString tp3,ph3,zd3,dd3,dc3;
        tp1 = QString("%1").arg(Widget::tp1);
        ph1 = QString("%1").arg(Widget::ph1);
        zd1 = QString("%1").arg(Widget::zd1);
        dd1 = QString("%1").arg(Widget::dd1);
        dc1 = QString("%1").arg(Widget::pct1);
        tp2 = QString("%1").arg(Widget::tp2);
        ph2 = QString("%1").arg(Widget::ph2);
        zd2 = QString("%1").arg(Widget::zd2);
        dd2 = QString("%1").arg(Widget::dd2);
        dc2 = QString("%1").arg(Widget::pct2);
        tp3 = QString("%1").arg(Widget::tp3);
        ph3 = QString("%1").arg(Widget::ph3);
        zd3 = QString("%1").arg(Widget::zd3);
        dd3 = QString("%1").arg(Widget::dd3);
        dc3 = QString("%1").arg(Widget::pct3);
        insert_table1(date,tp1,ph1,zd1,dd1,dc1);
        insert_table2(date,tp2,ph2,zd2,dd2,dc2);
        insert_table3(date,tp3,ph3,zd3,dd3,dc3);
    }
}


void one::insert_table1(QString date, QString tp1, QString ph1, QString zd1,QString dd1, QString dc1)
{
    update();
    int row_count = ui->text1->rowCount();   //获取总行数
    ui->text1->insertRow(row_count);         //插入行
    QTableWidgetItem *item0 = new QTableWidgetItem();
    QTableWidgetItem *item1 = new QTableWidgetItem();
    QTableWidgetItem *item2 = new QTableWidgetItem();
    QTableWidgetItem *item3 = new QTableWidgetItem();
    QTableWidgetItem *item4 = new QTableWidgetItem();
    QTableWidgetItem *item5 = new QTableWidgetItem();
    item0->setText(date); //时间
    item1->setText(tp1);
    item2->setText(ph1);
    item3->setText(zd1);
    item4->setText(dd1);
    item5->setText(dc1);
    ui->text1->setItem(row_count,0,item0);
    ui->text1->setItem(row_count,1,item1);
    ui->text1->setItem(row_count,2,item2);
    ui->text1->setItem(row_count,3,item3);
    ui->text1->setItem(row_count,4,item4);
    ui->text1->setItem(row_count,5,item5);
}
void one::insert_table2(QString date, QString tp2, QString ph2, QString zd2,QString dd2, QString dc2)
{
    update();
    int row_count = ui->text2->rowCount();   //获取总行数
    ui->text2->insertRow(row_count);         //插入行
    QTableWidgetItem *item0 = new QTableWidgetItem();
    QTableWidgetItem *item1 = new QTableWidgetItem();
    QTableWidgetItem *item2 = new QTableWidgetItem();
    QTableWidgetItem *item3 = new QTableWidgetItem();
    QTableWidgetItem *item4 = new QTableWidgetItem();
    QTableWidgetItem *item5 = new QTableWidgetItem();
    item0->setText(date); //时间
    item1->setText(tp2);
    item2->setText(ph2);
    item3->setText(zd2);
    item4->setText(dd2);
    item5->setText(dc2);
    ui->text2->setItem(row_count,0,item0);
    ui->text2->setItem(row_count,1,item1);
    ui->text2->setItem(row_count,2,item2);
    ui->text2->setItem(row_count,3,item3);
    ui->text2->setItem(row_count,4,item4);
    ui->text2->setItem(row_count,5,item5);
}
void one::insert_table3(QString date, QString tp3, QString ph3, QString zd3,QString dd3, QString dc3)
{
    update();
    int row_count = ui->text3->rowCount();   //获取总行数
    ui->text3->insertRow(row_count);         //插入行
    QTableWidgetItem *item0 = new QTableWidgetItem();
    QTableWidgetItem *item1 = new QTableWidgetItem();
    QTableWidgetItem *item2 = new QTableWidgetItem();
    QTableWidgetItem *item3 = new QTableWidgetItem();
    QTableWidgetItem *item4 = new QTableWidgetItem();
    QTableWidgetItem *item5 = new QTableWidgetItem();
    item0->setText(date); //时间
    item1->setText(tp3);
    item2->setText(ph3);
    item3->setText(zd3);
    item4->setText(dd3);
    item5->setText(dc3);
    ui->text3->setItem(row_count,0,item0);
    ui->text3->setItem(row_count,1,item1);
    ui->text3->setItem(row_count,2,item2);
    ui->text3->setItem(row_count,3,item3);
    ui->text3->setItem(row_count,4,item4);
    ui->text3->setItem(row_count,5,item5);
}












void one::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0, width(),height(),QPixmap(":/321.jpg"));
}

void one::setPreviousWidget(QWidget *widget)
{
    previousWidget = widget; // 设置前一个窗口
}

void one::on_pushButton_clicked()
{
    if (previousWidget) {
        previousWidget->show();
    }
    this->hide();
}

void one::on_xieru_clicked()
{
    ui->stop->setEnabled(true);
    _pTimerUpdate->start(1000); //1s更新一次
}

void one::on_stop_clicked()
{

    _pTimerUpdate->stop();
}

void one::on_qc_clicked()
{
    while(ui->text1->rowCount())
    {
        ui->text1->removeRow(0);
    }
}

void one::on_qc_2_clicked()
{
    while(ui->text2->rowCount())
    {
        ui->text2->removeRow(0);
    }
}

void one::on_qc_3_clicked()
{
    while(ui->text3->rowCount())
    {
        ui->text3->removeRow(0);
    }
}

void one::on_save_clicked()
{
    // 获取文件目录
    QString filename = Dir+"/";
    //文件名
    QDateTime time = QDateTime::currentDateTime();  //获取系统现在时间
    QString date = time.toString("MM.dd"); //设置显示格式
    filename += date;
    filename += "节点一.txt";
    //文件对象
    QFile file(filename);
    //只写方式打开
    if(!file.open(QFile::WriteOnly | QFile::Text))      //只写方式
    {
        QMessageBox::warning(this,tr("double file edit"),tr("no write ").arg(filename).arg(file.errorString()));
        return ;
    }
    //文件流对象
    QTextStream out(&file);
    //遍历数据
    int romcount = ui->text1->rowCount();     //获取总行数
    QString title;
    title +="  时间      水温(℃)     pH值  浊度(NTU)  电导率(uS/cm) 电量(%)  节点一\n";
    out << title;
    for(int i = 0; i < romcount; i++)
    {
        QString rowstring;
        for(int j = 0; j < 6; j++)
        {
            rowstring += ui->text1->item(i,j)->text();
            rowstring += "       ";
        }
        rowstring += "\n";
        out << rowstring;
    }

    file.close();
    QMessageBox::information(this, tr("节点一保存成功"), tr("路径：%1").arg(filename));
}

void one::on_save_2_clicked()
{
    // 获取文件目录
    QString filename = Dir+"/";
    //文件名
    QDateTime time = QDateTime::currentDateTime();  //获取系统现在时间
    QString date = time.toString("MM.dd"); //设置显示格式
    filename += date;
    filename += "节点二.txt";
    //文件对象
    QFile file(filename);
    //只写方式打开
    if(!file.open(QFile::WriteOnly | QFile::Text))      //只写方式
    {
        QMessageBox::warning(this,tr("double file edit"),tr("no write ").arg(filename).arg(file.errorString()));
        return ;
    }
    //文件流对象
    QTextStream out(&file);
    //遍历数据
    int romcount = ui->text2->rowCount();     //获取总行数
    QString title;
    title +="  时间      水温(℃)     pH值  浊度(NTU)  电导率(uS/cm) 电量(%)  节点二\n";
    out << title;
    for(int i = 0; i < romcount; i++)
    {
        QString rowstring;
        for(int j = 0; j < 6; j++)
        {
            rowstring += ui->text2->item(i,j)->text();
            rowstring += "       ";
        }
        rowstring += "\n";
        out << rowstring;
    }

    file.close();
    QMessageBox::information(this, tr("节点二保存成功"), tr("路径：%1").arg(filename));
}



void one::on_save_3_clicked()
{
    // 获取文件目录
    QString filename = Dir+"/";
    //文件名
    QDateTime time = QDateTime::currentDateTime();  //获取系统现在时间
    QString date = time.toString("MM.dd"); //设置显示格式
    filename += date;
    filename += "节点三.txt";
    //文件对象
    QFile file(filename);
    //只写方式打开
    if(!file.open(QFile::WriteOnly | QFile::Text))      //只写方式
    {
        QMessageBox::warning(this,tr("double file edit"),tr("no write ").arg(filename).arg(file.errorString()));
        return ;
    }
    //文件流对象
    QTextStream out(&file);
    //遍历数据
    int romcount = ui->text3->rowCount();     //获取总行数
    QString title;
    title +="  时间      水温(℃)     pH值  浊度(NTU)  电导率(uS/cm) 电量(%)  节点三\n";
    out << title;
    for(int i = 0; i < romcount; i++)
    {
        QString rowstring;
        for(int j = 0; j < 6; j++)
        {
            rowstring += ui->text3->item(i,j)->text();
            rowstring += "       ";
        }
        rowstring += "\n";
        out << rowstring;
    }

    file.close();
    QMessageBox::information(this, tr("节点三保存成功"), tr("路径：%1").arg(filename));

}

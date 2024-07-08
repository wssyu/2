#ifndef JIEDIAN1_H
#define JIEDIAN1_H
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class yi;
}
QT_END_NAMESPACE

class yi : public QWidget
{
    Q_OBJECT
public:
     yi(QWidget *parent = nullptr);
    ~yi();



private:
     Ui::yi *ui;



};





#endif // JIEDIAN1_H

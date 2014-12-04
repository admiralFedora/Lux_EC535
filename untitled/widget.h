#ifndef WIDGET_H
#define WIDGET_H

#include "adjusters.h"
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <controls.h>  // added by Ted

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void setParameter(); // added by Ted

private:
    QVBoxLayout *overAll;
    QHBoxLayout *boxBox;
    Adjusters *iso;
    Adjusters *shutter;
    Adjusters *aperture;
    Adjusters *exposure;
    Ui::Widget *ui;
    controls *motor_control; // added by Ted
};

#endif // WIDGET_H

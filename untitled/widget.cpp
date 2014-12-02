#include "widget.h"
#include "ui_widget.h"
#include <QIcon>
#include <QPixmap>
#include "adjusters.h"
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    iso = new Adjusters("iso");
    shutter = new Adjusters("shutter");
    aperture = new Adjusters("aperture");
    exposure = new Adjusters("exposure");
    overAll = new QVBoxLayout(this);
    boxBox = new QHBoxLayout();
    boxBox->addLayout(iso);
    boxBox->addLayout(shutter);
    boxBox->addLayout(aperture);
    boxBox->addLayout(exposure);
    overAll->addLayout(boxBox);
    overAll->setSpacing(10);
    this->setStyleSheet("background-color: white;");
}

Widget::~Widget()
{
    delete ui;
}

#ifndef ADJUSTERS_H
#define ADJUSTERS_H

#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QString>
#include <list>


class Adjusters : public QVBoxLayout
{
    Q_OBJECT

public:
    double current;
    QString whoami;
    Adjusters(QString text, int pFile); // changed by Ted
    ~Adjusters();

private:
    QPushButton *top;
    QPushButton *bottom;
    QLabel *text;
    std::list<double> values;
    std::list<double>::iterator pos;


    void initValues(QString text);
    void setTimer(); // added by Ted
private slots:
    void handleUp();
    void handleDown();
};

#endif // ADJUSTERS_H

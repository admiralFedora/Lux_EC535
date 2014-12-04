#include "widget.h"
#include "ui_widget.h"
#include <QIcon>
#include <QPixmap>
#include "adjusters.h"
// added by Ted
#include <cstdio>
#include <unistd.h>
#include <cstdlib>
#include <signal.h>
#include <fcntl.h>
#include <string.h>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    //added by Ted
	pFile = open("/dev/fasync_timer", O_RDWR);
	if (pFile < 0) {
		fprintf (stderr, "fasync_timer module isn't loaded\n");
	}
	// stop adding
	
    ui->setupUi(this);
    iso = new Adjusters("iso",pFile);           // changed by Ted
    shutter = new Adjusters("shutter",pFile);   // changed by Ted
    aperture = new Adjusters("aperture",pFile); // changed by Ted
    exposure = new Adjusters("exposure",pFile); // changed by Ted
    overAll = new QVBoxLayout(this);
    boxBox = new QHBoxLayout();
    boxBox->addLayout(iso);
    boxBox->addLayout(shutter);
    boxBox->addLayout(aperture);
    boxBox->addLayout(exposure);
    overAll->addLayout(boxBox);
    overAll->setSpacing(10);
    this->setStyleSheet("background-color: white;");
    
    
    // Setup signal handler
	memset(&action, 0, sizeof(action));
	action.sa_handler = setParameter;
	action.sa_flags = SA_SIGINFO;
	sigemptyset(&action.sa_mask);
	sigaction(SIGIO, &action, NULL);
	fcntl(pFile, F_SETOWN, getpid());
	oflags = fcntl(pFile, F_GETFL);
	fcntl(pFile, F_SETFL, oflags | FASYNC);
	
	// connect signal and slot
	connect(this->iso->top,SIGNAL(released()),this,SLOT(setTimer()));
	connect(this->iso->bottom,SIGNAL(released()),this,SLOT(setTimer()));
	connect(this->aperture->top,SIGNAL(released()),this,SLOT(setTimer()));
	connect(this->aperture->bottom,SIGNAL(released()),this,SLOT(setTimer()));
	connect(this->shutter->top,SIGNAL(released()),this,SLOT(setTimer()));
	connect(this->shutter->bottom,SIGNAL(released()),this,SLOT(setTimer()));
	connect(this->exposure->top,SIGNAL(released()),this,SLOT(setTimer()));
	connect(this->exposure->bottom,SIGNAL(released()),this,SLOT(setTimer()));
	// stop adding
}

Widget::~Widget()
{
    delete ui;
}

// added by Ted
void Widget::setParameter(int signo)
{
    // read lux reading from /proc/fortune
    FILE * pFile = fopen("/proc/fortune", "r");
    char content[10] = {0};
    int lux;
    fread(line,10,1,pFile);
    sscanf(line,"%d",&lux);
    fclose(pFile);
    // motor control
    motor_control->calculate(iso->current, 
                            aperture->current,
                            shutter->current,
                            exposure->current,
                            lux);
    
}

void Widget::setTimer(){
	write(pFile,"nothing",8);
}

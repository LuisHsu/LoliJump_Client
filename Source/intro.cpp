#include "intro.h"
#include "ui_intro.h"

#define LOADTIME 5000

Intro::Intro(MainWindow *main) :
	ui(new Ui::Intro)
{
	Main=main;
	ui->setupUi(this);
	elapse=0;
	LoadTime=new QTimer(this);
	LoadTime->start(1);
	QObject::connect(LoadTime,SIGNAL(timeout()),this,SLOT(Loaded()));

}

Intro::~Intro()
{
	delete LoadTime;
	delete ui;
}

void Intro::Loaded(){
	if(elapse<5000){
		elapse+=1;
		ui->progressBar->setValue(ui->progressBar->value()+1);
	}else{
		Main->show();
		delete this;
	}
	switch(elapse){
		case 2000:
			ui->label_2->setText("Loading Network Module......");
		break;
		case 2500:
			ui->label_2->setText("Setting platforms......");
		break;
		case 4500:
			ui->label_2->setText("Initializing......");
		break;
	}
}

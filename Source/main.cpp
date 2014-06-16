#include "mainwindow.h"
#include "intro.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	MainWindow w;
	Intro *i=new Intro(&w);
	i->setWindowFlags(Qt::FramelessWindowHint);
	i->show();

	return a.exec();
}

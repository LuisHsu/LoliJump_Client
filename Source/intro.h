#ifndef INTRO_H
#define INTRO_H

#include <QWidget>
#include <QTimer>
#include "mainwindow.h"

namespace Ui {
	class Intro;
}

class Intro : public QWidget
{
		Q_OBJECT

	public:
		explicit Intro(MainWindow *main);
		~Intro();

	private:
		Ui::Intro *ui;
		QTimer *LoadTime;
		MainWindow *Main;
		int elapse;
	private slots:
		void Loaded();
};

#endif // INTRO_H

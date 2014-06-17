#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QMovie>
#include <fstream>
#include "hp_bar.h"
#include "game.h"

#define MAXHP 15

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
		Q_OBJECT

	public:
		//Constructor
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();

	protected:
		void paintEvent(QPaintEvent *);
		void keyPressEvent(QKeyEvent *);
		void keyReleaseEvent(QKeyEvent *);

	public slots:
		void ChangeRecord(int);
		void ChangeFloor(int);
		void ChangeTime(int);
		void ChangePlatform(int);
		void ChangeHP(int);
		void ChangeStartButton(int);
		void CharacterPixChange(QMovie *);
		void MoveCharacter(int,int);

	private slots:
		void on_ClearButton_clicked();

	private:
		//Objects
		Ui::MainWindow *ui;
		Game *game;
		QLabel *Character;
		QMovie *ChtrPix;
		hp_bar *HpBar;

		//Record
		int record;
		void LoadRecord();
		void SaveRecord();
};

#endif // MAINWINDOW_H

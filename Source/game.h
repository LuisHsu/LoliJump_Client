#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QLabel>
#include <QTimer>
#include <QList>
#include <QtGlobal>
#include <QPainter>
#include <QDateTime>
#include <QMainWindow>

#include "hp_bar.h"
#include "normal_platform.h"
#include "laser_platform.h"
#include "temporary_platform.h"
#include "left_platform.h"
#include "right_platform.h"
#include "spring_platform.h"
#include "character.h"
#include "leaderboard.h"

#define INIT_ELAPSED 2
#define Maxinum_Speed 1
#define FloorDistance 500

class Game : public QObject
{
		Q_OBJECT
	public:
		explicit Game(QWidget *parent, hp_bar *Bar);
		~Game();
		Character *Lolita;
		void Paint(QPainter &p);

	signals:
		void RecordChange(int);
		void FloorChange(int);
		void TimeChange(int);
		void PlatformChange(int);
		void HPChange(int);
		void StartButtonImage(int);
		void PlatformUp();

	public slots:
		void StartButtonClicked();
		void Die();
		void SecTimeOut();
		void RemovePlatform(int, bool ClrPtr);
		void MilliTimeOut();

	private:
		QWidget *Parent;
		QTimer *SecTimer,*MilliTimer,*PaintTimer;
		int RecentTime,RecentElapsed,CountElapsed,CountAccelerate;
		int CountGenerate;
		int FloorCount,Floor;
		bool Started,Paused;
		QList<platform *> Platform_List;
		hp_bar *bar;

		Leaderboard *Leader_window;

		void GeneratePlatform(int type=-1, int X=0, int Y=0);
		void InitializeGame();
};

#endif // GAME_H

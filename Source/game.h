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
#include <QtMultimedia/qmediaplayer.h>
#include <QtMultimedia/qmediaplaylist.h>

#include "hp_bar.h"
#include "normal_platform.h"
#include "laser_platform.h"
#include "temporary_platform.h"
#include "left_platform.h"
#include "right_platform.h"
#include "spring_platform.h"
#include "character.h"
#include "leaderboard.h"

#define INIT_ELAPSED 7
#define Maxinum_Speed 5
#define FloorDistance 800
#define MaxinumFloorDist 177
#define GenerateAccele 14
#define Init_Gap 71
#define AcceleGap 10

class Game : public QObject
{
		Q_OBJECT
	public:
		explicit Game(QWidget *parent, hp_bar *Bar, QString pat, QMediaPlayer *bgm);
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
		int CountGenerate,GenerateGap;
		int FloorCount,Floor;
		bool Started,Paused;
		QList<platform *> Platform_List;
		hp_bar *bar;
		QString path;
		QMediaPlayer *BGM;

		Leaderboard *Leader_window;

		void GeneratePlatform(int type=-1, int X=0, int Y=0);
		void InitializeGame();
};

#endif // GAME_H

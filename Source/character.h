#ifndef CHARACTER_H
#define CHARACTER_H

#include <QObject>
#include <QLabel>
#include <QPixmap>
#include <QTimer>

#define MoveSpeed 2
#define LR_Speed 1
#define TimerTick 10
#define Gravity 0.07
#define JumpHeight 2

class Character : public QObject
{
		Q_OBJECT
	public:
		explicit Character(QWidget *parent = 0);
		~Character();

		void initialize();
		int getPlatform();
	signals:
		void CharacterPix(QPixmap *);
		void CharacterMove(int,int);
		void Fall();
		void MoveDown(int,int);
		void HpChange(int);
		void PlatformChange(int);

	public slots:
		void LeftPress(bool);
		void RightPress(bool);
		void MoveCharacter();
		void StartCharacter();
		void StopCharacter();
		void Hited(int,int);
		void TempOut();

	private:
		int x,y,t_y,s_y,pla;
		double Vertical;
		bool L_press,R_press;
		bool Hurted,Healed;
		bool TempTimeOut,TempTimeStarted;

		void NormalTouched(int);
		void LaserTouched(int);
		void TempTouched(int);
		void LeftTouched(int);
		void RightTouched(int);
		void SpringTouched(int);

		QPixmap *Static_pixmap;
		QWidget *Parent;
		QTimer *ChtrTimer,*TempTimer;
};

#endif // CHARACTER_H

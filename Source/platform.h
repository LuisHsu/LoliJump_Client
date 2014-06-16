#ifndef PLATFORM_H
#define PLATFORM_H

#include <QObject>
#include <QLabel>
#include <QtGlobal>
#include <QPainter>

#define PLATFORM_RAND -1
#define PLATFORM_NORMAL 0
#define PLATFORM_LASER 1
#define PLATFORM_TEMPORARY 2
#define PLATFORM_LEFT 3
#define PLATFORM_RIGHT 4
#define PLATFORM_SPRING 5

#define LOCATION_RAND 0

class platform : public QObject
{
		Q_OBJECT
	public:
		explicit platform(QWidget *parent, int index, int height,int type,int X,int Y);
		virtual ~platform();
		const int Type;
		virtual void PaintPlatform(QPainter &p)=0;
	signals:
		void ReachTop(int,bool);
		void Hitted(int,int);//y,type
	public slots:
		void MoveUp();//
		virtual void Checkhit(int,int)=0;
	protected:
		int x,y,Index,Height;
		QWidget *Parent;
};

#endif // PLATFORM_H

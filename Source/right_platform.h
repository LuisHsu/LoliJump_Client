#ifndef RIGHT_PLATFORM_H
#define RIGHT_PLATFORM_H

#include <QObject>
#include "platform.h"

class Right_platform : public platform
{
		Q_OBJECT
	public:
		explicit Right_platform(QWidget *parent, int index,int X=0,int Y=0);
		virtual void PaintPlatform(QPainter &p);
	signals:
		void Right_Hit(int);//

	public slots:
		void Checkhit(int,int);//
};

#endif // RIGHT_PLATFORM_H

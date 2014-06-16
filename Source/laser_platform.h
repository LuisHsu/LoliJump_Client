#ifndef LASER_PLATFORM_H
#define LASER_PLATFORM_H

#include <QObject>
#include "platform.h"

class Laser_platform : public platform
{
		Q_OBJECT
	public:
		explicit Laser_platform(QWidget *parent, int index, int X=0, int Y=0);
		virtual void PaintPlatform(QPainter &p);

	public slots:
		void Checkhit(int,int);//
};

#endif // LASER_PLATFORM_H

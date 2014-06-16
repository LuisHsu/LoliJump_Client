#ifndef SPRING_PLATFORM_H
#define SPRING_PLATFORM_H

#include <QObject>
#include "platform.h"

class Spring_platform : public platform
{
		Q_OBJECT
	public:
		explicit Spring_platform(QWidget *parent, int index,int X=0,int Y=0);
		virtual void PaintPlatform(QPainter &p);

	public slots:
		void Checkhit(int,int);//
};

#endif // SPRING_PLATFORM_H

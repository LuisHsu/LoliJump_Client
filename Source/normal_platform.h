#ifndef NORMAL_PLATFORM_H
#define NORMAL_PLATFORM_H

#include <QObject>
#include "platform.h"

class Normal_platform : public platform
{
		Q_OBJECT
	public:
		explicit Normal_platform(QWidget *parent, int index,int X=0,int Y=0);
		virtual void PaintPlatform(QPainter &p);

	public slots:
		void Checkhit(int,int);//
};

#endif // NORMAL_PLATFORM_H

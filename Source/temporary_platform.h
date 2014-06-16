#ifndef TEMPORARY_PLATFORM_H
#define TEMPORARY_PLATFORM_H

#include <QObject>
#include "platform.h"

class Temporary_platform : public platform
{
		Q_OBJECT
	public:
		explicit Temporary_platform(QWidget *parent, int index,int X=0,int Y=0);
		virtual void PaintPlatform(QPainter &p);

	public slots:
		void Checkhit(int,int);//
};

#endif // TEMPORARY_PLATFORM_H

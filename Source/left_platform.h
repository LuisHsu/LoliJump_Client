#ifndef LEFT_PLATFORM_H
#define LEFT_PLATFORM_H

#include <QObject>
#include "platform.h"

class Left_platform : public platform
{
		Q_OBJECT
	public:
		explicit Left_platform(QWidget *parent, int index,int X=0,int Y=0);
		virtual void PaintPlatform(QPainter &p);

	public slots:
		void Checkhit(int,int);//
};

#endif // LEFT_PLATFORM_H

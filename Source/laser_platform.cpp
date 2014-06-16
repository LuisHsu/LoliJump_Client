#include "laser_platform.h"

Laser_platform::Laser_platform(QWidget *parent, int index,int X,int Y) :
	platform(parent,index,10,PLATFORM_LASER,X,Y)
{
}

void Laser_platform::Checkhit(int characterX, int characterY){
	if(((characterX>=x)&&(characterX<=(x+143)))&&((characterY>=y)&&(characterY<=(y+Height)))){
		emit Hitted(y,1);
	}
}

void Laser_platform::PaintPlatform (QPainter &p){
	static QPixmap pix(":/Platform/Resources/Laser_Platform.png");
	p.drawPixmap(x,y,143,Height,pix);
}

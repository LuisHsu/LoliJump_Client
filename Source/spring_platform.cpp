#include "spring_platform.h"

Spring_platform::Spring_platform(QWidget *parent, int index, int X, int Y) :
	platform(parent,index,21,PLATFORM_SPRING,X,Y)
{

}

void Spring_platform::Checkhit(int characterX, int characterY){
	if(((characterX>=x)&&(characterX<=(x+143)))&&((characterY>=y)&&(characterY<=(y+Height)))){
		emit Hitted(y,5);
	}
}

void Spring_platform::PaintPlatform (QPainter &p){
	static QPixmap pix(":/Platform/Resources/Spring_Platform.png");
	p.drawPixmap(x,y,143,Height,pix);
}

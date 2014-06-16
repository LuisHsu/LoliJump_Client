#include "temporary_platform.h"

Temporary_platform::Temporary_platform(QWidget *parent, int index, int X, int Y) :
	platform(parent,index,10,PLATFORM_TEMPORARY,X,Y)
{

}

void Temporary_platform::Checkhit(int characterX, int characterY){
	if(((characterX>=x)&&(characterX<=(x+143)))&&((characterY>=y)&&(characterY<=(y+Height)))){
		emit Hitted(y,2);
	}
}

void Temporary_platform::PaintPlatform (QPainter &p){
	static QPixmap pix(":/Platform/Resources/Temporary_Platform.png");
	p.drawPixmap(x,y,143,Height,pix);
}

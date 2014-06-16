#include "normal_platform.h"

Normal_platform::Normal_platform(QWidget *parent,int index,int X,int Y) :
	platform(parent,index,10,PLATFORM_NORMAL,X,Y)
{
}
void Normal_platform::Checkhit(int characterX, int characterY){
	if(((characterX>=x)&&(characterX<=(x+143)))&&((characterY>=y)&&(characterY<=(y+Height)))){
		emit Hitted(y,0);
	}
}

void Normal_platform::PaintPlatform (QPainter &p){
	static QPixmap pix(":/Platform/Resources/Normal_Platform.png");
	p.drawPixmap(x,y,143,Height,pix);
}

#include "right_platform.h"

Right_platform::Right_platform(QWidget *parent, int index, int X, int Y) :
	platform(parent,index,28,PLATFORM_RIGHT,X,Y)
{

}

void Right_platform::Checkhit(int characterX, int characterY){
	if(((characterX>=x)&&(characterX<=(x+143)))&&((characterY>=y+7)&&(characterY<=(y+Height)))){
		emit Hitted(y+7,4);
	}
}

void Right_platform::PaintPlatform (QPainter &p){
	static QPixmap pix(":/Platform/Resources/Right_Platform.png");
	p.drawPixmap(x,y,143,Height,pix);
}

#include "left_platform.h"

Left_platform::Left_platform(QWidget *parent, int index, int X, int Y) :
	platform(parent,index,28,PLATFORM_LEFT,X,Y)
{

}

void Left_platform::Checkhit(int characterX, int characterY){
	if(((characterX>=x)&&(characterX<=(x+143)))&&((characterY>=y+7)&&(characterY<=(y+Height)))){
		emit Hitted(y+7,3);
	}
}

void Left_platform::PaintPlatform (QPainter &p){
	static QPixmap pix(":/Platform/Resources/Left_Platform.png");
	p.drawPixmap(x,y,143,Height,pix);
}

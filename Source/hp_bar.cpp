#include "hp_bar.h"

hp_bar::hp_bar(QLabel *label, const int max)
{
	Label=label;
	Label->setPixmap(QPixmap(":/HP/Resources/Red_HP.png").scaled(Label->width(),Label->height()));
	Max=max;
	hp=Max;
	increment=label->width()/max;
}

void hp_bar::Set(int value){
	hp=value;
	Label->setPixmap(QPixmap(":/HP/Resources/Red_HP.png").scaled(WIDTH,HEIGHT).copy(0,0,hp*increment,Label->height()));
	Label->setGeometry(Label->x(),Label->y(),hp*increment,Label->height());
}

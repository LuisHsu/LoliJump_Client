#include "platform.h"

platform::platform(QWidget *parent, int index , int height, int type, int X, int Y) :
	Type(type)
{
	if(X==0){
		x=(qrand()%351)+37;
	}else{
		x=X;
	}
	if(Y==0){
		y=610-height;
	}else{
		y=Y;
	}
	Parent=parent;
	Index=index;
	Height=height;
}

platform::~platform(){
}

void platform::MoveUp(){
	y-=1;
	if(y<(35)){
		emit ReachTop(0,true);
	}
}

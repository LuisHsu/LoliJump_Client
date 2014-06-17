#include "character.h"

Character::Character(QWidget *parent) :
	Parent(parent)
{
	ChtrTimer=new QTimer(this);
	TempTimer=new QTimer(this);
	QObject::connect(ChtrTimer,SIGNAL(timeout()),this,SLOT(MoveCharacter()));
	QObject::connect (TempTimer,SIGNAL(timeout()),this,SLOT(TempOut()));
	Static_Movie=new QMovie(":/Character/Girl_Stand");
	Jump_Movie=new QMovie(":/Character/Girl_Jump");
	L_Jump_Movie=new QMovie(":/Character/Girl_L_Jump");
	R_Jump_Movie=new QMovie(":/Character/Girl_R_Jump");
	L_Walk_Movie=new QMovie(":/Character/Girl_L_Walk");
	R_Walk_Movie=new QMovie(":/Character/Girl_R_Walk");
}
Character::~Character (){
	delete Static_Movie;
	delete Jump_Movie;
	delete L_Jump_Movie;
	delete R_Jump_Movie;
	delete L_Walk_Movie;
	delete R_Walk_Movie;
	delete ChtrTimer;
}

void Character::initialize(){
	x=240;
	y=130;
	L_press=false;
	R_press=false;
	Vertical=0;
	pla=-1;

	Hurted=false;
	Healed=false;
	TempTimeOut=false;
	TempTimeStarted=false;
	t_y=0;
	s_y=0;
	emit CharacterPix(Static_Movie);
	emit CharacterMove(x,y);
	emit PlatformChange(0);
}
void Character::StartCharacter(){
	ChtrTimer->start(TimerTick);
}

void Character::StopCharacter(){
	ChtrTimer->stop();
}

void Character::LeftPress(bool press){
	if(press==true){
		L_press=true;
	}else{
		L_press=false;
	}
}

void Character::RightPress(bool press){
	if(press==true){
		R_press=true;
	}else{
		R_press=false;
	}
}

void Character::MoveCharacter(){
	if((L_press==true)&&(R_press==false)){//Left
		x-=MoveSpeed;
		if(x<37){
			x=37;
		}
		if(Vertical>-1&&Vertical<1){
			emit CharacterPix(L_Walk_Movie);
		}else{
			emit CharacterPix(L_Jump_Movie);
		}
	}else{
		if((L_press==false)&&(R_press==true)){//Right
			x+=MoveSpeed;
			if(x>500){
				x=500;
			}
			if(Vertical>-1&&Vertical<1){
				emit CharacterPix(R_Walk_Movie);
			}else{
				emit CharacterPix(R_Jump_Movie);
			}
		}else{//Middle
			if(Vertical>-1&&Vertical<1){
				emit CharacterPix(Static_Movie);
			}else{
				emit CharacterPix(Jump_Movie);
			}
		}
	}
	emit MoveDown(x+15,y+50);
	if(Vertical!=0){
		Hurted=false;
		Healed=false;
		TempTimer->stop();
	}
	if((y-t_y)>10){
		TempTimeOut=false;
		TempTimeStarted=false;
	}
	y-=Vertical;
	Vertical-=Gravity;
	if(y>610){
		emit Fall();
	}
	if(y<50){
		if((y-s_y)>21){
			emit HpChange(-5);
		}
		y=50;
		s_y=y;
	}
	emit CharacterMove(x,y);
}

void Character::NormalTouched (int Y){
	Vertical=0;
	y=Y-50;
	if(Healed==false){
		emit HpChange(1);
		pla+=1;
		emit PlatformChange(pla);
	}
	Healed=true;
	t_y=0;
}

void Character::LaserTouched (int Y){
	Vertical=0;
	y=Y-50;
	if(Hurted==false){
		emit HpChange(-5);
		pla+=1;
		emit PlatformChange(pla);
	}
	Hurted=true;
	t_y=0;
}

void Character::Hited(int Y, int type){
	if((y-s_y)>21){
		switch (type){
			case 0:
				NormalTouched(Y);
			break;
			case 1:
				LaserTouched(Y);
			break;
			case 2:
				TempTouched(Y);
			break;
			case 3:
				LeftTouched(Y);
			break;
			case 4:
				RightTouched(Y);
			break;
			case 5:
				SpringTouched(Y);
			break;
		}

		s_y=0;
	}
}

void Character::TempTouched (int Y){
	if(TempTimeStarted==false){
		TempTimer->start(500);
		TempTimeStarted=true;
	}
	if(TempTimeOut==false){
		Vertical=0;
		y=Y-50;
		t_y=y;
		if(Healed==false){
			emit HpChange(1);
			pla+=1;
			emit PlatformChange(pla);
		}
		Healed=true;
	}
}

void Character::TempOut(){
	TempTimeOut=true;
	TempTimer->stop();
}

void Character::LeftTouched (int Y){
	Vertical=0;
	y=Y-50;
	x-=LR_Speed;
	if(Healed==false){
		emit HpChange(1);
		pla+=1;
		emit PlatformChange(pla);
	}
	Healed=true;
	t_y=0;
}

void Character::RightTouched (int Y){
	Vertical=0;
	y=Y-50;
	x+=LR_Speed;
	if(Healed==false){
		emit HpChange(1);
		pla+=1;
		emit PlatformChange(pla);
	}
	Healed=true;
	t_y=0;
}

void Character::SpringTouched (int Y){

	Vertical=JumpHeight;
	y=Y-50;
	if(Healed==false){
		emit HpChange(1);
		pla+=1;
		emit PlatformChange(pla);
	}
	Healed=true;
	t_y=0;
}

int Character::getPlatform (){
	return pla;
}

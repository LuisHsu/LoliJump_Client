#include "game.h"

Game::Game(QWidget *parent, hp_bar *Bar, QString pat ){


	qsrand(QDateTime::currentMSecsSinceEpoch());
	Parent=parent;

	path=pat;
	Lolita=new Character(Parent);

	SecTimer=new QTimer(this);
	MilliTimer=new QTimer(this);
	PaintTimer=new QTimer(this);
	PaintTimer->start(1);

	bar=Bar;
	BGM=new QMediaPlayer(this);
	BGMList=new QMediaPlaylist(this);
	BGMList->addMedia(QUrl::fromLocalFile(path+"/BGM.mp3"));
	BGMList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
	BGM->setPlaylist(BGMList);
	BGM->setVolume(50);

	Started=false;

	QObject::connect(SecTimer,SIGNAL(timeout()),this,SLOT(SecTimeOut()));
	QObject::connect(MilliTimer,SIGNAL(timeout()),this,SLOT(MilliTimeOut()));
	QObject::connect(PaintTimer,SIGNAL(timeout()),parent,SLOT(update()));
	QObject::connect(Lolita,SIGNAL(Fall()),this,SLOT(Die()));
}

Game::~Game(){
	delete Lolita;
	delete SecTimer;
	delete MilliTimer;
	delete PaintTimer;
	for(int i=0;i<Platform_List.count();++i){
		RemovePlatform(i,false);
	}
	Platform_List.clear();
}

void Game::StartButtonClicked(){
	if(Started==false){
		Started=true;
		InitializeGame();
	}
	if(Paused==true){
		SecTimer->start(1000);
		MilliTimer->start(Maxinum_Speed);
		Lolita->StartCharacter();

		Paused=false;
		emit TimeChange(RecentTime);
		emit StartButtonImage(1);
	}else{
		SecTimer->stop();
		MilliTimer->stop();
		Lolita->StopCharacter();

		Paused=true;
		emit StartButtonImage(0);
	}
}

void Game::Die(){
	BGM->stop();
	QMediaPlayer FX(this);
	FX.setMedia(QUrl::fromLocalFile(path+"/Annie.mp3"));
	FX.play();
	SecTimer->stop();
	MilliTimer->stop();
	Lolita->StopCharacter();
	Paused=true;
	emit StartButtonImage(0);
	Started=false;

	bar->Set(0);

	for(int i=0;i<Platform_List.count();++i){
		RemovePlatform(i,false);
	}
	Platform_List.clear();
	Parent->repaint();

	Leader_window=new Leaderboard(Floor,Lolita->getPlatform());
	Leader_window->show();
	Parent->setEnabled(false);
	Leader_window->exec();
	delete Leader_window;
	Parent->setEnabled(true);

}

void Game::SecTimeOut(){

	if(CountAccelerate<AcceleGap){
		CountAccelerate+=1;
	}else{
		CountAccelerate=0;
		if(RecentElapsed>=0){
			RecentElapsed-=1;
		}
		if(GenerateGap<MaxinumFloorDist){
			GenerateGap+=GenerateAccele;
		}
	}

	RecentTime+=1;
	emit TimeChange(RecentTime);
}

void Game::GeneratePlatform(int type, int X, int Y){
	Normal_platform *tmpnor;
	Laser_platform *tmplas;
	Temporary_platform *tmptem;
	Left_platform *tmplef;
	Right_platform *tmprgt;
	Spring_platform *tmpspr;
	if(type==-1){
		type=qrand()%10;
		switch (type) {
			case 0:
			case 1:
			case 7:
				tmpnor=new Normal_platform(Parent,Platform_List.count(),X,Y);
				Platform_List.push_back(tmpnor);
				QObject::connect(tmpnor,SIGNAL(Hitted(int,int)),Lolita,SLOT(Hited(int,int)));
			break;
			case 2:
			case 8:
				tmplas=new Laser_platform(Parent,Platform_List.count(),X,Y);
				Platform_List.push_back(tmplas);
				QObject::connect(tmplas,SIGNAL(Hitted(int,int)),Lolita,SLOT(Hited(int,int)));
			break;
			case 3:
			case 9:
				tmptem=new Temporary_platform(Parent,Platform_List.count(),X,Y);
				Platform_List.push_back(tmptem);
				QObject::connect (tmptem,SIGNAL(Hitted(int,int)),Lolita,SLOT(Hited(int,int)));
			break;
			case 4:
				tmplef=new Left_platform(Parent,Platform_List.count(),X,Y);
				Platform_List.push_back(tmplef);
				QObject::connect (tmplef,SIGNAL(Hitted(int,int)),Lolita,SLOT(Hited(int,int)));
			break;
			case 5:
				tmprgt=new Right_platform(Parent,Platform_List.count(),X,Y);
				Platform_List.push_back(tmprgt);
				QObject::connect (tmprgt,SIGNAL(Hitted(int,int)),Lolita,SLOT(Hited(int,int)));
			break;
			case 6:
				tmpspr=new Spring_platform(Parent,Platform_List.count(),X,Y);
				Platform_List.push_back(tmpspr);
				QObject::connect (tmpspr,SIGNAL(Hitted(int,int)),Lolita,SLOT(Hited(int,int)));
			break;
		}
	}else{
		switch(type){
			case PLATFORM_NORMAL:
				tmpnor=new Normal_platform(Parent,Platform_List.count(),X,Y);
				Platform_List.push_back(tmpnor);
				QObject::connect(tmpnor,SIGNAL(Hitted(int,int)),Lolita,SLOT(Hited(int,int)));
			break;
			case PLATFORM_LASER:
				tmplas=new Laser_platform(Parent,Platform_List.count(),X,Y);
				Platform_List.push_back(tmplas);
				QObject::connect(tmplas,SIGNAL(Hitted(int,int)),Lolita,SLOT(Hited(int,int)));
			break;
			case PLATFORM_TEMPORARY:
				tmptem=new Temporary_platform(Parent,Platform_List.count(),X,Y);
				Platform_List.push_back(tmptem);
				QObject::connect (tmptem,SIGNAL(Hitted(int,int)),Lolita,SLOT(Hited(int,int)));
			break;
			case PLATFORM_LEFT:
				tmplef=new Left_platform(Parent,Platform_List.count(),X,Y);
				Platform_List.push_back(tmplef);
				QObject::connect (tmplef,SIGNAL(Hitted(int,int)),Lolita,SLOT(Hited(int,int)));
			break;
			case PLATFORM_RIGHT:
				tmprgt=new Right_platform(Parent,Platform_List.count(),X,Y);
				Platform_List.push_back(tmprgt);
				QObject::connect (tmprgt,SIGNAL(Hitted(int,int)),Lolita,SLOT(Hited(int,int)));
			break;
			case PLATFORM_SPRING:
				tmpspr=new Spring_platform(Parent,Platform_List.count(),X,Y);
				Platform_List.push_back(tmpspr);
				QObject::connect (tmpspr,SIGNAL(Hitted(int,int)),Lolita,SLOT(Hited(int,int)));
			break;
		}
	}
	QObject::connect(this,SIGNAL(PlatformUp()),Platform_List.back(),SLOT(MoveUp()));
	QObject::connect(Platform_List.back(),SIGNAL(ReachTop(int,bool)),this,SLOT(RemovePlatform(int,bool)));
	QObject::connect(Lolita,SIGNAL(MoveDown(int,int)),Platform_List.back(),SLOT(Checkhit(int,int)));
}

void Game::RemovePlatform(int index,bool ClrPtr){
	delete Platform_List[index];
	if(ClrPtr==true){
		Platform_List.removeAt(index);
	}
}

void Game::InitializeGame(){

	Lolita->initialize();
	emit FloorChange(0);
	emit TimeChange(0);
	emit PlatformChange(0);
	emit HPChange(25);

	RecentTime=0;
	RecentElapsed=INIT_ELAPSED;
	CountElapsed=0;
	CountAccelerate=0;
	Paused=true;
	CountGenerate=0;
	FloorCount=0;
	Floor=0;
	GenerateGap=Init_Gap;

	BGM->play();

	GeneratePlatform(PLATFORM_NORMAL,200,610-426);
	GeneratePlatform(PLATFORM_RAND,LOCATION_RAND,610-355);
	GeneratePlatform(PLATFORM_RAND,LOCATION_RAND,610-284);
	GeneratePlatform(PLATFORM_RAND,LOCATION_RAND,610-213);
	GeneratePlatform(PLATFORM_RAND,LOCATION_RAND,610-142);
	GeneratePlatform(PLATFORM_RAND,LOCATION_RAND,610-71);
	GeneratePlatform(PLATFORM_RAND,LOCATION_RAND,LOCATION_RAND);
}

void Game::MilliTimeOut(){
	if(CountElapsed<RecentElapsed){
		CountElapsed+=1;
	}else{
		CountElapsed=0;
		if(CountGenerate<GenerateGap){
			CountGenerate+=1;
		}else{
			CountGenerate=0;
			GeneratePlatform();
		}
		if(FloorCount<FloorDistance){
			FloorCount+=1;
		}else{
			FloorCount=0;
			Floor+=1;
			emit FloorChange(Floor);
		}
		emit PlatformUp();
	}
}

void Game::Paint (QPainter &p){
	for(int i=0;i<Platform_List.count();++i){
		Platform_List[i]->PaintPlatform(p);
	}
}

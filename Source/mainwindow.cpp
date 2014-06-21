#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	//Allocate object
	ui->setupUi(this);
	HpBar=new hp_bar(ui->HPLabel_Red,MAXHP);
	QString path=QApplication::applicationDirPath();
	BGM=new QMediaPlayer(this);
	BGMList=new QMediaPlaylist(this);
	BGMList->addMedia(QUrl::fromLocalFile(path+"/BGM.mp3"));
	BGMList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
	BGM->setPlaylist(BGMList);
	BGM->setVolume(50);
	game=new Game(this,HpBar,QApplication::applicationDirPath(),BGM);


	//Connect
	QObject::connect(ui->StartButton,SIGNAL(clicked()),game,SLOT(StartButtonClicked()));
	QObject::connect(game,SIGNAL(StartButtonImage(int)),this,SLOT(ChangeStartButton(int)));
	QObject::connect(game,SIGNAL(FloorChange(int)),this,SLOT(ChangeFloor(int)));
	QObject::connect(game,SIGNAL(HPChange(int)),this,SLOT(ChangeHP(int)));
	QObject::connect(game,SIGNAL(PlatformChange(int)),this,SLOT(ChangePlatform(int)));
	QObject::connect(game,SIGNAL(RecordChange(int)),this,SLOT(ChangeRecord(int)));
	QObject::connect(game,SIGNAL(TimeChange(int)),this,SLOT(ChangeTime(int)));
	QObject::connect(HpBar,SIGNAL(Hp_Empty()),game,SLOT(Die()));
	QObject::connect(game->Lolita,SIGNAL(CharacterPix(QMovie*)),this,SLOT(CharacterPixChange(QMovie*)));
	QObject::connect(game->Lolita,SIGNAL(CharacterMove(int,int)),this,SLOT(MoveCharacter(int,int)));
	QObject::connect(game->Lolita,SIGNAL(HpChange(int)),this,SLOT(ChangeHP(int)));
	QObject::connect(game->Lolita,SIGNAL(PlatformChange(int)),this,SLOT(ChangePlatform(int)));

	//Initialize
	game->Lolita->initialize();
	LoadRecord();
}

MainWindow::~MainWindow()
{	
	SaveRecord();
	delete HpBar;
	delete game;
	delete ui;
}

void MainWindow::LoadRecord(){
	record=0;
	std::ifstream fin("Record.rec");
	if(fin){
		fin>>record;
		ChangeRecord(record);
	}
	fin.close();
}

void MainWindow::SaveRecord(){
	std::ofstream fout("Record.rec");
	fout<<record;
	fout.close();
}

void MainWindow::ChangeFloor(int value){
	if(value>record){
		ChangeRecord(value);
	}
	ui->Floor_Label->setText("<html><head/><body><p><span style=\" font-size:64pt; color:#ffffff;\">"+QString::number(value,10)+"</span></p></body></html>");
}

void MainWindow::ChangeTime(int value){
	ui->Time_Label->setText("<html><head/><body><p><span style=\" font-size:64pt; color:#ffffff;\">"+QString::number(value,10)+"</span></p></body></html>");
}

void MainWindow::ChangePlatform(int value){
	ui->Platform_Label->setText("<html><head/><body><p><span style=\" font-size:64pt; color:#ffffff;\">"+QString::number(value,10)+"</span></p></body></html>");
}

void MainWindow::ChangeRecord(int value){
	ui->Record_Label->setText("<html><head/><body><p><span style=\" font-size:64pt; color:#ffffff;\">"+QString::number(value,10)+"</span></p></body></html>");
	record=value;
}

void MainWindow::ChangeHP(int value){
	QMediaPlayer FX(this);
	QString path=QApplication::applicationDirPath();
	FX.setMedia(QUrl::fromLocalFile(path+"/jump.mp3"));
	FX.play();
	if(value<0){
		*HpBar-=value*(-1);
	}else{
		*HpBar+=value;
	}
}

void MainWindow::on_ClearButton_clicked()
{
	ChangeRecord(0);
	this->grabKeyboard();
}

void MainWindow::ChangeStartButton(int value){
	switch(value){
		case 1:
			ui->StartButton->setIcon(QIcon(":/Button/Resources/PauseButton.png"));
			ui->StartButton->setToolTip("Pause Game");
		break;
		default:
			ui->StartButton->setIcon(QIcon(":/Button/Resources/StartButton.png"));
			ui->StartButton->setToolTip("Start Game");
	}
}

void MainWindow::paintEvent(QPaintEvent *){
	QPainter p(this);
	p.drawPixmap(0,0,1008,630,QPixmap(":/Background/Resources/Background.png").scaled (1008,630));
	game->Paint(p);
}

void MainWindow::CharacterPixChange (QMovie *pix){
	ChtrPix=pix;
	ui->Character_Label->setMovie(ChtrPix);
	ChtrPix->start();
}
void MainWindow::MoveCharacter (int X, int Y){
	if((610-Y)<50){
		ui->Character_Label->setGeometry(X,Y,30,610-Y);
	}else{
		ui->Character_Label->setGeometry(X,Y,30,50);
	}
}

void MainWindow::keyPressEvent(QKeyEvent *e){
	switch (e->key()) {
		case Qt::Key_Left:
			game->Lolita->LeftPress(true);
		break;
		case Qt::Key_Right:
			game->Lolita->RightPress(true);
		default:
		break;
	}
}

void MainWindow::keyReleaseEvent(QKeyEvent *e){
	switch (e->key()) {
		case Qt::Key_Left:
			game->Lolita->LeftPress(false);
		break;
		case Qt::Key_Right:
			game->Lolita->RightPress(false);
		default:
		break;
	}
}

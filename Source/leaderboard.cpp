#include "leaderboard.h"
#include "ui_leaderboard.h"

//Send "request" to get leaderboard
//send "...(int)F...(int)P...(namestr)" to summit
//Floor read first, then platform

Leaderboard::Leaderboard(int floor,int PlatformCount) :
	ui(new Ui::Leaderboard)
{
	ui->setupUi(this);
	Floor=floor;
	plat=PlatformCount;

	ui->FloorLCD->display(Floor);
	ui->PlatformLCD->display(plat);
	SendSocket=new QTcpSocket(this);

	QObject::connect (ui->reconnect,SIGNAL(clicked()),this,SLOT(ConnectServer()));
	QObject::connect (ui->Refresh,SIGNAL(clicked()),this,SLOT(Refresh()));
	QObject::connect (ui->SummitButton,SIGNAL(clicked()),this,SLOT(Summit()));

	SendSocket=new QTcpSocket(this);
	ConnectServer();
}

Leaderboard::~Leaderboard()
{
	SendSocket->abort();
	delete SendSocket;
	delete ui;
}

void Leaderboard::ConnectServer(){
	SendSocket->abort();
	delete SendSocket;
	SendSocket=new QTcpSocket(this);
	SendSocket->abort();
	SendSocket->connectToHost(HOSTIP,PORT);
	if(!(SendSocket->waitForConnected(3000))){
		DisplayMsg("Connect Failed!");
		return;
	}
	DisplayMsg("Connect Success!");
	ui->reconnect->setEnabled(false);
	QObject::connect(SendSocket,SIGNAL(readyRead()),this,SLOT(ReadFromServer()));

	Refresh();
}

QString Leaderboard::ConvertString(const QString &input){
	return "<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#ffffff;\">"+input+"</span></p>";
}

void Leaderboard::DisplayFloor (){
	ui->FloorText->clear();
	QString DispStr;
	DispStr="<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\"><html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">p, li { white-space: pre-wrap; }</style></head><body style=\" font-family:'Arial'; font-size:12pt; font-weight:600; font-style:normal;\">";

	DispStr+="<p align=\"center\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Arial'; font-size:12pt; font-weight:600; color:#ffffff;\">Floor Leaderboard</span></p>";

	for(int i=0;i<FloorString.count();++i){
		DispStr+=ConvertString(FloorString[i]);
	}

	DispStr+="</body></html>";
	ui->FloorText->setHtml(DispStr);
}

void Leaderboard::DisplayPlatform (){
	ui->PlatformText->clear ();
	QString DispStr;
	DispStr="<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\"><html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">p, li { white-space: pre-wrap; }</style></head><body style=\" font-family:'Arial'; font-size:12pt; font-weight:600; font-style:normal;\">";

	DispStr+="<p align=\"center\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Arial'; font-size:12pt; font-weight:600; color:#ffffff;\">Platform Leaderboard</span></p>";

	for(int i=0;i<PlatformString.count();++i){
		DispStr+=ConvertString(PlatformString[i]);
	}

	DispStr+="</body></html>";
	ui->PlatformText->setHtml(DispStr);
}

void Leaderboard::DisplayMsg(QString msg){
	QString DispStr;
	DispStr="<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\"><html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">p, li { white-space: pre-wrap; }</style></head><body style=\" font-family:'Arial'; font-size:12pt; font-weight:600; font-style:normal;\">";
	DispStr+=ConvertString(msg);
	DispStr+="</body></html>";
	ui->FloorText->setHtml(DispStr);
	ui->PlatformText->setHtml(DispStr);
}

void Leaderboard::ReadFromServer (){

	QByteArray byteA =SendSocket->readAll();
	QString recvstr=QVariant(byteA).toString();

	int LeaCount=recvstr.split("-")[0].toInt();
	recvstr.remove(0,recvstr.split("-")[0].size ()+1);

	for(int i=0;i<LeaCount;++i){
		int charCount=recvstr.split("-")[0].toInt();
		recvstr.remove(0,recvstr.split("-")[0].size ()+1);
		FloorString.push_back(recvstr.left(charCount));
		recvstr.remove(0,charCount+1);
	}

	for(int i=0;i<LeaCount;++i){
		int charCount=recvstr.split("-")[0].toInt();
		recvstr.remove(0,recvstr.split("-")[0].size ()+1);
		PlatformString.push_back(recvstr.left(charCount));
		recvstr.remove(0,charCount+1);
	}

	DisplayFloor();
	DisplayPlatform();

	FloorString.clear();
	PlatformString.clear();
}

void Leaderboard::Summit (){
	QString msg=QString::number(Floor,10)+"F";
	msg+=QString::number(plat,10)+"P";
	msg+=ui->NameEdit->text();
	SendSocket->write(msg.toStdString().c_str(),strlen(msg.toStdString().c_str()));
	ui->SummitButton->setEnabled (false);
}

void Leaderboard::Refresh(){
	QString req="request";
	SendSocket->write(req.toStdString().c_str(),strlen(req.toStdString().c_str()));
}

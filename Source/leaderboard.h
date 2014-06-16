#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <QDialog>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>

#define HOSTIP "127.0.0.1"
#define PORT 5000

namespace Ui {
	class Leaderboard;
}

class Leaderboard : public QDialog
{
		Q_OBJECT

	public:
		explicit Leaderboard(int floor, int PlatformCount);
		~Leaderboard();

	private slots:
		void ReadFromServer();
		void ConnectServer();
		void Summit();
		void Refresh();

	private:
		Ui::Leaderboard *ui;
		int Floor,plat;
		QTcpSocket *SendSocket;
		QList<QString> FloorString;
		QList<QString> PlatformString;

		void DisplayFloor();
		void DisplayPlatform();
		void DisplayMsg(QString msg);

		QString ConvertString(const QString &input);
};

#endif // LEADERBOARD_H

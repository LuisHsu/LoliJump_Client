#ifndef HP_BAR_H
#define HP_BAR_H

#include <QObject>
#include <QLabel>
#include <QPixmap>

#define WIDTH 450
#define HEIGHT 20

class hp_bar : public QObject
{
		Q_OBJECT
	public:
		explicit hp_bar(QLabel *label, const int max);
		friend void operator+=(hp_bar &bar1,const int value){
			bar1.hp+=value;
			if(bar1.hp>bar1.Max){
				bar1.hp=bar1.Max;
			}

			bar1.Label->setPixmap(QPixmap(":/HP/Resources/Red_HP.png").scaled(WIDTH,HEIGHT).copy(0,0,bar1.hp*bar1.increment,bar1.Label->height()));
			bar1.Label->setGeometry(bar1.Label->x(),bar1.Label->y(),bar1.hp*bar1.increment,bar1.Label->height());
		}
		friend void operator-=(hp_bar &bar1,const int value){
			bar1.hp-=value;
			if(bar1.hp<=0){
				bar1.hp=0;
				emit bar1.Hp_Empty();
			}
			bar1.Label->setPixmap(QPixmap(":/HP/Resources/Red_HP.png").scaled(WIDTH,HEIGHT).copy(0,0,bar1.hp*bar1.increment,bar1.Label->height()));
			bar1.Label->setGeometry(bar1.Label->x(),bar1.Label->y(),bar1.hp*bar1.increment,bar1.Label->height());
		}

		void Set(int);

	signals:
		void Hp_Empty();

	private:
		int hp;
		int Max;
		float increment;
		QLabel *Label;
};

#endif // HP_BAR_H

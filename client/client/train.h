#ifndef ABSTRACTTRAIN_H
#define ABSTRACTTRAIN_H

#include <qstring.h>
#include <enum.h>
#include <qobject.h>
#include "user.h"
#include "qmainwindow.h"

class MainWindow;
class AdminWindow;
class Train:public QObject{
	Q_OBJECT
	friend void User::sendBuyOtherInfo();
	friend void User::buyOther(int x);
	friend void User::buy(int x);
	friend void User::sendBuyInfo();
	//friend void MainWindow::askDetail(int row, int column);
public:
	Train(){}
	Train(MainWindow *parent, QString newTrainName, QString newSStation, QString newEStation, QString newSTime, QString newETime,
		int newTrainType, int newPrice, int newTicketsLeft, int is1i, int is2i);
	Train(AdminWindow *parent, QString newTrainName, QString newSStation, QString newEStation, QString newSTime, QString newETime,
		int newTrainType, int newPrice, int newTicketsLeft, int is1i, int is2i);
	void show(int x);
	QString getTrainName(){return trainName;}
	QString getSTime(){return sTime;}
	int getTrainType(){
		if (trainType1==Stand) return 0; else return 1;
	}
	bool editable();
private:
	QString trainName;
	QString sStation;
	QString eStation;
	QString sTime;
	QString eTime;
	int price;
	int ticketsLeft;
	int windowType;
	trainType trainType1;//��¼��Ϊ��λ������
	trainType2 trainType3;//��¼��ΪTKG�е���һ��
	bool is1,is2;//��¼������յ��Ƿ�Ϊ·����վ��
	MainWindow *parent;
	AdminWindow *parent2;
private:
	//void selectSeat();
	QString tt1toString(trainType t);
	QString tt2toString(trainType2 t);
};

#endif
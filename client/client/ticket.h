#ifndef TICKET_H
#define TICKET_H
#include <qobject.h>
#include <qdatetime.h>
#include "enum.h"

class MainWindow;
class Ticket{
	friend class User;
public:
	Ticket(){}
	Ticket(MainWindow *parent, QString newTrainName, QString newSStation, QString newEStation, QString newSTime, QString newDTime,
		trainType newTrType, int newSeat, int newPrice, ticketType newTType);
	void show(int x);
private:
	QString trainName;
	QString sStation;
	QString eStation;
	QString sTime;
	QString dTime;
	trainType trType;
	trainType2 trType2;
	int duration;//ʱ��
	int seat;//��λ
	int price;
	ticketType tType;//ѧ��Ʊ��
	MainWindow *parent;
	QString tt1toString(trainType t);
	QString tt2toString(trainType2 t);
	QString seattoString(int x);
	QString tttoString(ticketType t);
};

#endif
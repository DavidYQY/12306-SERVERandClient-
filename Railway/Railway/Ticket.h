#pragma once
#include <Qstring>
class Ticket
{
public:
	Ticket(void){}
	~Ticket(void);
	QString TrainId;
	QString UserId;
	QString StartTime;
	QString EndTime;//Ϊ�˲�ѯ
	QString Origin;
	QString Destination;
	QString Buyer;
	int Seat;
	int Tickettype;
	int cartype;//Ϊ�˲�ѯ

	int OriginStationId;
	double price;
	int DestinationStaionId;//����Ʊ��
};


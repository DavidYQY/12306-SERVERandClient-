#pragma once
#include<QString>
class Train
{
public:
	Train(QString t="0",QString s="0",QString e="0",QString o=QStringLiteral("�Ϻ�"),QString d=QStringLiteral("����"),int StationId=0,int c=-1,int p=553,int ls=0)
		:TrainId(t),StartTime(s),EndTime(e),Origin(o),Destination(d),carType(c),Price(p),StationId(StationId),leftSeat(ls)
	{
	}
	void set(QString t,QString s,QString e,QString o=QStringLiteral("�Ϻ�"),QString d=QStringLiteral("����"),int sid=0,int l=0,int c=0,int p=0)
	{
		TrainId=t;StartTime=s;EndTime=e;Origin=o;Destination=d;carType=c;Price=p;StationId=sid;length=l;
	}
	void clear()
	{
		TrainId="0",StartTime="0",EndTime="0",carType=-1,leftSeat=0;
	}
	~Train(void);
	QString TrainId;
	QString StartTime;
	QString EndTime;
	QString Origin;
	QString Destination;
	QString TrainType;
	int carType;
	int length;
	int Price;
	int StationId;
	int maxSeatNum;
	int leftSeat;
	bool flag1;//�Ƿ�����ʼվ
	bool flag2;//�Ƿ����յ�վ
	int originStationId;//Ϊ����Ʊ����
	int endStationId;
	int addType;//Ϊ������г��ĸ���������0��������ӣ�1����ʱ���
	int addDays;//����г�ʱ�ĸ�������
};


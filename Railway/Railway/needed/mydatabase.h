#ifndef MYDATABASE_H
#define MYDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSQlQuery>
#include <QTime>
#include <QSqlError>
#include <QtDebug>
#include <QSqlDriver>
#include <QSqlRecord>
#include "train.h"
#include "ticket.h"
#include "user.h"
#include "admin.h"
enum id
{
	User=1,
	Admin=2,
};
class MyDataBase : public QObject
{
	Q_OBJECT

public:
	MyDataBase(QObject *parent=0);
	~MyDataBase();
	bool createConnection(QString);
	bool createTables();
	bool queryAll(QString);//��ѯ������Ϣ
	QStringList queryInfo(QString table,QString UserId);//��table���ҵ���Ӧ�û�����ȫ����Ϣ
	bool addTrain(QString date);
	bool deleteTrain(QString date);//���˽���Ͱ��⳵ɾ��.
	bool deleteTicket(QString date);//���˽���Ͱ�ƱҲɾ��.
	QString date;//����

signals:
	void newdebug(const QString&);
	void newUser(int,QString,int,QStringList a=QStringList());
	void registerUser(int);
	void userTicketInfo(QStringList);
	void trainInfo(QStringList);
	void returndeleteResult(int);
	void midStationInfo(QStringList);
	void userAddMoneyResult(int);
	void userUpdateInfoResult(int);
	void buyTicketResult(int);
	void adminUpdateInfoResult(int);
	void addTrainResult(int);
	void trainUpdateResult(int);
	void deleteTrainResult(int);

public slots:
	void checkNewUser(QString,QString);
	void registerNewUser(QString,QString,QString,QString,QString,QString,QString,QString,QString);//����һ��
	void onTicketQuery(QString);
	void onTrainQuery(Train t);
	void onTicketReturn(Ticket t);
	void onMidStationQuery(Train t);
	void onUserAddMoney(UserClass t);
	void onUserUpdateInfo(UserClass u);
	void onBuyTicket(Ticket);
	void onUpdateAdminInfo(admin);
	void onAddTrainInfo(Train);
	void onUpdateTrainInfo(Train);
	void onDeleteTrain(Train);

private:
	QString DateBaseName;
	QSqlDatabase db;
	QString tranlateDate(QString);
	void aux_addTrain(const Train& t);
	int addUser(QString,QString,QString,QString,QString,QString,QString,QString,QString);//�����ݿ����user
	int query(QString table,QString UserId,QString);//��table���ѯ�û��������Ƿ�ƥ�䡣
	QStringList queryUserTicketInfo(QString UserId);//��ticket���ҵ��û�����Ʊ����Ϣ��
	QStringList queryTrainInfo(Train t);//��train���ҵ��ƶ�Ҫ���train
	QStringList queryMidStationInfo(Train t);//��train���ҵ�train�������м�վ
	QStringList aux_getTrains(Train t);//�ҵ����з��������ĳ�����
	int ticketReturn(Ticket t);//����ticketreturn�Ľ����
	int addUserMoney(UserClass u);
	int aux_getItemNumber(QString table);//��ȡtable������Ŀ��
	int aux_getStationNum(Train t);//�ҵ���t(��ĳ��)�����г�վ����
	int aux_getSeatNum(Train t);//����trainid�ҵ�������λ��
	int aux_getType(Train t);//����id�ҵ�type
	int aux_getLeftTicket(Train t);
	int aux_getOriginStationId(Ticket t);
	int aux_getDestinationStationId(Ticket t);
	double aux_getCurrentMoney(UserClass u);
	double aux_getPrice(Ticket t);
	QStringList aux_getTrainTicketInfo(Train t);
	int addUserMoney(double money,QString user);
	int updateUserInfo(UserClass u);
	int addTicket(Ticket t);
	QString aux_getOriginTime(Train t);
	QString aux_getEndTime(Train t);
	QString aux_getEndTime(Ticket t);//�ҵ�����Ʊdestination��Ӧ��ʱ��
	double aux_getTrainPrice(const Train& t);
	int updateAdminInfo(admin a);
	QList<Train> aux_getRegularTrain();//��regulartrain������ݳ����浽Qlist
	int addTrain(Train);
	int updateTrainInfo(Train t);
	bool aux_IsExists(QString table,QString TrainId,QString Starttime,QString Origin);
	bool aux_IsExists(QString,QString,QString);
	int aux_updateTrainInfo(QString table,Train t);
	int deleteTrain(Train t);
	int aux_deleteTrain(QString table,Train t);
	bool aux_IsExists(QString table,QString UserId);
	QString aux_getBuyer(Ticket t);
};

#endif // MYDATABASE_H

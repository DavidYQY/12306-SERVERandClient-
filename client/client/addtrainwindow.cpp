#include "addTrainWindow.h"
#include "client.h"
#include "adminwindow.h"
#include <qmessagebox.h>
#include <qdialog.h>

AddTrainWindow::AddTrainWindow(Client* client, AdminWindow* parent):client(client),parent(parent){
	ui.setupUi(this);
	ui.stationTable->setColumnCount(3);
	ui.stationTable->setHorizontalHeaderItem(0,new QTableWidgetItem(QStringLiteral("��վ��")));
	ui.stationTable->setColumnWidth(0,80);
	ui.stationTable->setHorizontalHeaderItem(1,new QTableWidgetItem(QStringLiteral("��վʱ��")));
	ui.stationTable->setColumnWidth(1,160);
	ui.stationTable->setHorizontalHeaderItem(2,new QTableWidgetItem(QStringLiteral("����վ���")));
	QTableWidgetItem *temp=new QTableWidgetItem("");
	//ui.stationTable->setColumnWidth(0,70);
	ui.dStartDate->setDate(QDate::currentDate());
	connect(ui.bCancel,SIGNAL(clicked()),this,SLOT(close()));
	connect(ui.bSubmit,SIGNAL(clicked()),this,SLOT(sendNewTrainInfo()));
	connect(ui.dStartDate,SIGNAL(dateChanged(QDate)),this,SLOT(setupTable()));
	connect(ui.sStationCnt,SIGNAL(valueChanged(int)),this,SLOT(setupTable()));
	connect(ui.cTrType,SIGNAL(currentIndexChanged(int)),this,SLOT(daysBoxEnabled(int)));
	ui.sStationCnt->setValue(2);
	lastRowCnt=0;
	setupTable();
}

void AddTrainWindow::daysBoxEnabled(int x){
	if (x==0) ui.sDaysCnt->setEnabled(false);
	else ui.sDaysCnt->setEnabled(true);
}

bool AddTrainWindow::check(){
	bool flag=true;
	for (int i=0;i<ui.sStationCnt->value()-1;i++){
		QDateTimeEdit *d1=(QDateTimeEdit *)ui.stationTable->cellWidget(i,1);
		QDateTimeEdit *d2=(QDateTimeEdit *)ui.stationTable->cellWidget(i+1,1);
		QDateTime dt1=d1->dateTime(); QDateTime dt2=d2->dateTime();
		if (dt1.secsTo(dt2)<=0) {
			QMessageBox msg;
			msg.setText(QStringLiteral("�ִ�ʱ�̲������ڳ���ʱ�̣�"));
			msg.setWindowTitle("Error");
			msg.exec();
			flag=false; break;
		}
	}
	for (int i=1;i<ui.sStationCnt->value();i++){
		QString t=ui.stationTable->item(i,2)->text();
		bool ok;
		int x=t.toInt(&ok);
		if (!ok) {
			QMessageBox msg;
			msg.setText(QStringLiteral("���Ϊ���������������룡"));
			msg.setWindowTitle("Error");
			msg.exec();
			flag=false; break;
		}
	}
	return flag;
}

void AddTrainWindow::sendNewTrainInfo(){
	if (!check()) return;
	int flag=0; //0������1�Ѵ��ڣ�2��������
	for (int i=0;i<ui.sStationCnt->value()-1;i++){
		QString temp="addtrain-";
		temp+=ui.lTrainName->text()+"-";
		QDateTimeEdit *d1=(QDateTimeEdit *)ui.stationTable->cellWidget(i,1);
		temp+=d1->text()+"-";
		QDateTimeEdit *d2=(QDateTimeEdit *)ui.stationTable->cellWidget(i+1,1);
		temp+=d2->text()+"-";		
		temp+=ui.stationTable->item(i,0)->text()+"-";
		temp+=ui.stationTable->item(i+1,0)->text()+"-";
		temp+=QString::number(ui.cSeatType->currentIndex())+"-";
		temp+=ui.stationTable->item(i+1,2)->text()+"-";
		temp+=QString::number(i)+"-";
		temp+=QString::number(ui.cTrType->currentIndex())+"-";
		temp+=QString::number(ui.sDaysCnt->value());
		client->Write(temp);
		//client->sleep(20);
		client->waitForReadyRead(-1);
		QString m=client->getCurrentMessage();
		if (!(m=="success")) {
			if (m=="exists") flag=1; else flag=2;
		}
	}
	//emit addFinish();
	if (flag==0){
		QMessageBox msg;
		msg.setText(QStringLiteral("��ӳɹ���"));
		msg.exec();
		this->close();
		if (parent->ui.lStart->text()!="" && parent->ui.lDes->text()!="") parent->searchTrain();
	} else if (flag==1){
		QMessageBox msg;
		msg.setText(QStringLiteral("�г����Ѵ��ڣ�"));
		msg.exec();
		//setupTable();
	} else {
		QMessageBox msg;
		msg.setText(QStringLiteral("���ʧ�ܣ�"));
		msg.exec();
		//setupTable();
	}
}

void AddTrainWindow::setupTable(){
	int x=ui.sStationCnt->value();
	ui.stationTable->setRowCount(x);
	if (x>lastRowCnt) {
		for (int i=lastRowCnt;i<x;i++){
			QDateTimeEdit *temp=new QDateTimeEdit();
			temp->setDisplayFormat("yyyy/MM/dd hh:mm");
			temp->setDate(ui.dStartDate->date());
			ui.stationTable->setCellWidget(i,1,temp);
		}
	}
	lastRowCnt=x;
}
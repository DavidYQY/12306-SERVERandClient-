#include "user.h"
#include "qmessagebox.h"
#include "mainwindow.h"
#include "ui_buyother.h"
#include <iostream>

User::User(Client* newClient, MainWindow* parent, QString newUsername, QString newPassword, QString newName, genderType newGender, QString newID, QString newPhone,
		QString newCountry, ticketType newTType, int newBalance, QString newSchoolName, QString newSchoolNum)
		:AbstractUser(newUsername,newPassword,newName,newPhone,false),parent(parent)
{
	client=newClient;
	balance=newBalance;
	gender=newGender;
	ID=newID;
	country=newCountry;
	tType=newTType;
	schoolName=newSchoolName;
	schoolNum=newSchoolNum;
	ticketTypeToBuy=0;
	buyOtherW=NULL;
}

void User::buyOther(int x){
	ticketTypeToBuy=0;
	trainToBuy=x;
	if (buyOtherW!=NULL) delete buyOtherW;
	buyOtherW=new QWidget();
	ui.setupUi(buyOtherW);
	Train *curr=parent->getTrain(x);
	QString temp=QStringLiteral("��ȷ�Ϲ�Ʊ��Ϣ��")+curr->trainName+" "+curr->sStation
		+" "+curr->sTime+" "+curr->eStation+" "+curr->eTime+" "
		+QString::number(curr->price)+QStringLiteral("Ԫ");
	ui.label_2->setText(temp);
	if (curr->price>balance){
		QMessageBox msg2;
		msg2.setText(QStringLiteral("���㣬��ȥ��ֵ��"));
		QPushButton* bOk=msg2.addButton(QStringLiteral("��֪����"),QMessageBox::ButtonRole::NoRole);
		//connect(bOk,SIGNAL(clicked()),&msg2,SLOT(close()));
		msg2.exec();
	} else if (dateCheck(curr->sTime)<=0) {
		QMessageBox msg2;
		msg2.setText(QStringLiteral("�г��Ѿ�ʻ�룡"));
		msg2.setInformativeText(QStringLiteral("��ѡ���������Σ�"));
		QPushButton* bOk=msg2.addButton(QStringLiteral("��֪����"),QMessageBox::ButtonRole::NoRole);
		msg2.exec();
	} else if (dateCheck(curr->sTime)<1800) {
		QMessageBox msg2;
		msg2.setText(QStringLiteral("�г�����30������ʻ�룬��ֹͣ��Ʊ��"));
		msg2.setInformativeText(QStringLiteral("��ѡ���������Σ�"));
		QPushButton* bOk=msg2.addButton(QStringLiteral("��֪����"),QMessageBox::ButtonRole::NoRole);
		msg2.exec();
	} else {
		buyOtherW->show();
		connect(ui.bSubmit,SIGNAL(clicked()),this,SLOT(sendBuyOtherInfo()));
	}
}

void User::sendBuyOtherInfo(){
	Train *curr=parent->getTrain(trainToBuy);
	QString temp=ui.lUsername->text()+"-"+curr->trainName+"-"+curr->sTime+"-"+curr->sStation+"-"+curr->eStation+"-120-"
		+QString::number(ticketTypeToBuy)+"-"+QString::number(curr->price)+"-"+username;
	client->Write("buyticket");
	client->sleep(20);
	client->Write(temp);
	client->waitForReadyRead(-1);
	QString m=client->getCurrentMessage();
	if (m=="success"){
		buyOtherW->close();
		QMessageBox msg;
		msg.setText(QStringLiteral("��Ʊ�ɹ���"));
		msg.setInformativeText(QStringLiteral("��֪ͨ�ó˿����ѹ���Ʊ�в鿴��ϸ��Ϣ~"));
		msg.setWindowTitle(QStringLiteral("Success"));
		msg.exec();
		balance-=curr->price;
		showPersonalInfo();
		parent->searchTrain();
	} else if (m=="xuser") {
		QMessageBox msg;
		msg.setText(QStringLiteral("�û��������ڣ�"));
		msg.setWindowTitle(QStringLiteral("Error"));
		msg.exec();
	} else {
		QMessageBox msg;
		msg.setText(QStringLiteral("��Ʊʧ�ܣ�"));
		msg.setWindowTitle(QStringLiteral("Error"));
		msg.exec();
	}

}

void User::buyStudent(int x){
	ticketTypeToBuy=1;
	buy(x);
}

void User::buy(int x){
	QMessageBox msg;
	trainToBuy=x;
	Train *curr=parent->getTrain(x);
	msg.setText(QStringLiteral("��ȷ�Ϲ�Ʊ��Ϣ��"));
	int price=curr->price;
	if (ticketTypeToBuy==1){
		if (curr->trainType3==G) price*=0.75;
		else price*=0.5;
	}
	msg.setInformativeText(curr->trainName+" "+curr->sStation+" "+curr->sTime+" "+curr->eStation+" "+curr->eTime+" "
		+QString::number(price)+QStringLiteral("Ԫ"));
	QPushButton *bYes=msg.addButton(QStringLiteral("ȷ��"),QMessageBox::ButtonRole::NoRole);
	QPushButton *bNo=msg.addButton(QStringLiteral("ȡ��"),QMessageBox::ButtonRole::NoRole);
	if (price>balance){
		QMessageBox msg2;
		msg2.setText(QStringLiteral("���㣬��ȥ��ֵ��"));
		QPushButton* bOk=msg2.addButton(QStringLiteral("��֪����"),QMessageBox::ButtonRole::NoRole);
		//connect(bOk,SIGNAL(clicked()),&msg2,SLOT(close()));
		msg2.exec();
	} else if (!ticketCheck(curr->trainName,curr->sTime)) {
		QMessageBox msg2;
		msg2.setText(QStringLiteral("���ѹ��ó��γ�Ʊ��"));
		QPushButton* bOk=msg2.addButton(QStringLiteral("��֪����"),QMessageBox::ButtonRole::NoRole);
		msg2.exec();
	} else if (dateCheck(curr->sTime)<=0) {
		QMessageBox msg2;
		msg2.setText(QStringLiteral("�г��Ѿ�ʻ�룡"));
		msg2.setInformativeText(QStringLiteral("��ѡ���������Σ�"));
		QPushButton* bOk=msg2.addButton(QStringLiteral("��֪����"),QMessageBox::ButtonRole::NoRole);
		msg2.exec();
	} else if (dateCheck(curr->sTime)<1800) {
		QMessageBox msg2;
		msg2.setText(QStringLiteral("�г�����30������ʻ�룬��ֹͣ��Ʊ��"));
		msg2.setInformativeText(QStringLiteral("��ѡ���������Σ�"));
		QPushButton* bOk=msg2.addButton(QStringLiteral("��֪����"),QMessageBox::ButtonRole::NoRole);
		msg2.exec();
	} else {
		connect(bYes,SIGNAL(clicked()),this,SLOT(sendBuyInfo()));
		connect(bYes,SIGNAL(clicked()),&msg,SLOT(close()));
		connect(bNo,SIGNAL(clicked()),&msg,SLOT(close()));
		msg.exec();
	}
	ticketTypeToBuy=0;
}

bool User::ticketCheck(QString t, QString d){
	for (int i=0;i<ticketList.size();i++){
		Ticket *tk=ticketList[i];
		if (tk->trainName==t && tk->sTime.mid(0,10)==d.mid(0,10)) return false;
	}
	return true;
}

int User::dateCheck(QString d1){
	QDateTime qdt1=QDateTime::fromString(d1,"yyyy/MM/dd hh:mm");
	int delta=qdt1.secsTo(QDateTime::currentDateTime());
	return (-delta);
}

void User::sendBuyInfo(){
	Train *curr=parent->getTrain(trainToBuy);
	int price=curr->price;
	if (ticketTypeToBuy==1){
		if (curr->trainType3==G) price*=0.75;
		else price*=0.5;
	}
	client->Write("buyticket");
	client->sleep(20);
	client->Write(username+"-"+curr->trainName+"-"+curr->sTime+"-"+curr->sStation+"-"+curr->eStation+"-120-"
		+QString::number(ticketTypeToBuy)+"-"+QString::number(price)+"-"+username);
	client->waitForReadyRead(-1);
	QString m=client->getCurrentMessage();
	if (m=="success"){
		QMessageBox msg;
		msg.setText(QStringLiteral("��Ʊ�ɹ���"));
		msg.setInformativeText(QStringLiteral("�����ѹ���Ʊ�в鿴��ϸ��Ϣ~"));
		msg.setWindowTitle(QStringLiteral("Success"));
		msg.exec();
		balance-=price;
		parent->setupTicketInfo();
		showPersonalInfo();
		parent->searchTrain();
	} else {
		QMessageBox msg;
		msg.setText(QStringLiteral("��Ʊʧ�ܣ�"));
		msg.setWindowTitle(QStringLiteral("Error"));
		msg.exec();
	}
}

void User::pay(int x){
	client->Write("pay-"+username+"-"+QString::number(x));
	client->waitForReadyRead(-1);
	QString m=client->getCurrentMessage();
	if (m=="success") {
		QMessageBox msg;
		msg.setText(QStringLiteral("��ֵ�ɹ���"));
		msg.setWindowTitle(QStringLiteral("Success"));
		msg.exec();
		balance+=x;
		showPersonalInfo();
		parent->payWindow->close();
	} else {
		QMessageBox msg;
		msg.setText(QStringLiteral("��ֵʧ�ܣ�"));
		msg.setWindowTitle(QStringLiteral("Error"));
		msg.exec();
	}
}

void User::extraInfoEditEnabled(int x){
	if (x==1) {
		parent->ui.lSchoolName->setEnabled(true);
		parent->ui.lSchoolID->setEnabled(true);
	} else {
		parent->ui.lSchoolName->setEnabled(false);
		parent->ui.lSchoolName->clear();
		parent->ui.lSchoolID->setEnabled(false);
		parent->ui.lSchoolID->clear();
	}
}

void User::editPersonalInfoEnabled(){
	parent->ui.lPassword->setEnabled(true);
	parent->ui.lName->setEnabled(true);
	parent->ui.cGender->setEnabled(true);
	parent->ui.dBirthday->setEnabled(true);
	parent->ui.cCountry->setEnabled(true);
	parent->ui.lID->setEnabled(true);
	parent->ui.lPhone->setEnabled(true);
	parent->ui.cTType->setEnabled(true);
	if (tType==Student){
		parent->ui.lSchoolName->setEnabled(true);
		parent->ui.lSchoolID->setEnabled(true);
	}
	connect(parent->ui.cTType,SIGNAL(currentIndexChanged(int)),this,SLOT(extraInfoEditEnabled(int)));
}

void User::editPersonalInfoDisabled(){
	parent->ui.lPassword->setEnabled(false);
	parent->ui.lName->setEnabled(false);
	parent->ui.cGender->setEnabled(false);
	parent->ui.dBirthday->setEnabled(false);
	parent->ui.cCountry->setEnabled(false);
	parent->ui.lID->setEnabled(false);
	parent->ui.lPhone->setEnabled(false);
	parent->ui.cTType->setEnabled(false);
	parent->ui.lSchoolName->setEnabled(false);
	parent->ui.lSchoolID->setEnabled(false);
}

bool User::checkID(){
	QString ID=parent->ui.lID->text();
	if (ID.length()!=18) return false;
	for (int i=0;i<17;i++){
		if (!ID[i].isNumber()) return false; 
	}
	if (ID[17].isNumber() || ID[17]=='x' || ID[17]=='X') return true; else return false;
}

bool User::checkPhone(){
	QString phone=parent->ui.lPhone->text();
	if (phone.length()!=11) return false;
	for (int i=0;i<11;i++){
		if (!phone[i].isNumber()) return false;
	}
	return true;
}

bool User::checkInfo(){
	QString name=parent->ui.lName->text();
	QString password=parent->ui.lPassword->text();
	QString schoolName=parent->ui.lSchoolName->text();
	QString schoolNum=parent->ui.lSchoolID->text();
	QString country=parent->ui.cCountry->currentText();
	QDate birthday=parent->ui.dBirthday->date();
	QString ID=parent->ui.lID->text();
	bool gender=(parent->ui.cGender->currentIndex()==0?true:false);
	bool flag=true;
	if (name.contains("-") || name.contains("/") || name.contains(";")) {
		QMessageBox msg;
		msg.setText(QStringLiteral("�������Ƿ��ַ���"));
		msg.setInformativeText(QStringLiteral("- / ;��Ϊ�Ƿ��ַ�"));
		msg.exec();
		flag=false;
	} else if (password.length()<6||password.length()>15){
		QMessageBox msg;
		msg.setText(QStringLiteral("���볤��Ӧ��6��15λ֮�䣡"));
		msg.exec();
		flag=false;
	} else if (password.contains("-") || password.contains("/") || password.contains(";")){
		QMessageBox msg;
		msg.setText(QStringLiteral("���뺬�Ƿ��ַ���"));
		msg.setInformativeText(QStringLiteral("- / ;��Ϊ�Ƿ��ַ�"));
		msg.exec();
		flag=false;
	} else if (schoolName.contains("-") || schoolName.contains("/") || schoolName.contains(";")) {
		QMessageBox msg;
		msg.setText(QStringLiteral("ѧУ���ƺ��Ƿ��ַ���"));
		msg.setInformativeText(QStringLiteral("- / ;��Ϊ�Ƿ��ַ�"));
		msg.exec();
		flag=false;
	} else if (schoolNum.contains("-") || schoolNum.contains("/") || schoolNum.contains(";")) {
		QMessageBox msg;
		msg.setText(QStringLiteral("ѧ�ź��Ƿ��ַ���"));
		msg.setInformativeText(QStringLiteral("- / ;��Ϊ�Ƿ��ַ�"));
		msg.exec();
		flag=false;
	} else if (country!=QStringLiteral("�й�")) {
		return true;
	} else if (!checkPhone()){
		QMessageBox msg;
		msg.setText(QStringLiteral("��Ч���ֻ��ţ�"));
		msg.exec();
		flag=false;
	} else if (!checkID()){
		QMessageBox msg;
		msg.setText(QStringLiteral("��Ч�����֤�ţ�"));
		msg.exec();
		flag=false;
	} else if (!(birthday.year()==(ID.mid(6,4).toInt())&&
			birthday.month()==(ID.mid(10,2).toInt())&&
			birthday.day()==(ID.mid(12,2).toInt()))){
		QMessageBox msg;
		msg.setText(QStringLiteral("���������֤�Ų�����"));
		msg.exec();
		flag=false;
	} else if (ID.mid(16,1).toInt()%2!=(gender?1:0)) {
		QMessageBox msg;
		msg.setText(QStringLiteral("�Ա������֤�Ų�����"));
		msg.exec();
		flag=false;
	} else {
		int a[18];
		for (int i=0;i<17;i++) a[i]=ID.mid(i,1).toInt();
		if (ID.mid(17,1)=="X" || ID.mid(17,1)=="x") a[17]=10; else a[17]=ID.mid(17,1).toInt();
		int sum = a[0]*7 + a[1]*9 + a[2]*10 + a[3]*5 + a[4]*8 + a[5]*4 + a[6]*2  
        + a[7]*1 + a[8]*6 + a[9]*3 +a[10]*7 + a[11]*9 + a[12]*10 + a[13]*5  
        + a[14]*8 + a[15]*4 + a[16]*2;
		int b=sum%11;
		if (b!=(12-a[17])%11) {
			QMessageBox msg;
			msg.setText(QStringLiteral("��Ч�����֤�ţ�"));
			msg.exec();
			flag=false;
		}
	}
	//this->activateWindow();
	//����ѡ��ѧ��ʱѧУ����Ϊ�յ��ж�
	return flag;
}

void User::updateLocalPersonalInfo(){
	password=parent->ui.lPassword->text();
	name=parent->ui.lName->text();
	phone=parent->ui.lPhone->text();
	gender=parent->ui.cGender->currentIndex()==0?Male:Female;
	country=parent->ui.cCountry->currentText();
	ID=parent->ui.lID->text();
	tType=parent->ui.cTType->currentIndex()==0?Adult:Student;
	schoolName=parent->ui.lSchoolName->text();
	schoolNum=parent->ui.lSchoolID->text();
}

void User::updatePersonalInfo(){
	if (checkInfo()){
		client->Write("updateinfo");
		client->sleep(20);
		QString password=parent->ui.lPassword->text();
		QString name=parent->ui.lName->text();
		bool gender=(parent->ui.cGender->currentIndex()==0);
		QString country=parent->ui.cCountry->currentText();
		QString ID=parent->ui.lID->text();
		QString phone=parent->ui.lPhone->text();
		bool tType=(parent->ui.cTType->currentIndex()==0);
		QString schoolName=parent->ui.lSchoolName->text();
		QString schoolID=parent->ui.lSchoolID->text();
		QString temp=username+"-"+password+"-"+name+"-"+(gender?"Male":"Female");
		temp+="-"+country+"-"+ID+"-"+phone+"-"+(tType?"Adult":"Student")+"-"+schoolName+","+schoolID;
		client->Write(temp);
	    client->waitForReadyRead(-1);
		QString s=client->getCurrentMessage();
		if (s=="success"){
			QMessageBox msg;
			msg.setText(QStringLiteral("�޸ĳɹ���"));
			msg.setWindowTitle(QStringLiteral("Success"));
			msg.exec();
			editPersonalInfoDisabled();
			updateLocalPersonalInfo();
			parent->ui.bEdit->show();
			parent->ui.bEditComplete->hide();
			parent->ui.bEditCancel->hide();
			showPersonalInfo();
			parent->setupBuyButton();
		} else if (s=="xID"){
			QMessageBox msg;
			msg.setText(QStringLiteral("���֤���ѱ�ע�ᣡ"));
			msg.setWindowTitle(QStringLiteral("Error"));
			msg.exec();
		} else {
			QMessageBox msg;
			msg.setText(QStringLiteral("����������"));
			msg.setWindowTitle(QStringLiteral("Error"));
			msg.exec();
		}
	}
	//editPersonalInfoDisabled();
}

void User::showPersonalInfo(){
	parent->ui.lUsername->setText(username);
	parent->ui.lPassword->setText(password);
	parent->ui.lName->setText(name);
	parent->ui.cGender->setCurrentIndex(gender==Male?0:1);
	QDate temp;
	temp.setDate(ID.mid(6,4).toInt(),ID.mid(10,2).toInt(),ID.mid(12,2).toInt());
	parent->ui.dBirthday->setDate(temp);
	parent->ui.cCountry->setCurrentIndex(country==QStringLiteral("�й�")?0:1);
	parent->ui.lID->setText(ID);
	parent->ui.lPhone->setText(phone);
	parent->ui.lPay->setText(QString::number(balance));
	parent->ui.cTType->setCurrentIndex(tType==Adult?0:1);
	if (tType==Student){
		parent->ui.lSchoolID->setText(schoolNum);
		parent->ui.lSchoolName->setText(schoolName);
	}
}

void User::returnTicket(int row, int column){
	std::cout<<"returnTicket"<<row<<endl;
	ticketToReturn=row;
	QMessageBox msgBox;
	msgBox.setFixedWidth(500);
	msgBox.setText(QStringLiteral("��ȷ��Ҫ��Ʊ��"));
	msgBox.setInformativeText(ticketList[row]->trainName+" "+ticketList[row]->sStation+" "+ticketList[row]->sTime+
		" "+ticketList[row]->eStation+" "+ticketList[row]->dTime);
	QPushButton *bYes=msgBox.addButton(QStringLiteral("��"),QMessageBox::ButtonRole::NoRole);
	QPushButton *bNo=msgBox.addButton(QStringLiteral("��"),QMessageBox::ButtonRole::NoRole);
	connect(bYes,SIGNAL(clicked()),&msgBox,SLOT(close()));
	connect(bYes,SIGNAL(clicked()),this,SLOT(sendReturnInfo()));
	connect(bNo,SIGNAL(clicked()),&msgBox,SLOT(close()));
	msgBox.exec();
}

void User::sendReturnInfo(){
	client->Write("returnticket");
	client->sleep(20);
	client->Write(username+"-"+ticketList[ticketToReturn]->trainName+"-"+ticketList[ticketToReturn]->sTime);
	client->waitForReadyRead(-1);
	QString m=client->getCurrentMessage();
	if (m=="success"){
		QMessageBox msg;
		msg.setText(QStringLiteral("��Ʊ�ɹ���"));
		msg.setWindowTitle(QStringLiteral("Success"));
		msg.exec();
		balance+=ticketList[ticketToReturn]->price;
		parent->setupTicketInfo();
		showPersonalInfo();
	} else {
		QMessageBox msg;
		msg.setText(QStringLiteral("��Ʊʧ�ܣ�"));
		msg.setWindowTitle(QStringLiteral("Error"));
		msg.exec();
	}
}

void User::showTicket(int x){
	ticketList[x]->show(x);
}

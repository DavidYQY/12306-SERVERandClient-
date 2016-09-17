#include "railway.h"
#include "mainwindow.h"
#include <qdebug>
#include <QmessageBox>
Railway::Railway(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	flag=false;
	connect(ui.pushButton,SIGNAL(clicked()),this,SLOT(onclicked()));
	//connect(ui.spinBox,SIGNAL(editingFinished()),this,SLOT(onclicked()));
}
void Railway::onclicked()
{
	if (flag)//ò��editingFinished���signal�е�С���⡣�����ᴥ������
		return ;
	flag=true;
	if (ui.spinBox->value()==0)
	{
		QMessageBox msgBox;
		msgBox.setText(QStringLiteral("�˿ڲ���Ϊ0��"));
		msgBox.exec();
		flag=false;
		return;
	}
	if (!ui.lineEdit->text().contains("db"))
	{
		QMessageBox msgBox;
		msgBox.setText(QStringLiteral("��������ʵ����ݿ�����"));
		msgBox.exec();
		flag=false;
		return;
	}
	qDebug()<<QString("Your assigned port is %1").arg(ui.spinBox->value());
	mainwindow *m=new mainwindow(ui.spinBox->value(),ui.lineEdit->text());
	m->show();
	setVisible(false);
}
Railway::~Railway()
{

}

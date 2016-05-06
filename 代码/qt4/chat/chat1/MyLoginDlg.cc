#include "MyLoginDlg.h"
#include <iostream>
using namespace std;
MyLoginDlg::MyLoginDlg(QWidget *parent,Qt::WindowFlags flags):QDialog(parent,flags)
{
    QVBoxLayout *mlay = new QVBoxLayout();
    QLabel *p = new QLabel(tr("ip地址"));
    ip = new QLineEdit();
    ip->setText(tr("127.0.0.1"));
    QHBoxLayout *llay = new QHBoxLayout();
    llay->addWidget(p);
    llay->addWidget(ip);
    mlay->addLayout(llay);
    
    p = new QLabel(tr("端口号"));
    port = new QSpinBox();
    port->setRange(1,65535);//范围1-65535
    port->setValue(3000);//默认值3000
    llay = new QHBoxLayout();
    llay->setAlignment(Qt::AlignLeft);//左边对齐
    llay->addWidget(p);
    llay->addWidget(port);
    mlay->addLayout(llay);
    
    p = new QLabel(tr("用户名"));
    name = new QLineEdit();
    llay = new QHBoxLayout();
    llay->addWidget(p);
    llay->addWidget(name);
    mlay->addLayout(llay);
    
    yes=new QPushButton(tr("确定"));
    no =new QPushButton(tr("取消"));
    llay = new QHBoxLayout();
    llay->addWidget(yes);
    llay->addWidget(no);
    mlay->addLayout(llay);
    
    QObject::connect(yes,SIGNAL(clicked()),this,SLOT(sure()));
    connect(no,SIGNAL(clicked()),this,SLOT(close()));
    setLayout(mlay);
    name->setFocus();
}
int MyLoginDlg::sure(void)
{
    unsigned short up = port->value();
    QString portStr = QString("%1").arg(up);
    if(name->text().compare(QString("群")) == 0)
    {
        QMessageBox box;
        box.setText("‘群’是保留名称");
        box.exec();
        return -1;
    }
    emit ok(ip->text(),portStr,name->text());
    return 0;
}
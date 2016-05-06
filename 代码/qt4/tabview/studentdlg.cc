#include "studentdlg.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
studentdlg::studentdlg(QWidget *parent):QDialog(parent)
{
    QVBoxLayout *mlay = new QVBoxLayout();
    QLabel *p = new QLabel(tr("学号"));
    id = new QLineEdit();
    id->setMaxLength(19);//最多输入19个字符
    QHBoxLayout *llay = new QHBoxLayout();
    llay->addWidget(p);
    llay->addWidget(id);
    mlay->addLayout(llay);
    
    p = new QLabel(tr("姓名"));
    name = new QLineEdit();
    name->setMaxLength(19);
    llay = new QHBoxLayout();
    llay->addWidget(p);
    llay->addWidget(name);
    mlay->addLayout(llay);
    
    p = new QLabel(tr("年龄"));
    age = new QSpinBox();
    age->setRange(10,35);//范围10-35
    age->setValue(20);//默认值20
    llay = new QHBoxLayout();
    llay->setAlignment(Qt::AlignLeft);//左边对齐
    llay->addWidget(p);
    llay->addWidget(age);
    mlay->addLayout(llay);
    
    p = new QLabel(tr("性别"));
    sex = new QComboBox();
    sex->addItem(tr("男"));
    sex->addItem(tr("女"));
    llay = new QHBoxLayout();
    llay->setAlignment(Qt::AlignLeft);
    llay->addWidget(p);
    llay->addWidget(sex);
    mlay->addLayout(llay);
    
    yes=new QPushButton(tr("确定"));
    no =new QPushButton(tr("取消"));
    llay = new QHBoxLayout();
    llay->addWidget(yes);
    llay->addWidget(no);
    mlay->addLayout(llay);
    
    setLayout(mlay);
    QObject::connect(yes,SIGNAL(clicked(bool)),this,SLOT(sure()));
    QObject::connect(no,SIGNAL(clicked(bool)),this,SLOT(cancel()));
}
bool studentdlg::checkInput(void)
{
    return true;
}
int studentdlg::getInput(struct student *pstu)
{
    *pstu = stu;
    return 0;
}
int studentdlg::sure(void)
{
    if(checkInput())
    {
        QString sid = id->text();
        QString sname = name->text();
        strcpy(stu.id,(char *)sid.toStdString().c_str());
        strcpy(stu.name,(char *)sname.toStdString().c_str());
        stu.age = (char)age->value();
        if(0 == sex->currentIndex())
        {
            stu.sex = 'm';
        }
        else
        {
            stu.sex = 'f';
        }
        accept();
    }
}
int studentdlg::cancel(void)
{
    reject();
}
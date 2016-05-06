#ifndef  __STUDENTDLG_H__
#define  __STUDENTDLG_H__
#include <stdio.h>
#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include "student.h"
class studentdlg:public QDialog
{
    Q_OBJECT
private:
    QLineEdit *name;
    QLineEdit *id;
    QSpinBox  *age;
    QComboBox *sex;
    QPushButton *yes;
    QPushButton *no;
    struct student stu;
    bool checkInput(void);
protected slots:
    int sure(void);
    int cancel(void);
public:
    studentdlg(QWidget *parent=NULL);
    int getInput(struct student *pstu);
};

#endif
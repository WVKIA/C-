
#ifndef __MYWIDGET_H__
#define __MYWIDGET_H__

#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>

class myWidget:public QWidget
{
    Q_OBJECT
    public:
        myWidget(QWidget *p=0,Qt::WindowFlags f=0);
    public slots:
        void yes(void);
        void no(void);
    protected:
        QPushButton b1;
        QPushButton b2;
        QVBoxLayout mlay;
        QHBoxLayout slay;
        QTextEdit   t1;
        QTextEdit   t2;
};

//QLabel  标签
//QSpinBox  
//QSlider
//QLineEdit
//QRadioButton
//QCheckBox

#endif

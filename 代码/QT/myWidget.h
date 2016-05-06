#ifndef __MYWIDGET_H__
#define __MYWIDGET_H__

#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QTextEdit>
#include <QSlider>
#include <QSpinBox>
#include <QRadioButton>
#include <QCheckBox>
class myWidget:public QWidget
{
	Q_OBJECT
    public:
        myWidget(QWidget *p = 0,Qt::WindowFlags f  =0);
	public slots:
		void yes(void);
		void no(void);
    protected:
        QPushButton b1;
        QPushButton b2;
        QVBoxLayout mlay;
		QHBoxLayout slay;
        QHBoxLayout tlay;
        QSpinBox s1;
        QSlider l1;
        QRadioButton r1;
        QRadioButton r2;
        QCheckBox c1;
        QCheckBox c2;
		QTextEdit t1;
		QTextEdit t2;
};

#endif

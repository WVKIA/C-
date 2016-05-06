#ifndef __MYDIALOG_H__
#define __MYDIALOG_H_
#include <QtGui>
class myDialog:public QDialog
{
    Q_OBJECT
    public:
        myDialog(QWidget *p = 0, Qt::WindowFlags f = 0);
		int getValue(void);
		bool setValue(int);
	signals:
		void valueChanged(int);
	public slots:
		void valueChange(int);
		
		void valueUpdate(void);
    protected:
        QSpinBox s;
        QSlider l;
		
        QVBoxLayout mlay;
		QHBoxLayout toplay;
		QHBoxLayout bottomlay;
		
		QPushButton b1;
		QPushButton b2;
		
		int r;
};
#endif

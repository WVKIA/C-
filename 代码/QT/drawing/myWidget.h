#ifndef __MYWIDGET_H__
#define __MYWIDGET_H__

#include <QtGui>
#include "myDialog.h"
class myWidget:public QWidget
{
	Q_OBJECT
    public:
        myWidget(QWidget *p = 0,Qt::WindowFlags f  =0);
	public slots:
		void dlgAccept(void);
		
		void dlgvalueChange(int);
    protected:
        void paintEvent(QPaintEvent * event);
				
		void mouseDoubleClickEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);
		void mousePressEvent(QMouseEvent *event);
		bool left;
		QPointF pos;
		int r;
		myDialog dlg;
		
};

#endif

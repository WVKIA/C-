#include "myWidget.h"

#include <sstream>
myWidget::myWidget(QWidget *p ,Qt::WindowFlags f ):QWidget(p,f),left(false),pos(QPoint(0,0)),r(100)
{
	QObject::connect(&dlg,SIGNAL(accepted()),this,SLOT(dlgAccept()));
	QObject::connect(&dlg,SIGNAL(rejected()),this,SLOT(dlgAccept()));
	QObject::connect(&dlg,SIGNAL(valueChanged(int)),this,SLOT(dlgvalueChange(int)));
}
void myWidget::paintEvent(QPaintEvent *event)
{
	
	QPainter painter(this);
	painter.drawText(pos,QString("hello world"));
	painter.drawEllipse(pos,r,r);
}
void myWidget::dlgvalueChange(int v)
{
	r = v;
	update();
}
void myWidget::dlgAccept(void)
{
	r = dlg.getValue();
	update();
}
void myWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
	if(event->button() == Qt::RightButton)
	{
		
		dlg.setValue(r);
		
		dlg.setWindowTitle(QString("Radius"));
		dlg.show();
	/*	if(dlg.exec() == QDialog::Accepted)
		{
		r = dlg.getValue();
		update();		
		}        */  //                   mo tai dui hua kuang
	}
	else
	{
		QWidget::mouseDoubleClickEvent(event);
	}
}
void myWidget::mouseMoveEvent(QMouseEvent *event)
{
	if(left)
	{
		pos = event->posF();
		update();
		
	}
	else
	{
		QWidget::mouseMoveEvent(event);
	}
}
void myWidget::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		left = true;
	}
	else
	{
		QWidget::mousePressEvent(event);
	}
}
void myWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		left = false;
	}
	else
	{
		QWidget::mouseReleaseEvent(event);
	}
}

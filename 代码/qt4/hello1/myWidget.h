
#ifndef __MYWIDGET_H__
#define __MYWIDGET_H__

#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include "myDialog.h"

class myWidget:public QWidget
{
    Q_OBJECT
    public:
        myWidget(QWidget *p=0,Qt::WindowFlags f=0);
        virtual ~myWidget();
    public slots:
        void dlgAccept(void);
        void dlgValueChanged(int v);
    protected:
        void paintEvent(QPaintEvent *event);
        void mouseDoubleClickEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent * event);
        void mousePressEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);
        bool left;
        QPointF pos;
        int r;
        myDialog *dlg;
};

//QLabel  标签
//QSpinBox  
//QSlider
//QLineEdit
//QRadioButton
//QCheckBox

#endif

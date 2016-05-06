
#ifndef  __MY_CENTWIN_H__
#define  __MY_CENTWIN_H__
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <iostream>
#include <QMessageBox>
class centwin:public QWidget
{
    private:
        enum checkColor
        {
            RED=0,
            BLACK
        };
        bool gameover;
        int row;
        int column;
        double wid;
        double high;
        double dw;
        double dh;
        double dmax;
        QPen pen;
        QMessageBox box;
        enum checkColor color;
        std::vector<unsigned int>  vp[2];
    public:
        centwin(QWidget *parent=NULL,Qt::WindowFlags flags=0);
    protected:
        void paintEvent(QPaintEvent *event);
        void mousePressEvent(QMouseEvent *event);
        void mouseDoubleClickEvent(QMouseEvent *event); 
        bool checkend(void);
};

#endif

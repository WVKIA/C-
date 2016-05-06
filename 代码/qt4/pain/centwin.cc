#include "centwin.h"
#include <algorithm>

centwin::centwin(QWidget *parent,Qt::WindowFlags flags):QWidget(parent,flags)
{
    row = 8;
    column = 8;
    color = RED;
    gameover = false;
}
bool centwin::checkend(void)
{
    int index = color==RED?0:1;
    int num=1;
    int p=vp[index][vp[index].size()-1];
    int i0=p>>16;
    int j0=p&0xffff;
    int i = i0;
    int j = j0;
    while(1)
    {
        i++;
        if(std::find(vp[index].begin(),vp[index].end(),i<<16|j)
                !=vp[index].end())
        {
            num++;
        }
        else
        {
            break;
        }
    }
    i = i0;
    while(1)
    {
        i--;
        if(std::find(vp[index].begin(),vp[index].end(),i<<16|j)
                !=vp[index].end())
        {
            num++;
        }
        else
        {
            break;
        }
    }
    if(num == 5)
    {
        return true;
    }
    num = 1;
    i=i0;
    j=j0;
    while(1)
    {
        j++;
        if(std::find(vp[index].begin(),vp[index].end(),i<<16|j)
                !=vp[index].end())
        {
            num++;
        }
        else
        {
            break;
        }
    }
    i=i0;
    j=j0;
    while(1)
    {
        j--;
        if(std::find(vp[index].begin(),vp[index].end(),i<<16|j)
                !=vp[index].end())
        {
            num++;
        }
        else
        {
            break;
        }
    }
    if(num == 5)
    {
        return true;
    }
    num = 1;
    i=i0;
    j=j0;
    while(1)
    {
        i++;
        j++;
        if(std::find(vp[index].begin(),vp[index].end(),i<<16|j)
                !=vp[index].end())
        {
            num++;
        }
        else
        {
            break;
        }
    }
    i=i0;
    j=j0;
    while(1)
    {
        i--;
        j--;
        if(std::find(vp[index].begin(),vp[index].end(),i<<16|j)
                !=vp[index].end())
        {
            num++;
        }
        else
        {
            break;
        }
    }
    if(num == 5)
    {
        return true;
    }
    num = 1;
    i=i0;
    j=j0;
    while(1)
    {
        i--;
        j++;
        if(std::find(vp[index].begin(),vp[index].end(),i<<16|j)
                !=vp[index].end())
        {
            num++;
        }
        else
        {
            break;
        }
    }
    i=i0;
    j=j0;
    while(1)
    {
        i++;
        j--;
        if(std::find(vp[index].begin(),vp[index].end(),i<<16|j)
                !=vp[index].end())
        {
            num++;
        }
        else
        {
            break;
        }
    }
    if(num == 5)
    {
        return true;
    }

    return false;
}
void centwin::paintEvent(QPaintEvent *event)
{
    high = height()-20;
    wid = width()-20;
    dh = high/(double)row;
    dw = wid/(double)column;
    dmax = dh*dh/9+dw*dw/9;
    int i = 0;
    int j = 0;
    QPainter painter(this);
    QLine l1;
    for(i=0;i<=row;i++)
    {
        l1.setLine(10,10+i*dh,10+wid,10+i*dh);
        painter.drawLine(l1);
    }
    for(i=0;i<=column;i++)
    {
        l1.setLine(10+i*dw,10,10+i*dw,10+high);
        painter.drawLine(l1);
    }
    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.setBrush(Qt::red);
    for(j=0;j<vp[0].size();j++)
    {
        unsigned int p = vp[0][j];
        double x=(p&0xffff)*dw;
        double y=(p>>16)*dh;
        QRectF rec(x,y,20,20);
        painter.drawEllipse(rec);
    }
    pen.setColor(Qt::black);
    painter.setPen(pen);
    painter.setBrush(Qt::black);
    for(j=0;j<vp[1].size();j++)
    {
        unsigned int p = vp[1][j];
        double x=(p&0xffff)*dw;
        double y=(p>>16)*dh;
        QRectF rec(x,y,20,20);
        painter.drawEllipse(rec);
    }
}
void centwin::mousePressEvent(QMouseEvent *event)
{
    QPointF pf = event->posF();
    int i = 0;
    int j = 0;
    int flag = 0;
    double l1 = 0;
    double l2  = 0;
    if(gameover)
    {
        return;
    }
    for(j=0;j<=column;j++)
    {
        l1 = (dw*j+10-pf.rx())*(dw*j+10-pf.rx());
        for(i=0;i<=row;i++)
        {
            l2 = (dh*i+10-pf.ry())*(dh*i+10-pf.ry());
            if(l1+l2 < dmax)
            {
                flag = 1;
                break;
            }
        }
        if(1 == flag)
        {
            break;
        }
    }
    if(1 == flag)
    {
        if(std::find(vp[0].begin(),vp[0].end(),i<<16|j)
                != vp[0].end())
        {
        }
        else if(std::find(vp[1].begin(),vp[1].end(),i<<16|j)
                != vp[1].end())
        {
        }
        else
        {
            color==RED?vp[0].push_back(i<<16|j):vp[1].push_back(i<<16|j);
            update();
            if(checkend())
            {
                gameover = true;
                if(color == RED)
                {
                    box.setText("red win");
                }
                else
                {
                    box.setText("black win");
                }
                box.show();
            }
            color = RED==color?BLACK:RED;
        }
    }
}
void centwin::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        vp[0].clear();
        vp[1].clear();
        color = RED;
        gameover = false;
        update();
    }
}

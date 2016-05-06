#include "model.h"
#include <iostream>
using namespace std;

mymodel::mymodel(void)
{
    eachPage = 2;
    cuPage   = 0;
    initallstudent(&allstu,100);
    setHorizontalHeaderItem(0,new QStandardItem(QObject::tr("id")));
    setHorizontalHeaderItem(1,new QStandardItem(QObject::tr("name")));
    setHorizontalHeaderItem(2,new QStandardItem(QObject::tr("age")));
    setHorizontalHeaderItem(3,new QStandardItem(QObject::tr("sex")));
    setRowCount(0);
}
bool mymodel::upDate(void)
{
    unsigned int viewNum = eachPage;
    if(0 == allstu.num)
    {
        viewNum = 0;
    }
    else
    {
        unsigned int tmp = allstu.num%eachPage;
        if((cuPage == totalPage-1) && (0!=tmp))
        {
            viewNum = tmp;
        }
    }
    setRowCount(viewNum);
    emit layoutChanged();
}
bool mymodel::pageUp(unsigned int &cu,unsigned int &total)
{
    total = totalPage;
    if(0 == cuPage)
    {
        cu = 0;
        return false;
    }
    cuPage--;
    cu = cuPage;
    return true;
}
bool mymodel::pageDown(unsigned int &cu,unsigned int &total)
{
    if(cuPage == totalPage-1)
    {
        cu = cuPage;
        total = totalPage;
        return false;
    }
    else
    {
        cuPage++;
        cu = cuPage;
        total = totalPage;
        return true;
    }
}
bool mymodel::getPages(unsigned int &cuPage,unsigned int &totalPage,unsigned int &viewNum)
{
    unsigned int vn = eachPage;
    cuPage = this->cuPage;
    totalPage = this->totalPage;
    unsigned int tmp = allstu.num%eachPage;
    if((cuPage == totalPage-1) && (0 != tmp))
    {
        vn = tmp;
    }
    viewNum = vn;
    return true;
}
int mymodel::addstu(struct student &stu)
{
    if(allstu.num == allstu.space)
    {
        grow(&allstu);
    }
    allstu.pall[allstu.num] = stu;
    allstu.num++;
    totalPage = allstu.num/eachPage;
    totalPage += allstu.num%eachPage;
    //setRowCount(eachPage);
    return 0;
}
int mymodel::delstu(int row)
{
    int i = 0;
    row += cuPage*eachPage;
    for(i=row;i<allstu.num-1;i++)
    {
        allstu.pall[i] = allstu.pall[i+1];
    }
    allstu.num--;
    totalPage = allstu.num/eachPage;
    totalPage += allstu.num%eachPage;
    if(cuPage >= totalPage)
    {
        cuPage = totalPage-1;
    }
    //setRowCount(eachPage);
    return 0;
}
QVariant mymodel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()) 
    {
        return QVariant();
    }
    if((index.row() >= rowCount()) || (index.row() < 0))
    {
        return QVariant();
    }
    if(role == Qt::DisplayRole) 
    {
        int row = index.row();
        int i = row+cuPage*eachPage;
        int column = index.column();
        if(column == 0)
        {
            return QString(allstu.pall[i].id);
        }
        else if(1 == column)
        {
            return QString(allstu.pall[i].name);
        }
        else if(2 == column)
        {
            QString s=QString("%1").arg((int)allstu.pall[i].age);
            return s;
        }
        else if(3 == column)
        {
            QString s=QString("%1").arg(allstu.pall[i].sex);
            return s;
        }
    }
    return QVariant();
}
bool mymodel::setData(const QModelIndex &index, const QVariant &value, int role)
{
//    cout<<"setdata:"<<index.row()<<"  "<<index.column()<<endl;
    if(index.isValid() && role == Qt::EditRole) 
    {
        int row = index.row();
        int i = row+cuPage*eachPage;
        int column = index.column();
        string s = value.toString().toStdString();
        cout<<s<<column<<endl;
        if(column == 0)
        {
            strcpy(allstu.pall[i].id,s.c_str());
        }
        else if(column == 1)
        {
            strcpy(allstu.pall[i].name,s.c_str());
        }
        else if(column == 2)
        {
            allstu.pall[i].age = (char)atoi(s.c_str());
        }
        else if(column == 3)
        {
            allstu.pall[i].sex = s[0];
        }
        emit(dataChanged(index, index));
        return true;

    }
    return false;
};

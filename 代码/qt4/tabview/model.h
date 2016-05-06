
#ifndef __MODEL_H__
#define __MODEL_H__

#include <QtGui>
#include "student.h"

class mymodel : public QStandardItemModel
{
    public:
        QVariant data(const QModelIndex &index, int role) const;
        bool setData(const QModelIndex &index, const QVariant &value, int role);
        mymodel(void);
        int addstu(struct student &stu);
        int delstu(int row);
        bool upDate(void);
        bool pageUp(unsigned int &cu,unsigned int &total);
        bool pageDown(unsigned int &cu,unsigned int &total);
        bool getPages(unsigned int &cuPage,unsigned int &totalPage,unsigned int &viewNum);
    private:
        struct allstudent allstu;
        unsigned int cuPage;
        unsigned int totalPage;
        unsigned int eachPage;
};

#endif

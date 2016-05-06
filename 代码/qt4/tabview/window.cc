
#include <QtGui>
#include <iostream>
#include "model.h"
#include "window.h"

using namespace std;
mywindow::~mywindow()
{
    delete tview;
    delete smodel;
}
mywindow::mywindow()
{
    QMenu *m;
    QAction *ac;
    tview = new QTableView();
    smodel = new mymodel();
    menu = new QMenuBar(this);
    setMenuBar(menu);
    tbar = new QToolBar(this);
    addToolBar(tbar);
    status = new QStatusBar(this);
    setStatusBar(status);
    tview->setModel(smodel);
    tview->setSelectionBehavior(QAbstractItemView::SelectRows);
    tview->setContextMenuPolicy(Qt::CustomContextMenu);
    setCentralWidget(tview);
    
    acPageUp = tbar->addAction(tr("上一页"));
    connect(acPageUp,SIGNAL(triggered()),this,SLOT(pageUp()));
    acPageDown = tbar->addAction(tr("下一页"));
    connect(acPageDown,SIGNAL(triggered()),this,SLOT(pageDown()));
    acPageUp->setEnabled(false);
    acPageDown->setEnabled(false);
    
    m = menu->addMenu(tr("&Operation"));
    ac = m->addAction(tr("&Add"));
    connect(ac,SIGNAL(triggered()),this,SLOT(myadd()));
    ac = m->addAction(tr("&Del"));
    connect(ac,SIGNAL(triggered()),this,SLOT(mydel()));
    ac = m->addAction(tr("&Save"));
    connect(ac,SIGNAL(triggered()),this,SLOT(mysave()));
    ac = m->addAction(tr("&Quit"));
    connect(ac,SIGNAL(triggered()),this,SLOT(myclose()));
    m = menu->addMenu(tr("&About"));
    ac = m->addAction(tr("about this software"));
    connect(ac,SIGNAL(triggered()),this,SLOT(myabout()));
}
int mywindow::pageUp(void)
{
    unsigned int cu;
    unsigned int total;
    smodel->pageUp(cu,total);
    if(0 == cu)
    {
        acPageUp->setEnabled(false);
    }
    if(cu != total-1)
    {
        acPageDown->setEnabled(true);
    }
    smodel->upDate();
    return 0;
}
int mywindow::pageDown(void)
{
    unsigned int cu;
    unsigned int total;
    smodel->pageDown(cu,total);
    if(cu == total-1)
    {
        acPageDown->setEnabled(false);
    }
    if(0!=cu)
    {
        acPageUp->setEnabled(true);
    }
    smodel->upDate();
    return 0;
}
int mywindow::myadd(void)
{
    status->showMessage(tr("add"),200);
    struct student s;
    
    studentdlg dlg;
    if(dlg.exec() == QDialog::Accepted)
    {
        dlg.getInput(&s);
        smodel->addstu(s);
        unsigned int cuPage;
        unsigned int totalPage;
        unsigned int viewNum;
        smodel->getPages(cuPage,totalPage,viewNum);
        if(cuPage<totalPage-1)
        {
            acPageDown->setEnabled(true);
        }
        smodel->upDate();
    }
    return 0;
}
int mywindow::mydel(void)
{
    int row;
    status->showMessage(tr("del"),200);
    row = tview->currentIndex().row();
    smodel->delstu(row);
    unsigned int cuPage;
    unsigned int totalPage;
    unsigned int viewNum;
    smodel->getPages(cuPage,totalPage,viewNum);
    if(cuPage<totalPage-1)
    {
        acPageDown->setEnabled(true);
    }
    else
    {
        acPageDown->setEnabled(false);
    }
    if(0 == cuPage)
    {
        acPageUp->setEnabled(false);
    }
    else
    {
        acPageUp->setEnabled(true);
    }
    smodel->upDate();
    return 0;
}
int mywindow::mysave(void)
{
    status->showMessage(tr("save"),200);
    return 0;
}
int mywindow::myclose(void)
{
    status->showMessage(tr("quit"));
    close();
    return 0;
}
int mywindow::myabout(void)
{
    status->showMessage(tr("about"),2000);
    return 0;
}

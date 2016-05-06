#include "mywindow.h"
#include <iostream>
#include <fstream>
using namespace std;

MyWindow::MyWindow(void)
{
    QMenu *m;
    QAction *ac;
    text = new QTextEdit(this);
    menu = new QMenuBar(this);
    m = menu->addMenu(tr("&File"));
    ac = m->addAction(tr("&open"));
    connect(ac,SIGNAL(triggered()),this,SLOT(myopen()));
    ac = m->addAction(tr("&save"));
    connect(ac,SIGNAL(triggered()),this,SLOT(mysave()));
    ac = m->addAction(tr("&close"));
    connect(ac,SIGNAL(triggered()),this,SLOT(myclose()));
    menu->addMenu(tr("&edit"));
    setCentralWidget(text);
    setMenuBar(menu);
    fname = "";
}
MyWindow::~MyWindow()
{
    return;
}

int MyWindow::myopen(void)
{
    ifstream in;
    string str;
    QString s;
    char ch;
    s = QFileDialog::getOpenFileName(this,tr("Open text files"),".",
                tr("text files(*.txt);;all(*)"));
    if(s.size() == 0)
    {
        return 0;
    }
    fname = s.toAscii().data();
    in.open(fname.c_str(),ios::in);
    if(in.is_open())
    {
        text->setText("");
        while(in.get(ch))
        {
            str += ch;
        }
        in.close();
        text->append(str.c_str());
    }
    else
    {
        cout<<"error when open file:"<<fname<<endl;
    }
    return 0;
}
int MyWindow::myclose(void)
{
    fname="";
    text->setText("");
    return 0;
}
int MyWindow::mysave(void)
{
    ofstream out;
    QString s;
    s = text->toPlainText();
    if(fname.size() == 0)
    {
        return 0;
    }
    out.open(fname.c_str(),ios::out);
    if(out.is_open())
    {
        out<<s.toAscii().data();
        out.close();
    }
    else
    {
        cout<<"open file failed:"<<fname<<endl;
    }
    return 0;
}

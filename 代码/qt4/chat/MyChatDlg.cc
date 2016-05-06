#include "MyChatDlg.h"
#include <iostream>
using namespace std;
MyChatDlg::MyChatDlg(QWidget *parent,Qt::WindowFlags flags):QDialog(parent,flags)
{
    QVBoxLayout *mLay = new QVBoxLayout;
    history = new QTextEdit;
    chat    = new QTextEdit;
    send = new QPushButton(tr("发送"));
    mLay->addWidget(history);
    mLay->addWidget(chat);
    mLay->addWidget(send);
    setLayout(mLay);
    
    QObject::connect(send,SIGNAL(clicked()),this,SLOT(mysend()));
};
void MyChatDlg::mysend(void)
{
    QString s = chat->toPlainText();
    emit(sendMsg(this,s));
    history->append(s);
	chat->setText(QString(""));
    return ;
}
void MyChatDlg::myappend(QString & s)
{
    history->append(s);
    return ;
}
void MyChatDlg::dragEnterEvent(QDragEnterEvent * event)
{
    if(event->minedata() ->hasFormat("text/uri-list"))
    {
        event->acceptProposeAction();
    }
}
void MyChatDlg::dropEvent(QDropEvent *event)
{
    QList<QUrl >urls = event->mineData()->urls();
    if(urls.isEmpty())
    {
        return ;
    }
    QString filename = urls.first().toLocalFile();
    if(fileName.isEmpty())
    {
        return;
    }
    QMessageBox box;
    box.setText(filename);
    box.exec();
}

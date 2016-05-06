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
    history->setAcceptDrops(false);  
    chat->setAcceptDrops(false);
    setAcceptDrops(true);  
};
void MyChatDlg::showMsg(QString &s)
{
    history->append(s);
}
int MyChatDlg::mysend(void)
{
    QString msg = chat->toPlainText();
    cout<<msg.toStdString()<<endl;
    if(msg.size() == 0)
    {
        QMessageBox box;
        box.setText(tr("不能发送空消息"));
        box.exec();
        return 0;
    }
    QString s1("send to "); 
    s1 += windowTitle();
    history->append(s1);
    history->append(msg);
    emit sendMsg(this,msg,false);
    chat->setText("");
    return 0;
}
void MyChatDlg::dragEnterEvent(QDragEnterEvent *event)  
{  
    if (event->mimeData()->hasFormat("text/uri-list")) 
    {  
        event->acceptProposedAction();  
    }  
}
void MyChatDlg::dropEvent(QDropEvent *event)  
{  
    QList<QUrl> urls = event->mimeData()->urls();  
    if (urls.isEmpty()) 
    {  
        return;  
    }  
 
    QString fileName = urls.first().toLocalFile();  
    if (fileName.isEmpty()) 
    {  
        return;
    }
    FILE *fp = fopen(fileName.toStdString().c_str(),"r");
    if(NULL == fp)
    {
        QMessageBox box;
        box.setText(tr("文件打开失败"));
        box.exec();
        return;
    }
    fseek(fp,0,SEEK_END);
    long len = ftell(fp);
    if(len <= 0)
    {
        QMessageBox box;
        box.setText(tr("不能发送空文件"));
        box.exec();
        goto end;
    }
    emit sendMsg(this,fileName,true);
end:
    fclose(fp);
}
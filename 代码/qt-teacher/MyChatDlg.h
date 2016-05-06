#ifndef __MYCHATDLG_H__
#define __MYCHATDLG_H__

#include <QtGui>

class MyChatDlg :public QDialog
{
    Q_OBJECT
private:
    QTextEdit *history;
    QTextEdit *chat;
    QPushButton *send;
protected:  
    void dragEnterEvent(QDragEnterEvent *event);  
    void dropEvent(QDropEvent *event);  
signals:
    int sendMsg(MyChatDlg *chatDlg,QString &msg);
public slots:
    int mysend(void);
public:
    MyChatDlg(QWidget *parent = 0,Qt::WindowFlags flags = 0);
    void showMsg(QString &s);
};

#endif
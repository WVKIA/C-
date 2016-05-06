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
signals:
    int sendInfor(QString );
    int sendMsg(MyChatDlg *,QString &);
public slots:
    
    void mysend(void);
public:
    MyChatDlg(QWidget *parent = 0,Qt::WindowFlags flags = 0);
    void myappend(QString &);
};

#endif

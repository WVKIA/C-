
#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <QtGui>
#include "model.h"
#include "studentdlg.h"
class mywindow : public QMainWindow
{
    Q_OBJECT
    public:
        mywindow(void);
        ~mywindow();
    public slots:
        int myadd(void);
        int mydel(void);
        int mysave(void);
        int myclose(void);
        int myabout(void);
        int pageUp(void);
        int pageDown(void);
    private:
        QTableView *tview;
        mymodel *smodel;
        QMenuBar *menu;
        QToolBar *tbar;
        QStatusBar *status;
        QAction *acPageUp;
        QAction *acPageDown;
};

#endif

#include "mywindow.h"
#include <iostream>
#include <fstream>
using namespace std;

MyWindow::MyWindow(QString s)
{
    QMenu *m;
    QAction *ac;
    video = new QWidget(this);
    menu = new QMenuBar(this);
    m = menu->addMenu(tr("&File"));
    ac = m->addAction(tr("&open"));
    connect(ac,SIGNAL(triggered()),this,SLOT(myopen()));
    ac = m->addAction(tr("&close"));
    connect(ac,SIGNAL(triggered()),this,SLOT(myclose()));
    menu->addMenu(tr("&play"));
    setCentralWidget(video);
    setMenuBar(menu);
    fname = s;
    
    setWindowTitle("videoPlayer");
    mediaObject = new Phonon::MediaObject(video);
    Phonon::VideoWidget *videoWidget = new Phonon::VideoWidget(video);
    Phonon::createPath(mediaObject,videoWidget);
    Phonon::AudioOutput *audioOutput =
        new Phonon::AudioOutput(Phonon::VideoCategory,video);
    Phonon::createPath(mediaObject, audioOutput);
    play();
    show();
}
MyWindow::~MyWindow()
{
    return;
}

int MyWindow::myopen(void)
{
    fname = QFileDialog::getOpenFileName(this,tr("Open text files"),".",
                tr("video(*.mp4 *.mpg *.rmvb);;all(*.*)"));
    std::cout<<fname.toStdString();
    play();
    return 0;
}
int MyWindow::myclose(void)
{
    close();
    return 0;
}
int MyWindow::play(void)
{
//    QUrl url(fname);
    Phonon::MediaSource source(fname);
    mediaObject->setCurrentSource(source);
    mediaObject->play();
    return 0;
}

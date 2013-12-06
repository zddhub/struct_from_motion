#include "readthread.h"

ReadThread::ReadThread(MeshWidget *mw, QObject *parent) :
    QThread(parent)
{
    meshWidget = mw;
}

void ReadThread::setFilename(const QString &filename)
{
    fileName = filename;
}

void ReadThread::run()
{
    meshWidget->readObj(fileName.toLocal8Bit().data());
}

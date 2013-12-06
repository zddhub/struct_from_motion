#ifndef READTHREAD_H
#define READTHREAD_H

#include <QThread>
#include "meshwidget/meshwidget.h"
using namespace zdd;

class ReadThread : public QThread
{
    Q_OBJECT
public:
    explicit ReadThread(MeshWidget *mw, QObject *parent = 0);
    void setFilename(const QString &filename);
    void run();
signals:
    
public slots:
private:
    MeshWidget *meshWidget;
    QString fileName;
};

#endif // READTHREAD_H

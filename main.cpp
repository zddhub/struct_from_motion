/*******************************************
# Struct from motion
# Project created by QtCreator 5.1
# Author: zdd
# Email: zddmail@gmail.com / zddhub@gmail.com
#
********************************************/


#include "mainwindow.h"
#include <QApplication>

#include "waitingdialog.h"
#include "meshwidget/meshwindow.h"
#include "progressindicator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.showMaximized();

    return a.exec();
}

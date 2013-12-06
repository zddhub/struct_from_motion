/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen_Images;
    QAction *actionOpen_Left_Image;
    QAction *actionOpen_Right_Image;
    QAction *actionDisparityMap;
    QAction *actionReconstruct_3D;
    QAction *actionDepth_Map;
    QAction *actionCreate_3D;
    QAction *action3D_View;
    QAction *actionAbout;
    QAction *actionUsage;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuSFM;
    QMenu *menuStereo;
    QMenu *menuView;
    QMenu *menuAbout;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(800, 600);
        MainWindow->setMinimumSize(QSize(800, 600));
        actionOpen_Images = new QAction(MainWindow);
        actionOpen_Images->setObjectName(QStringLiteral("actionOpen_Images"));
        actionOpen_Images->setEnabled(false);
        actionOpen_Left_Image = new QAction(MainWindow);
        actionOpen_Left_Image->setObjectName(QStringLiteral("actionOpen_Left_Image"));
        actionOpen_Right_Image = new QAction(MainWindow);
        actionOpen_Right_Image->setObjectName(QStringLiteral("actionOpen_Right_Image"));
        actionDisparityMap = new QAction(MainWindow);
        actionDisparityMap->setObjectName(QStringLiteral("actionDisparityMap"));
        actionReconstruct_3D = new QAction(MainWindow);
        actionReconstruct_3D->setObjectName(QStringLiteral("actionReconstruct_3D"));
        actionReconstruct_3D->setEnabled(false);
        actionDepth_Map = new QAction(MainWindow);
        actionDepth_Map->setObjectName(QStringLiteral("actionDepth_Map"));
        actionCreate_3D = new QAction(MainWindow);
        actionCreate_3D->setObjectName(QStringLiteral("actionCreate_3D"));
        actionCreate_3D->setEnabled(false);
        action3D_View = new QAction(MainWindow);
        action3D_View->setObjectName(QStringLiteral("action3D_View"));
        action3D_View->setCheckable(true);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionUsage = new QAction(MainWindow);
        actionUsage->setObjectName(QStringLiteral("actionUsage"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuSFM = new QMenu(menuBar);
        menuSFM->setObjectName(QStringLiteral("menuSFM"));
        menuStereo = new QMenu(menuBar);
        menuStereo->setObjectName(QStringLiteral("menuStereo"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        menuAbout = new QMenu(menuBar);
        menuAbout->setObjectName(QStringLiteral("menuAbout"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuSFM->menuAction());
        menuBar->addAction(menuStereo->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuAbout->menuAction());
        menuFile->addAction(actionOpen_Left_Image);
        menuFile->addAction(actionOpen_Right_Image);
        menuFile->addSeparator();
        menuFile->addAction(actionOpen_Images);
        menuSFM->addAction(actionReconstruct_3D);
        menuStereo->addAction(actionDisparityMap);
        menuStereo->addAction(actionDepth_Map);
        menuStereo->addAction(actionCreate_3D);
        menuView->addAction(action3D_View);
        menuAbout->addAction(actionUsage);
        menuAbout->addAction(actionAbout);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Stereo -- zdd", 0));
        actionOpen_Images->setText(QApplication::translate("MainWindow", "Open Images", 0));
        actionOpen_Left_Image->setText(QApplication::translate("MainWindow", "Open Left Image", 0));
        actionOpen_Right_Image->setText(QApplication::translate("MainWindow", "Open Right Image", 0));
        actionDisparityMap->setText(QApplication::translate("MainWindow", "Disparity Map", 0));
        actionReconstruct_3D->setText(QApplication::translate("MainWindow", "Reconstruct 3D", 0));
        actionDepth_Map->setText(QApplication::translate("MainWindow", "Depth Map", 0));
        actionCreate_3D->setText(QApplication::translate("MainWindow", "Create 3D", 0));
        action3D_View->setText(QApplication::translate("MainWindow", "3D View", 0));
        actionAbout->setText(QApplication::translate("MainWindow", "About Stereo", 0));
        actionUsage->setText(QApplication::translate("MainWindow", "Usage", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuSFM->setTitle(QApplication::translate("MainWindow", "SFM", 0));
        menuStereo->setTitle(QApplication::translate("MainWindow", "Stereo", 0));
        menuView->setTitle(QApplication::translate("MainWindow", "View", 0));
        menuAbout->setTitle(QApplication::translate("MainWindow", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

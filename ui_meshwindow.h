/********************************************************************************
** Form generated from reading UI file 'meshwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESHWINDOW_H
#define UI_MESHWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MeshWindow
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionDefault;
    QAction *actionPoints;
    QAction *actionWireframe;
    QAction *actionReset_View;
    QAction *actionWireframe_color;
    QAction *actionWireframe_light;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuRenderer;
    QMenu *menuView;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MeshWindow)
    {
        if (MeshWindow->objectName().isEmpty())
            MeshWindow->setObjectName(QStringLiteral("MeshWindow"));
        MeshWindow->resize(800, 600);
        actionOpen = new QAction(MeshWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(MeshWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionDefault = new QAction(MeshWindow);
        actionDefault->setObjectName(QStringLiteral("actionDefault"));
        actionDefault->setCheckable(true);
        actionPoints = new QAction(MeshWindow);
        actionPoints->setObjectName(QStringLiteral("actionPoints"));
        actionPoints->setCheckable(true);
        actionWireframe = new QAction(MeshWindow);
        actionWireframe->setObjectName(QStringLiteral("actionWireframe"));
        actionWireframe->setCheckable(true);
        actionReset_View = new QAction(MeshWindow);
        actionReset_View->setObjectName(QStringLiteral("actionReset_View"));
        actionWireframe_color = new QAction(MeshWindow);
        actionWireframe_color->setObjectName(QStringLiteral("actionWireframe_color"));
        actionWireframe_color->setCheckable(true);
        actionWireframe_light = new QAction(MeshWindow);
        actionWireframe_light->setObjectName(QStringLiteral("actionWireframe_light"));
        centralwidget = new QWidget(MeshWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        MeshWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MeshWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuRenderer = new QMenu(menubar);
        menuRenderer->setObjectName(QStringLiteral("menuRenderer"));
        menuView = new QMenu(menubar);
        menuView->setObjectName(QStringLiteral("menuView"));
        MeshWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MeshWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MeshWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuRenderer->menuAction());
        menubar->addAction(menuView->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuRenderer->addAction(actionDefault);
        menuRenderer->addAction(actionPoints);
        menuRenderer->addAction(actionWireframe);
        menuRenderer->addAction(actionWireframe_light);
        menuRenderer->addAction(actionWireframe_color);
        menuView->addAction(actionReset_View);

        retranslateUi(MeshWindow);

        QMetaObject::connectSlotsByName(MeshWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MeshWindow)
    {
        MeshWindow->setWindowTitle(QApplication::translate("MeshWindow", "MeshView -- zdd", 0));
        actionOpen->setText(QApplication::translate("MeshWindow", "Open", 0));
        actionSave->setText(QApplication::translate("MeshWindow", "Save", 0));
        actionDefault->setText(QApplication::translate("MeshWindow", "Default", 0));
        actionPoints->setText(QApplication::translate("MeshWindow", "Points", 0));
        actionWireframe->setText(QApplication::translate("MeshWindow", "Wireframe", 0));
        actionReset_View->setText(QApplication::translate("MeshWindow", "Reset View", 0));
        actionWireframe_color->setText(QApplication::translate("MeshWindow", "Wireframe (color)", 0));
        actionWireframe_light->setText(QApplication::translate("MeshWindow", "Wireframe (light)", 0));
        menuFile->setTitle(QApplication::translate("MeshWindow", "File", 0));
        menuRenderer->setTitle(QApplication::translate("MeshWindow", "Renderer", 0));
        menuView->setTitle(QApplication::translate("MeshWindow", "View", 0));
    } // retranslateUi

};

namespace Ui {
    class MeshWindow: public Ui_MeshWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESHWINDOW_H

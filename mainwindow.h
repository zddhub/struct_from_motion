#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mdichild.h"
#include "meshwidget/meshwindow.h"

typedef float pixel_t;

#include <QMainWindow>
#include <QMdiArea>
#include <QMdiSubWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_actionOpen_Images_triggered();

    void on_actionOpen_Left_Image_triggered();

    void on_actionOpen_Right_Image_triggered();

    void on_actionDisparityMap_triggered();

    void on_actionReconstruct_3D_triggered();

    void on_actionDepth_Map_triggered();

    void on_actionCreate_3D_triggered();

    void on_action3D_View_triggered();
    void on_actionAbout_triggered();

    void on_actionUsage_triggered();

private:
    MdiChild* createMdiChild(MdiChild::WindowType wt);
    MdiChild *createMdiChild();
    void setActiveSubWindow(QWidget *window);
    MdiChild* activeMdiChild();
    QMdiSubWindow* findMdiChild(MdiChild::WindowType wt);

private:
    void setColors(std::vector<uvec3> &colors);
private:
    Ui::MainWindow *ui;
    QMdiArea *mdiArea;

    MdiChild *leftWindow;
    MdiChild *rightWindow;

    MdiChild *matchWindow;
    MdiChild *depthWindow;

    MdiChild *disparityWindow;

    cv::Mat leftImage;
    cv::Mat rightImage;

    cv::Mat disparity;
    cv::Mat depthMap;//
    bool hadDepthMap;

    double Zf;
    double d;

    TriangleMesh *mesh;
    MeshWindow *meshWindow;
    QDockWidget *meshDockWidget;

    std::vector<cv::Mat> images;
    std::vector<std::string> images_names;
};

#endif // MAINWINDOW_H

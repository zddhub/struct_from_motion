#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "algo.h"
#include "meshwidget/meshwindow.h"
#include "triangulationstrategy.h"

#include <QFileDialog>
#include <QMessageBox>

using cv::imread;
using cv::Mat;
using namespace zdd;

#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainToolBar->hide();

    mdiArea = new QMdiArea;
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->setCentralWidget(mdiArea);

    leftWindow = 0;
    rightWindow = 0;

    Zf = 869.0;
    d = 60;

    hadDepthMap = false;
    mesh = new TriangleMesh();

    meshWindow = new MeshWindow;
    meshDockWidget = new QDockWidget;

    meshDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
    meshDockWidget->setWindowTitle(tr("^ Drag up for larger view ^"));
    meshWindow->setMinimumHeight(400);//set meshDockWidget height, zdd will change ... :)
    meshDockWidget->setWidget(meshWindow);
    addDockWidget(Qt::BottomDockWidgetArea, meshDockWidget);
    meshDockWidget->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mdiArea;
    delete meshWindow;
}

MdiChild* MainWindow::createMdiChild()
{
    MdiChild *child = new MdiChild;

    //获取子窗口，在MdiChild类中根据图片改变子窗口大小
    QMdiSubWindow *childWindow = mdiArea->addSubWindow(child);
    child->setWindow(childWindow);//

    return child;
}

MdiChild* MainWindow::createMdiChild(MdiChild::WindowType wt)
{
    QMdiSubWindow *existing = findMdiChild(wt);
    if(existing)
    {
        MdiChild *child = qobject_cast<MdiChild *>(existing->widget());
        return child;
    }
    else
    {
        MdiChild *child = createMdiChild();
        child->setWindowType(wt);
        return child;
    }
}

void MainWindow::setActiveSubWindow(QWidget *window)
{
    if (!window)
        return;
    mdiArea->setActiveSubWindow(qobject_cast<QMdiSubWindow *>(window));
}

MdiChild* MainWindow::activeMdiChild()
{
    if (QMdiSubWindow *activeSubWindow = mdiArea->activeSubWindow())
        return qobject_cast<MdiChild *>(activeSubWindow->widget());
    return 0;
}

QMdiSubWindow* MainWindow::findMdiChild(MdiChild::WindowType wt)
{
    foreach (QMdiSubWindow *window, mdiArea->subWindowList()) {
        MdiChild *mdiChild = qobject_cast<MdiChild *>(window->widget());
        if (mdiChild->getWindowType() == wt)
            return window;
    }
    return 0;
}

void MainWindow::on_actionOpen_Images_triggered()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this,
                                                    tr("Open Images"),
                                                    QDir::currentPath(),
                                                    "Image Files (*.png *.jpg *.bmp)");
    if(fileNames.isEmpty())
        return;
    images.clear();
    images_names.clear();

    QStringList::Iterator it = fileNames.begin();

    while(it != fileNames.end()) {

        Mat mat = imread((*it).toLocal8Bit().data());
        if(!mat.data)
        {
            ++it;
            continue;
        }

        images.push_back(mat);
        images_names.push_back((*it).toLocal8Bit().data());

        MdiChild *child = createMdiChild();

        if(child)
        {
            child->showMatImage(mat);
            child->setWindowTitle((*it).toLocal8Bit().data());
            this->setActiveSubWindow(child);
        }

        ++it;
     }
}

void MainWindow::on_actionOpen_Left_Image_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Left Image"),
                                                    QDir::currentPath(),
                                                    "Image Files (*.png *.jpg *.bmp)");
    if (!fileName.isEmpty())
    {
        leftImage = imread(fileName.toLocal8Bit().data());

        QMdiSubWindow *leftWindowExisting = findMdiChild(MdiChild::LeftWindow);

        if(leftWindowExisting)
        {
            leftWindow->showMatImage(leftImage);
            leftWindow->setWindowTitle(tr("Left: %1").arg(fileName));

            mdiArea->setActiveSubWindow(leftWindowExisting);
        }
        else
        {
            leftWindow = createMdiChild();
            leftWindow->setWindowType(MdiChild::LeftWindow);

            if(leftWindow)
            {
                leftWindow->showMatImage(leftImage);
                leftWindow->setWindowTitle(tr("Left: %1").arg(fileName));

                this->setActiveSubWindow(leftWindow);
            }
        }
    }
}

void MainWindow::on_actionOpen_Right_Image_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Right Image"),
                                                    QDir::currentPath(),
                                                    "Image Files (*.png *.jpg *.bmp)");
    if (!fileName.isEmpty())
    {
        rightImage = imread(fileName.toLocal8Bit().data());

        QMdiSubWindow *rightWindowExisting = findMdiChild(MdiChild::RightWindow);

        if(rightWindowExisting)
        {
            rightWindow->showMatImage(rightImage);
            rightWindow->setWindowTitle(tr("Right: %1").arg(fileName));

            mdiArea->setActiveSubWindow(rightWindowExisting);
        }
        else
        {
            rightWindow = createMdiChild();
            rightWindow->setWindowType(MdiChild::RightWindow);

            if(rightWindow)
            {
                rightWindow->showMatImage(rightImage);
                rightWindow->setWindowTitle(tr("Right: %1").arg(fileName));

                this->setActiveSubWindow(rightWindow);
            }
        }
    }
}

static void writeToObj(vector<cv::Point3d>& pointCould, const QString& fileName)
{
    QFile file(fileName);
    file.open(QFile::WriteOnly);

    QTextStream ts(&file);
    for(int i = 0; i < pointCould.size(); i++)
    {
        ts << "v " << pointCould[i].x << " " << pointCould[i].y << " " << pointCould[i].z <<endl;
    }

    file.close();
}

void MainWindow::on_actionReconstruct_3D_triggered()
{
    if(images.size() < 2)
    {
        QMessageBox::critical(this, tr("Error"), tr("Please open at least two images"));
        return;
    }


}

void MainWindow::on_actionDisparityMap_triggered()
{
    if(!findMdiChild(MdiChild::LeftWindow) || !findMdiChild(MdiChild::RightWindow))
    {
        QMessageBox::critical(this, tr("Error"), tr("Left or Right image can not opened!"));
        this->statusBar()->showMessage( tr("Left or Right image can not opened!"));
        return;
    }

    cv::Mat disparity;
    double minVal, maxVal;
    if(!getDisparity(leftImage, rightImage, disparity, minVal, maxVal))
    {
        QMessageBox::critical(this, tr("Error"),
                              tr("Please make sure that left image and right image have the same size"));
        this->statusBar()->showMessage( tr("compute disparity error."));
        return;
    }

    //imwrite("disparity.jpg", disparity);
    Mat disparity8U = Mat( disparity.rows, disparity.cols, CV_8UC1 );
    disparity.convertTo(disparity8U, CV_8UC1, 255/(maxVal - minVal));

    disparityWindow = createMdiChild(MdiChild::DisparityWindow);
    //disparityWindow->setWindowTitle(tr("Disparity -- minVal: %1 maxVal: %2").arg(minVal).arg(maxVal));
    disparityWindow->setWindowTitle(tr("Disparity"));
    disparityWindow->showMatImage(disparity8U);

    this->setActiveSubWindow(disparityWindow);
}

//test
static void makeGray(cv::Mat &gray)
{
    gray = cv::Mat::zeros(255, 255, CV_8U);

    uchar *data = (uchar*)gray.data;
    int step = gray.step/sizeof(data[0]);

    for(int  j = 0; j < gray.cols; j++)
    {
        for(int i = 0; i < gray.rows; i++)
        {
            *(data + step * i + j) = (uchar)i;
        }
    }
}

void MainWindow::on_actionDepth_Map_triggered()
{
    if(!findMdiChild(MdiChild::LeftWindow) || !findMdiChild(MdiChild::RightWindow))
    {
        QMessageBox::critical(this, tr("Error"), tr("Left or Right image can not opened!"));
        this->statusBar()->showMessage( tr("Left or Right image can not opened!"));
        return;
    }

    double minVal, maxVal;
    if(!getDisparity(leftImage, rightImage, disparity, minVal, maxVal))
    {
        QMessageBox::critical(this, tr("Error"),
                              tr("Please make sure that left image and right image have the same size"));
        this->statusBar()->showMessage( tr("compute disparity error."));
        return;
    }

    //cout << "disparity type: " << disparity.type() << " channels: "<< disparity.channels()<<endl;

    cv::Mat depth;
    disparity.copyTo(depth);

    pixel_t *data = (pixel_t*) depth.data;
    int step = depth.step/sizeof(data[0]);


    if(fabs(data[0] + d) < 1e-5)
    {
        QMessageBox::critical(this, tr("Error"), tr("Floating point division by zero. Try increasing d."));
        this->statusBar()->showMessage( tr("Depth Map Error"));
        return;
    }
    else
    {
        maxVal = minVal = (-Zf/(data[0] + d));
    }

    for(int  j = 0; j < depth.cols; j++)
    {
        for(int i = 0; i < depth.rows; i++)
        {
            pixel_t disp = *(data + step * i + depth.channels() *j);

            if(fabs((disp + d)) < 1e-5)
            {
                QMessageBox::critical(this, tr("Error"), tr("Floating point division by zero. Try increasing d."));
                this->statusBar()->showMessage( tr("Depth Map Error"));
                return;
            }

            double Zp = (-Zf/(disp + d));

            if(maxVal < Zp)
                maxVal = Zp;
            if(minVal > Zp)
                minVal = Zp;

            *(data + step * i + depth.channels() *j) = (pixel_t)Zp;

            //mesh->vertices.push_back(vec((float)i/((disp + d)), (float)j/(disp + d), (float)Zp));
        }
    }

    depthMap = depth;
    hadDepthMap = true;
    ui->actionCreate_3D->setEnabled(true);

    //可视化
    Mat depth8U = Mat( depth.rows, depth.cols, CV_8UC1 );
    depth.convertTo(depth8U, CV_8UC1, 255/(maxVal - minVal), -255*minVal/(maxVal-minVal)); //

    Mat depth8UC3;
    gray2PseudoColor(depth8U, depth8UC3);

    depthWindow = createMdiChild(MdiChild::DepthWindow);
    //depthWindow->setWindowTitle(tr("Depth Map -- minVal: %1 maxVal: %2").arg(minVal).arg(maxVal));
    depthWindow->setWindowTitle(tr("Depth Map"));
    depthWindow->showMatImage(depth8UC3);
}

void MainWindow::setColors(std::vector<uvec3>& colors)
{
    if(leftImage.empty())
        return;
    if(leftImage.channels() != 3 || leftImage.type() != CV_8UC3)
        return;

    if(leftImage.rows < 2 || leftImage.cols < 2)
        return;

    uchar *data = (uchar*) leftImage.data;
    int step = leftImage.step/sizeof(data[0]);

    //设置顶点
    for(int i = 0; i < leftImage.rows; i++)
    {
        for(int  j = 0; j < leftImage.cols; j++)
        {
            //注意：此处的取深度时，图像空间坐标系上的点(i,j)转换到世界坐标系时,z = data[i][COLS-j].
            //详见trianglationstrategy.cpp
            uchar b = *(data + step * i + leftImage.channels() *(leftImage.cols - j) + 0);
            uchar g = *(data + step * i + leftImage.channels() *(leftImage.cols - j) + 1);
            uchar r = *(data + step * i + leftImage.channels() *(leftImage.cols - j) + 2);

            colors.push_back(uvec3(r, g, b));
        }
    }
}

void MainWindow::on_actionCreate_3D_triggered()
{
    if(!hadDepthMap)
        return;

    this->statusBar()->showMessage(tr("Creating 3D ..."));
    if(mesh)
    {
        delete mesh;
        mesh = new TriangleMesh();
    }

    TriangulationStrategy::disparityMapToTriMesh(disparity, Zf, d, *mesh);

    //MeshWindow *mw = new MeshWindow();
    meshWindow->setMesh(mesh);
    this->setColors(meshWindow->getColors());
    meshWindow->updateGL();

    this->statusBar()->showMessage(tr("Creating 3D ... Done."));
    hadDepthMap = false;
    ui->actionCreate_3D->setEnabled(false);

    ui->action3D_View->setChecked(true);
    meshDockWidget->show();
}

void MainWindow::on_action3D_View_triggered()
{
    if(ui->action3D_View->isChecked())
        meshDockWidget->show();
    else
        meshDockWidget->hide();
}

void MainWindow::on_actionAbout_triggered()
{
    QString text = "struct from motion (beta version)\r\n" \
            "zdd zddmail@gmail.com";
    QMessageBox::about(this, tr("About"),
                       tr("%1").arg(text));
}

void MainWindow::on_actionUsage_triggered()
{
    QString text =  "Usage: \r\n\r\n" \
    "1、Open left and right image.  (File->Open Left Image、File->Open Right Image)\r\n" \

    "2、Get Depth Map (Stereo->Depth Map)\r\n" \

    "3、Create 3D. (Stereo->Create 3D, make sure click Stereo->Depth Map first.)\r\n" \

    "4、View->3D view : open/close 3Dview, Drag up for larger view.\r\n\r\n" \

    "zdd\r\n" \
    "zddmail@gmail.com\r\n";
    QMessageBox::about(this, tr("Usage"),
                       tr("%1").arg(text));
}

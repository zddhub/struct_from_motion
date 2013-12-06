#include "meshwindow.h"
#include "ui_meshwindow.h"

#include <QFileDialog>
#include <QMessageBox>

MeshWindow::MeshWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MeshWindow)
{
    ui->setupUi(this);
    ui->actionDefault->setChecked(true);

    mw = new MeshWidget();
    this->setCentralWidget(mw);
}

MeshWindow::~MeshWindow()
{
    delete ui;
}

void MeshWindow::setMesh(TriangleMesh *mesh)
{
    mw->setMesh(mesh);
}

std::vector<uvec3>& MeshWindow::getColors()
{
    return mw->getTriMesh()->colors;
}

bool MeshWindow::readObj(const char *filename)
{
    return mw->readObj(filename);
}

bool MeshWindow::saveObj(const char *filename)
{
    return mw->writeObj(filename);
}

void MeshWindow::on_actionOpen_triggered()
{ 
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Obj"),
                                                    QDir::currentPath(),
                                                    "File(*.obj *.OBJ)");
    if (!fileName.isEmpty())
    {
        this->statusBar()->showMessage(tr("Opening %1 ...").arg(fileName));
        readObj(fileName.toLocal8Bit().data());
        this->statusBar()->showMessage(tr("Opening %1 ... Done.").arg(fileName));
    }
}

void MeshWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save Obj"),
                                                    QDir::currentPath(),
                                                    "File(*.obj)");
    if(!fileName.isEmpty())
    {
        if(fileName.size()<=4 || (fileName.right(4)!=".obj" && fileName.right(4)!=".OBJ"))
            fileName += ".obj";
        this->statusBar()->showMessage(tr("Saving %1 ...").arg(fileName));
        if(saveObj(fileName.toLocal8Bit().data()))
            this->statusBar()->showMessage(tr("Saving %1 ... Done.").arg(fileName));
        else
        {
            QMessageBox::critical(this, tr("Error"), tr("save file %1 error").arg(fileName));
            this->statusBar()->showMessage(tr("Saving %1 ... Error.").arg(fileName));
        }
    }
}

void MeshWindow::on_actionDefault_triggered()
{
    mw->setRendererType(MeshWidget::Default);
    ui->actionDefault->setChecked(true);
    ui->actionPoints->setChecked(false);
    ui->actionWireframe->setChecked(false);
    ui->actionWireframe_color->setChecked(false);
    ui->actionWireframe_light->setChecked(false);

    mw->update();
}

void MeshWindow::on_actionPoints_triggered()
{
    mw->setRendererType(MeshWidget::Points);
    ui->actionDefault->setChecked(false);
    ui->actionPoints->setChecked(true);
    ui->actionWireframe->setChecked(false);
    ui->actionWireframe_color->setChecked(false);
    ui->actionWireframe_light->setChecked(false);

    mw->update();
}

void MeshWindow::on_actionWireframe_triggered()
{
    mw->setRendererType(MeshWidget::Wireframe);
    ui->actionDefault->setChecked(false);
    ui->actionPoints->setChecked(false);
    ui->actionWireframe->setChecked(true);
    ui->actionWireframe_color->setChecked(false);
    ui->actionWireframe_light->setChecked(false);

    mw->update();
}

void MeshWindow::on_actionWireframe_color_triggered()
{
    mw->setRendererType(MeshWidget::WireframeWithColor);
    ui->actionDefault->setChecked(false);
    ui->actionPoints->setChecked(false);
    ui->actionWireframe->setChecked(false);
    ui->actionWireframe_color->setChecked(true);
    ui->actionWireframe_light->setChecked(false);

    mw->update();
}

void MeshWindow::on_actionReset_View_triggered()
{
    mw->resetView();

    mw->update();
}

void MeshWindow::on_actionWireframe_light_triggered()
{
    mw->setRendererType(MeshWidget::WireframeWithLight);
    ui->actionDefault->setChecked(false);
    ui->actionPoints->setChecked(false);
    ui->actionWireframe->setChecked(false);
    ui->actionWireframe_color->setChecked(false);
    ui->actionWireframe_light->setChecked(true);

    mw->update();
}

void MeshWindow::updateGL()
{
    mw->update();
}

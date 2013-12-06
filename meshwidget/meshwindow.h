#ifndef MESHWINDOW_H
#define MESHWINDOW_H

#include <QMainWindow>
#include "meshwidget.h"


using namespace zdd;

namespace Ui {
class MeshWindow;
}

class MeshWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MeshWindow(QWidget *parent = 0);
    ~MeshWindow();
    void setMesh(TriangleMesh *mesh);
    bool readObj(const char *filename);
    bool saveObj(const char *filename);
    std::vector<uvec3>& getColors();
    void updateGL();

private slots:
    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionDefault_triggered();

    void on_actionPoints_triggered();

    void on_actionWireframe_triggered();

    void on_actionWireframe_color_triggered();

    void on_actionReset_View_triggered();

    void on_actionWireframe_light_triggered();

private:
    Ui::MeshWindow *ui;
    MeshWidget *mw;
};

#endif // MESHWINDOW_H

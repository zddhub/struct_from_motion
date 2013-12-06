#ifndef TRIMESHVIEW_H
#define TRIMESHVIEW_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QTimer>

#include "trianglemesh.h"
#include "XForm.h"
#include "GLCamera.h"

using namespace std;

class TriMeshView : public QGLWidget
{
    Q_OBJECT
public:
    explicit TriMeshView(QWidget *parent = 0);
    ~TriMeshView();
    TriangleMesh *getTriMesh() {return triMesh; }
protected:
    bool readMesh(const char *filename, const char* xffilename = "");
signals:

public slots:
    void autospin();
protected:
    void cls();

    void resizeGL(int width, int height);
    void paintGL();

    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *e);

private:
    virtual void drawMesh();

protected:
    TriangleMesh *triMesh;

    xform xf;
    GLCamera camera;
    point viewpos;//当前视点位置

    QTimer *timer;
};

#endif // TRIMESHVIEW_H

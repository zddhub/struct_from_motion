
#include "trimeshview.h"

#include <QFile>
#include <QTextStream>

//输出数据_测试用
static void write_to_file(const vector<float> &v, QString filename)
{
    QFile file(filename);
    file.open(QFile::WriteOnly);

    QTextStream out(&file);

    for(unsigned int i = 0; i < v.size(); i++)
    {
        out << v[i] - 1.0f << " ";
    }
    out <<"\r\n";

    file.close();
}

TriMeshView::TriMeshView(QWidget *parent) :
    QGLWidget(parent)
{
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setSizePolicy(sizePolicy);

    this->timer = new QTimer(this);
    timer->start(1);
    connect(this->timer, SIGNAL(timeout()), this, SLOT(autospin()));

    resize(840, 720);

    triMesh = NULL;
}

TriMeshView::~TriMeshView()
{
//    if(triMesh)
//    {
//        delete triMesh;
//        triMesh = NULL;
//    }
}

void TriMeshView::autospin()
{
    if(camera.autospin(xf))
    {
        updateGL();
    }
}

bool TriMeshView::readMesh(const char *filename, const char *xffilename)
{
    if(triMesh)
    {
        delete triMesh;
        triMesh = NULL;
    }

    triMesh = TriangleMesh::read(filename);
    if(!triMesh)
    {
        cout<<"read file "<<filename<<" error."<<endl;
        exit(-1);
    }

    triMesh->need_bsphere();
    triMesh->need_normals();
    triMesh->need_tstrips();


    if(!xf.read(xffilename))
        xf = xform::trans(0, 0, -3.5f / 0.7 * triMesh->bsphere.r) *
                             xform::trans(-triMesh->bsphere.center);

    camera.stopspin();

    updateGL();
    return true;
}

//------------------------protected function------------------------

void TriMeshView::resizeGL(int width, int height)
{
    //设置opengl视口与QWidget窗口大小相同
    glViewport( 0, 0, (GLint)width, (GLint)height );
}

// Clear the screen and reset OpenGL modes to something sane
void TriMeshView::cls()
{
    glDisable(GL_DITHER);
    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_NORMALIZE);
    glDisable(GL_LIGHTING);
    glDisable(GL_COLOR_MATERIAL);
    glClearColor(0.7, 0.7, 0.7, 0);
//        if (color_style == COLOR_GRAY)
//                glClearColor(0.8, 0.8, 0.8, 0);
    glClearDepth(1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void TriMeshView::drawMesh()
{
    if(triMesh->vertices.empty())
        return;

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, &triMesh->vertices[0][0]);

    glPolygonMode(GL_FRONT_AND_BACK, GL_POINTS);

    glColor3f(1.0f, 1.0f, 1.0f);
    glDrawArrays(GL_POINTS, 0, triMesh->vertices.size());

    glDisableClientState(GL_VERTEX_ARRAY);
}

void TriMeshView::paintGL()
{
    if(!triMesh)
    {
        cls();
        return;
    }

    viewpos = inv(xf) * point(0,0,0);

    camera.setupGL(xf * triMesh->bsphere.center, triMesh->bsphere.r);

    cls();

    // Transform and draw
    glPushMatrix();

    glMultMatrixd((double *)xf);
    //draw_mesh();
    drawMesh();
    glPopMatrix();
}

//鼠标交互处理
Mouse::button btn = Mouse::NONE;
void TriMeshView::mousePressEvent(QMouseEvent *e)
{
    if(!triMesh)
        return;

    int x = e->pos().x();
    int y = e->pos().y();

    if(e->button() ==  Qt::LeftButton)
    {
        btn = Mouse::ROTATE;
    }
    else if(e->button() == Qt::RightButton)
    {
        btn = Mouse::MOVEZ;
    }
    else if(e->button() == Qt::MidButton)
    {
        btn = Mouse::MOVEXY;
    }
    else
        btn = Mouse::NONE;

    //根据鼠标交互位置(x,y)重新放置摄像机
 //   camera.setupGL(xf*triMesh->bsphere.center, triMesh->bsphere.r);
    camera.mouse(x, y, btn, xf*triMesh->bsphere.center, triMesh->bsphere.r, xf);

    mouseMoveEvent(e);
}

void TriMeshView::mouseReleaseEvent(QMouseEvent * e)
{
    if(!triMesh)
        return;

    int x = e->pos().x();
    int y = e->pos().y();

    btn = Mouse::NONE;

    camera.mouse(x, y, btn, xf*triMesh->bsphere.center, triMesh->bsphere.r, xf);
}

void TriMeshView::mouseMoveEvent(QMouseEvent *e)
{
    if(!triMesh)
        return;

    int x = e->pos().x();
    int y = e->pos().y();

    if(e->buttons() &  Qt::LeftButton) //该函数中，e->button()总是返回Qt::NoButton.
    {
        btn = Mouse::ROTATE;
    }
    else if(e->buttons() &  Qt::RightButton)
    {
        btn = Mouse::MOVEZ;
    }
    else if(e->buttons() &  Qt::MidButton)
    {
        btn = Mouse::MOVEXY;
    }
    else
    {
        btn = Mouse::NONE;
    }

    camera.mouse(x, y, btn, xf*triMesh->bsphere.center, triMesh->bsphere.r, xf);

    if(btn != Mouse::NONE)
        updateGL();
}

void TriMeshView::wheelEvent(QWheelEvent *e)
{
    if(!triMesh)
        return;

    int x = e->pos().x();
    int y = e->pos().y();

    if(e->orientation() == Qt::Vertical)
    {
        if (e->delta() > 0)
        {
            btn = Mouse::WHEELUP;
        }
        else
        {
            btn = Mouse::WHEELDOWN;
        }
    }

    e->accept();
    camera.mouse(x, y, btn, xf*triMesh->bsphere.center, triMesh->bsphere.r, xf);
    //btn = Mouse::NONE;
    updateGL();
}

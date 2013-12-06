#include "meshwidget.h"
#include <QFile>
#include <QTextStream>

#include <iostream>
#include <fstream>

namespace zdd
{

MeshWidget::MeshWidget(QWidget *parent)
    : TriMeshView(parent)
{
    rt = Default;
    lom = FromPointer;
}

MeshWidget::~MeshWidget()
{

}

void MeshWidget::setMesh(TriangleMesh *mesh)
{
    if(!mesh)
        return;

    //该类只只适用于从指针
    if(triMesh)
    {
        if(lom == FromFile)
        {
            delete triMesh;
            triMesh = NULL;
        }
        else
        {
            // 交给上层释放
            triMesh = NULL;
        }

    }
    triMesh = mesh;
    this->setLastOpenMode(FromPointer);

    triMesh->need_normals();
    triMesh->need_bsphere();
    triMesh->need_tstrips();

    xf = xform::trans(0, 0, -3.5f / 0.7 * triMesh->bsphere.r) *
                         xform::trans(-triMesh->bsphere.center);

    //xf = xform::rot(-1.57, 0 ,0 ,1) * xf; //逆时针旋转90°

    camera.stopspin();

    this->setWindowTitle(tr("vertices: %1").arg(triMesh->vertices.size()));
    updateGL();
}


//
bool MeshWidget::writeObj(const char *filename)
{
    if(!triMesh)
        return false;

    ofstream fout(filename);

    //顶点
    for(unsigned int i = 0; i < triMesh->vertices.size(); i++)
    {
        fout << "v " << triMesh->vertices[i][0] << " " << triMesh->vertices[i][1] << " " << triMesh->vertices[i][2] <<endl;
    }

    //颜色
    if(triMesh->colors.size() == triMesh->vertices.size())
    {
        for(unsigned int i = 0; i < triMesh->colors.size(); i++)
        {
            fout << "c " << (int)triMesh->colors[i][0] << " " << (int)triMesh->colors[i][1] << " " << (int)triMesh->colors[i][2] <<endl;
        }
    }

    //面片
    for(unsigned int i = 0; i < triMesh->faces.size(); i++)
    {
        fout << "f " << triMesh->faces[i][0] << " " << triMesh->faces[i][1] << " " << triMesh->faces[i][2] <<endl;
    }

    fout.close();
    return true;
}

//
// 使用 QFile存在中文路径问题，故使用如上函数方法，使用ofstream写文件
//bool MeshWidget::writeObj(const char *filename)
//{
//    if(!triMesh)
//        return false;

//    QFile file(filename);
//    file.open(QFile::WriteOnly);

//    QTextStream ts(&file);

//    //顶点
//    for(unsigned int i = 0; i < triMesh->vertices.size(); i++)
//    {
//        ts << "v " << triMesh->vertices[i][0] << " " << triMesh->vertices[i][1] << " " << triMesh->vertices[i][2] <<endl;
//    }

//    //颜色
//    if(triMesh->colors.size() == triMesh->vertices.size())
//    {
//        for(unsigned int i = 0; i < triMesh->colors.size(); i++)
//        {
//            ts << "c " << triMesh->colors[i][0] << " " << triMesh->colors[i][1] << " " << triMesh->colors[i][2] <<endl;
//        }
//    }

//    //面片
//    for(unsigned int i = 0; i < triMesh->faces.size(); i++)
//    {
//        ts << "f " << triMesh->faces[i][0] << " " << triMesh->faces[i][1] << " " << triMesh->faces[i][2] <<endl;
//    }

//    file.close();
//    return true;
//}

bool MeshWidget::readObj(const char *filename)
{
    if(triMesh)
    {
        if(lom == FromFile)
        {
            delete triMesh;
            triMesh = NULL;
        }
        else
        {
            // 交给上层释放
            triMesh = NULL;
        }
    }

    triMesh = TriangleMesh::read(filename);
    if(!triMesh)
    {
        cout<<"read file "<<filename<<" error."<<endl;
        exit(-1);
    }

    this->setLastOpenMode(FromFile);

    triMesh->need_bsphere();
    triMesh->need_normals();
    triMesh->need_tstrips();



    xf = xform::trans(0, 0, -3.5f / 0.7 * triMesh->bsphere.r) *
                         xform::trans(-triMesh->bsphere.center);

    camera.stopspin();

    updateGL();
    return true;
}

bool MeshWidget::readCls(const char *filename)
{
    QFile file(filename);
    file.open(QFile::ReadOnly);

    QTextStream ts(&file);
    QString line;

    colors.clear();

    do {
        line = ts.readLine();
        QStringList lists = line.split(' ');
        if(lists.size() == 4 && line.startsWith('c'))
        {
            unsigned char r = lists.at(1).toShort();
            unsigned char g = lists.at(2).toShort();
            unsigned char b = lists.at(3).toShort();

            colors.push_back(uvec3(r, g, b));
        }

    }while(!line.isNull());

    if(colors.size() != triMesh->vertices.size())
        colors.clear();

    return true;
}

void MeshWidget::resetView()
{
    if(!triMesh)
        return;

    xf = xform::trans(0, 0, -3.5f / 0.7 * triMesh->bsphere.r) *
                         xform::trans(-triMesh->bsphere.center);

    camera.stopspin();
}

void MeshWidget::setRendererType(const RendererType &type)
{
    rt = type;
}

void MeshWidget::setLastOpenMode(const LastOpenMode &mode)
{
    lom = mode;
}

// Draw triangle strips.  They are stored as length followed by values.
void MeshWidget::draw_strips()
{
    if(triMesh->tstrips.empty())
        return;

    const int *t = &triMesh->tstrips[0];
    const int *end = t + triMesh->tstrips.size();

    while (likely(t < end)) {
        int striplen = *t++;
        glDrawElements(GL_TRIANGLE_STRIP, striplen, GL_UNSIGNED_INT, t);
        t += striplen;
    }
}

void MeshWidget::drawMesh()
{
    if(triMesh->vertices.empty())
        return;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

   // glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHTING);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, &triMesh->vertices[0][0]);

    switch(rt)
    {
    case Points:
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        glColor3f(0.5, 1.0, 1.0);
        break;
    case Wireframe:
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glColor3f(0.5, 1.0, 1.0);
        break;
    case WireframeWithLight:
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHTING);
        break;
    case WireframeWithColor:
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        if(triMesh->colors.size() != 0 && this->getTriMesh()->colors.size() == triMesh->vertices.size())
        {
            glEnableClientState(GL_COLOR_ARRAY);
            glColorPointer(3, GL_UNSIGNED_BYTE, 0, &triMesh->colors[0][0]);
        }
        else
        {
            glEnable(GL_LIGHT0);
            glEnable(GL_LIGHTING);
        }
        break;
    case Default:
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        if(triMesh->colors.size() != 0 && this->getTriMesh()->colors.size() == triMesh->vertices.size())
        {
            glEnableClientState(GL_COLOR_ARRAY);
            glColorPointer(3, GL_UNSIGNED_BYTE, 0, &triMesh->colors[0][0]);
        }
        else
        {
            glEnable(GL_LIGHT0);
            glEnable(GL_LIGHTING);
        }
        break;
    }

    //normal array
   if(!triMesh->normals.empty())
   {
       glEnableClientState(GL_NORMAL_ARRAY);
       glNormalPointer(GL_FLOAT, 0, &triMesh->normals[0][0]);
   }
   else
   {
       glDisableClientState(GL_NORMAL_ARRAY);
   }

    draw_strips();

    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

} //namespace zdd

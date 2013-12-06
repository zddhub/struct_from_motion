#ifndef MESHWIDGET_H
#define MESHWIDGET_H

#include <QtWidgets>
#include "meshview/trimeshview.h"

namespace zdd
{

class Color3b {
public:
    Color3b(unsigned char r, unsigned char g, unsigned char b)
    {
        c[0] = r;
        c[1] = g;
        c[2] = b;
    }

    Color3b() { c[0] = c[1] = c[2] = 0; }

    unsigned char c[3];

    unsigned char &operator[] (int i) { return c[i]; }
    const unsigned char &operator[] (int i) const { return c[i]; }

};

class MeshWidget : public TriMeshView
{
    Q_OBJECT

public:

    //
    enum RendererType {
        Default,
        Points,
        Wireframe,
        WireframeWithColor,
        WireframeWithLight
    };

    //记录上一次打开triMesh的方法，如果从文件读取，则释放内存，反之，只引用指针
    enum LastOpenMode
    {
        FromFile, //从文件
        FromPointer //从文件指针
    };

    MeshWidget(QWidget *parent = 0);
    ~MeshWidget();

    bool readObj(const char *filename);
    bool readCls(const char *filename);
    void setMesh(TriangleMesh *mesh);

    bool writeObj(const char *filename);

    void setRendererType(const RendererType &type);

    void resetView();

    void setLastOpenMode(const LastOpenMode &mode);

private:
    RendererType rt;
    LastOpenMode lom;

    void drawMesh();
    void draw_strips();
public:
    vector<uvec3> colors;
};

}// namspace zdd

#endif // MESHWIDGET_H

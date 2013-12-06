#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H

#include "Vec.h"
#include <vector>
#include "Color.h"

class TriangleMesh
{
public:
    //
    //������������
    //
    //Face
    struct Face {
        int v[3];

        Face() {}
        Face(const int &v0, const int &v1, const int &v2)
                { v[0] = v0; v[1] = v1; v[2] = v2; }
        Face(const int *v_)
                { v[0] = v_[0]; v[1] = v_[1]; v[2] = v_[2]; }
        int &operator[] (int i) { return v[i]; }
        const int &operator[] (int i) const { return v[i]; }
        operator const int * () const { return &(v[0]); }
        operator const int * () { return &(v[0]); }
        operator int * () { return &(v[0]); }
        int indexof(int v_) const
        {
                return (v[0] == v_) ? 0 :
                       (v[1] == v_) ? 1 :
                       (v[2] == v_) ? 2 : -1;
        }
    };

    struct BSphere {
        point center;
        float r;
        bool valid;
        BSphere() : valid(false)
                {}
    };

    //
    // Enums
    //
    enum TstripRep { TSTRIP_LENGTH, TSTRIP_TERM };

    //�������Ƭ
    std::vector<point> vertices;
    std::vector<Face> faces;

    //colors
    std::vector<uvec3> colors;

    void need_faces()
    {
        if(!faces.empty())
            return;
        if(!tstrips.empty())
            unpack_tstrips();
    }

    //ģ�ͱ߽磺����
    BSphere bsphere;
    void need_bsphere();

    //��ͨ��
    // Connectivity structures:
    //  For each vertex, all neighboring vertices
    std::vector< std::vector<int> > neighbors;
    //  For each vertex, all neighboring faces
    std::vector< std::vector<int> > adjacentfaces;
    //  For each face, the three faces attached to its edges
    //  (for example, across_edge[3][2] is the number of the face
    //   that's touching the edge opposite vertex 2 of face 3)
    //  across_edge[3][2]��ʾ��������Ƭ���(faces[across_edge[3][2]]Ϊ����������Ƭ)
    //  �����������4(�±�Ϊ3)��������(faces[3])�й����ߣ�������Ϊfaces[3]���±�Ϊ[2]�Ķ������Եı�
    std::vector<Face> across_edge;

    void need_neighbors();
    void need_adjacentfaces();
    void need_across_edge();

    //
    // Compute all this stuff...
    //
    //�����δ����������涼����������
    std::vector<int> tstrips;

    void need_tstrips();
    void convert_strips(TstripRep rep);
    void unpack_tstrips();

    //����
    std::vector<vec> normals;
    void need_normals();


    //�����ʺͷ���
    std::vector<vec> pdir1, pdir2;
    std::vector<float> curv1, curv2;

    std::vector<float> pointareas;
    std::vector<vec> cornerareas;
    void need_pointareas();
    void need_curvatures();

    //���ʵ�΢��
    std::vector< Vec<4,float> > dcurv;
    void need_dcurv();

    //ͳ����Ϣ
    float feature_size();

protected:
    static bool read_helper(const char *filename, TriangleMesh *mesh);
public:
    static TriangleMesh *read(const char *filename);

    //
    // Debugging
    //

    // Debugging printout, controllable by a "verbose"ness parameter
    static int verbose;
    static void set_verbose(int);
    static void (*dprintf_hook)(const char *);
    static void set_dprintf_hook(void (*hook)(const char *));
    static void dprintf(const char *format, ...);

    // Same as above, but fatal-error printout
    static void (*eprintf_hook)(const char *);
    static void set_eprintf_hook(void (*hook)(const char *));
    static void eprintf(const char *format, ...);
};

#endif // TRIANGLEMESH_H

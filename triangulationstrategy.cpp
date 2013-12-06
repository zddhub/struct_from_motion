#include "triangulationstrategy.h"

typedef float pixel_t;

#include "assert.h"

TriangulationStrategy::TriangulationStrategy()
{
}

bool TriangulationStrategy::disparityMapToTriMesh(const cv::Mat &disparity, float Zf, float d, TriangleMesh &triMesh)
{
    //
    if(disparity.empty())
        return false;

    if(disparity.rows < 2 || disparity.cols < 2)
        return false;


    cv::medianBlur(disparity, disparity, 5); //中值滤波, 删除错误的点
    cv::GaussianBlur(disparity, disparity, cv::Size(5, 5), 2.6); //高斯滤波

    pixel_t *data = (pixel_t*) disparity.data;
    int step = disparity.step/sizeof(data[0]);

    if(fabs(data[0] + d) < 1e-5)
    {
        return false;
    }

    //设置顶点
    float halfCols = (float) (disparity.cols >> 2); // 保证i分布到[-halfCols, halfCols]
    float halfRows = (float) (disparity.rows >> 2);

    for(int i = 0; i < disparity.rows; i++)
    {
        for(int  j = 0; j < disparity.cols; j++)
        {
            //注意：此处的取深度时，图像空间坐标系上的点(i,j)转换到世界坐标系时,z = data[i][COLS-j].
            //
            pixel_t disp = *(data + step * i + disparity.channels() *(disparity.cols -j));

            float denominator = disp + d;
            if(fabs(denominator) < 1e-5)
            {
                return false;
            }

            //(x: j--cols, y: i--rows, z)
            //注意：此处的取深度时，图像空间坐标系上的点(i,j)转换到世界坐标系时,z = data[i][COLS-j].
            //image -> (j, i, data[i][COLS-j]
            //pixel_t disp = *(data + step * i + disparity.channels() *(disparity.cols -j));
            triMesh.vertices.push_back(vec(((float)-j + halfCols)/denominator,((float)-i + halfRows)/denominator,(float)(-Zf/denominator)));
            //triMesh.vertices.push_back(vec(((float)-i + halfRows)/denominator,((float)(disparity.cols-j) + -halfCols)/denominator,(float)(-Zf/denominator)));
        }
    }

    //设置拓扑关系
    for(int i = 0; i < disparity.rows - 1; i++)
    {
        for(int j = 0; j < disparity.cols - 1; j++)
        {
            //每个正方形有两个三角形，按顺时针方向。
            //注：在设置顶点时，将图片坐标系(rows, cols)转到空间坐标系(x, y),如下(above)
            //(x: j--cols, y: i--rows, z),
            //注意：此处的取深度时，图像空间坐标系上的点(i,j)转换到世界坐标系时,z = data[i][COLS-j].
            //image -> (j, i, data[i][COLS-j]
            //pixel_t disp = *(data + step * i + disparity.channels() *(disparity.cols -j));
            //triMesh.vertices.push_back(vec(((float)-j + halfCols)/denominator,((float)-i + halfRows)/denominator,(float)(-Zf/denominator)));
            //即沿原点做了对称变换，因此，原本逆时针方向的拓扑关系在对称之后变成了顺时针方向。
            //顺时针方向
            //Face(Index(data[i][j]), Index(data[i][j+1]), Index(data[i+1,j]))
            //Face(Index(data[i+1][j]), Index(data[i][j+1]), Index(data[i+1,j+1]))

            int Vij = i * disparity.cols +j;
            int Vij1 = i * disparity.cols + (j+1);
            int Vi1j = (i+1) * disparity.cols +j;
            int Vi1j1 = (i+1) * disparity.cols +(j+1);


            triMesh.faces.push_back(TriangleMesh::Face( Vij, Vij1, Vi1j));
            triMesh.faces.push_back(TriangleMesh::Face( Vi1j,Vij1, Vi1j1));
//            triMesh.faces.push_back(TriangleMesh::Face( Vij1, Vij, Vi1j));
//            triMesh.faces.push_back(TriangleMesh::Face( Vij1, Vi1j, Vi1j1));
        }
    }

    return true;
}

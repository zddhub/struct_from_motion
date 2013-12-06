/**
*
* TriangulationStrategy
* zdd
* zddmail@gmail.com
*
*/

#ifndef TRIANGULATIONSTRATEGY_H
#define TRIANGULATIONSTRATEGY_H

#include "meshwidget/meshwidget.h"
#include "opencv2/opencv.hpp"

class TriangulationStrategy
{
public:
    TriangulationStrategy();
    static bool disparityMapToTriMesh(const cv::Mat &disparity, float Zf, float d, TriangleMesh &triMesh);
};

#endif // TRIANGULATIONSTRATEGY_H

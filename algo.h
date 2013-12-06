#ifndef ALGO_H
#define ALGO_H

#include <opencv2/opencv.hpp>

//获取视差图
bool getDisparity(const cv::Mat &leftImage, const cv::Mat &rightImage,
                  cv::Mat &disparity, double &minVal, double &maxVal);

//灰度转伪彩色
void gray2PseudoColor(const cv::Mat &gray, cv::Mat &pcolor);


#endif // ALGO_H

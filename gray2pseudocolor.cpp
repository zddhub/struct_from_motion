
#include "algo.h"

#include "assert.h"

//灰度图转伪彩色
//灰度由0-255 ： blue - red
void gray2PseudoColor(const cv::Mat &gray, cv::Mat &pcolor)
{
//    CV_ASSERT(gray.type() == CV_8U && pcolor.type() == CV_8UC3);
//    CV_ASSERT(gray.size() == pcolor.size());

    pcolor = cv::Mat::zeros(gray.rows, gray.cols, CV_8UC3);

    cv::Mat blue = cv::Mat::zeros(gray.rows, gray.cols, CV_8U);
    cv::Mat green = cv::Mat::zeros(gray.rows, gray.cols, CV_8U);
    cv::Mat red = cv::Mat::zeros(gray.rows, gray.cols, CV_8U);

    cv::Mat mask = cv::Mat::zeros(gray.rows, gray.cols, CV_8U);

    cv::subtract(gray, cv::Scalar(0), red); //red = gray
    cv::subtract(cv::Scalar(255), gray, blue); //blue = 255 - gray

    cv::subtract(gray, cv::Scalar(0), green); //if(gray < 128) green = gray
    cv::compare(green, cv::Scalar(128), mask, cv::CMP_GE);//if(gray >= 128) green = 255 - gray
    cv::subtract(cv::Scalar(255), green, green, mask);
    cv::add(green, green, green);

    std::vector<cv::Mat> vm;
    vm.push_back(blue);
    vm.push_back(green);
    vm.push_back(red);
    cv::merge(vm, pcolor);
}

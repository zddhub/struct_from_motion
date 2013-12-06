
#include <stdio.h>
#include <iostream>

#include "algo.h"
using namespace cv;

bool getDisparity(const cv::Mat &leftImage, const cv::Mat &rightImage,
                  cv::Mat &disparity, double &minVal, double &maxVal)
{
    if(leftImage.size() != rightImage.size())
    {
        return false;
    }

    Mat imgLeft, imgRight;

    if(leftImage.channels() != 1)
    {
        cvtColor(leftImage, imgLeft, CV_BGR2GRAY);
        cvtColor(rightImage, imgRight, CV_BGR2GRAY);
    }

//    Mat imgDisparity16S = Mat( imgLeft.rows, imgLeft.cols, CV_16S );
//    Mat imgDisparity8U = Mat( imgLeft.rows, imgLeft.cols, CV_8UC1 );

    Mat imgDisparity32F = Mat( imgLeft.rows, imgLeft.cols, CV_32F );
    Mat imgDisparity8U = Mat( imgLeft.rows, imgLeft.cols, CV_8UC1 );

    if( !imgLeft.data || !imgRight.data )
    {
        std::cout<< " --(!) Error reading images " << std::endl;
        return false;
    }

    //-- 2. Call the constructor for StereoBM
    int ndisparities = 16*5;   /**< Range of disparity */
    int SADWindowSize = 21; /**< Size of the block window. Must be odd */

    StereoBM sbm( StereoBM::BASIC_PRESET, ndisparities, SADWindowSize );

    //-- 3. Calculate the disparity image
   // sbm( imgLeft, imgRight, imgDisparity16S, CV_16S );
    sbm( imgLeft, imgRight, imgDisparity32F, CV_32F );

    //-- Check its extreme values
//    double minVal; double maxVal;

    //minMaxLoc( imgDisparity16S, &minVal, &maxVal );
    minMaxLoc( imgDisparity32F, &minVal, &maxVal );

    printf("Min disp: %f Max value: %f \n", minVal, maxVal);

    //-- 4. Display it as a CV_8UC1 image
    imgDisparity32F.convertTo( imgDisparity8U, CV_8UC1, 255/(maxVal - minVal));

    //disparity = imgDisparity8U;
    disparity = imgDisparity32F;

    return true;
}

#include "qmatlabel.h"

QMatLabel::QMatLabel(QWidget *parent) :
    QLabel(parent)
{
    this->setFrameStyle(QFrame::Box);
}

void QMatLabel::showMatImage(const cv::Mat &matImage)
{
    cv::Mat rgb;
    QImage img;
    if(matImage.channels() == 3)    // RGB image
    {
        cvtColor(matImage,rgb,CV_BGR2RGB);
        img = QImage((const uchar*)(rgb.data),  //(const unsigned char*)
                     rgb.cols,rgb.rows,
                     rgb.cols*rgb.channels(),   //
                     QImage::Format_RGB888);
    }else // gray image
    {
        img = QImage((const uchar*)(matImage.data),
                     matImage.cols,matImage.rows,
                     matImage.cols*matImage.channels(),    //
                     QImage::Format_Indexed8);
    }

    img = img.scaled(this->width(), this->height(), Qt::KeepAspectRatio);
    this->setPixmap(QPixmap::fromImage(img));
    //this->resize(img.width(), img.height());
}

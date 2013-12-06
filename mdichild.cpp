#include "mdichild.h"

MdiChild::MdiChild(QWidget *parent) :
    QScrollArea(parent)
{
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setSizePolicy(sizePolicy);

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    imageLabel = new QLabel(this);
    this->setWidget(imageLabel);

    this->setWindowType(Default);
}

void MdiChild::setWindow(QMdiSubWindow *window)
{
    areaWindow = window;
}

////��IplImageת��ΪQImage,ͨ�������ڴ棬ʵ�ֵ�һ��ʵʱ���Ż��ķ���
//void MdiChild::cvxIplImageToQImage(const IplImage *pIplImage, QImage &qImage)
//{
//    if(!pIplImage)
//        return;
//    if(qImage.isNull())
//    {
//        //Format_RGB888ʹ��24λ
//        qImage = QImage(QSize(pIplImage->width, pIplImage->height),
//                        QImage::Format_RGB888);
//        cvImage = cvCreateImageHeader(
//                cvSize(pIplImage->width, pIplImage->height), 8, 3);
//        //IplImage �� QImage �����ڴ�
//        cvImage->imageData = (char*)qImage.bits();
//    }

//    cvCopy(pIplImage, cvImage, 0);

//    //QT�еĵ�ͼƬ��RGB��ʽ����OpenCV����ͷ���ͼƬ��BGR��ʽ
//    //ת����ʽ����
//    cvCvtColor(cvImage, cvImage, CV_BGR2RGB);
//}

//��IplImage ת��Ϊ QImage
QImage& MdiChild::cvxCopyIplImage(const IplImage *pIplImage, QImage &qImage)
{
   if(!pIplImage) return qImage;

   // qImage

   if(qImage.isNull())
   {
      int w = pIplImage->width;
      int h = pIplImage->height;
      qImage = QImage(w, h, QImage::Format_RGB32);
   }
//qDebug("IplImage width:%d height:%d", pIplImage->width, pIplImage->height);
   int x, y;
   for(x = 0; x < pIplImage->width; ++x)
   {
      for(y = 0; y < pIplImage->height; ++y)
      {
         CvScalar color = cvGet2D(pIplImage, y, x);

         int r = color.val[2];
         int g = color.val[1];
         int b = color.val[0];

         qImage.setPixel(x, y, qRgb(r,g,b));
      }
   }

   return qImage;
}

void MdiChild::showMatImage(const cv::Mat &matImage)
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

    //img = img.scaled(this->width(), this->height(), Qt::KeepAspectRatio);
    imageLabel->setPixmap(QPixmap::fromImage(img));
    imageLabel->resize(imageLabel->pixmap()->size());
    this->resize(imageLabel->pixmap()->size());
    //this->adjustSize();
    //this->setPixmap(QPixmap::fromImage(img));
    //this->widget()->resize(imageLabel->pixmap()->size());

    this->areaWindow->resize(QSize(this->size().width()+16, this->size().height()+39));

    this->show();

    //this->resize(img.width(), img.height());
}


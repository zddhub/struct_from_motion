#ifndef MDICHILD_H
#define MDICHILD_H

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <QTabWidget>
#include <QLabel>
#include <QScrollArea>
#include <QMdiSubWindow>

class MdiChild : public QScrollArea
{
    Q_OBJECT
public:
    enum WindowType
    {
        Default,
        LeftWindow,
        RightWindow,
        MatchWindow,
        DepthWindow,
        DisparityWindow
    };

    explicit MdiChild(QWidget *parent = 0);
    void showMatImage(const cv::Mat &matImage);
    void setWindow(QMdiSubWindow *window);
    WindowType getWindowType() const {return wt;}
    void setWindowType(WindowType type) { wt = type; }
signals:

public slots:
private:
    //void cvxIplImageToQImage(const IplImage *pIplImage, QImage &qImage);
    QImage& cvxCopyIplImage(const IplImage *pIplImage, QImage &qImage);
private:
    QString fileName;
    QLabel *imageLabel;
    QMdiSubWindow *areaWindow;
    WindowType wt;
};

#endif // MDICHILD_H

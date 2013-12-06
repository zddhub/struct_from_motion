#ifndef QMATLABEL_H
#define QMATLABEL_H

#include <QLabel>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

//Make OpenCV Mat Image show in QLabel
class QMatLabel : public QLabel
{
    Q_OBJECT
public:
    explicit QMatLabel(QWidget *parent = 0);
    void showMatImage(const cv::Mat &matImage);
signals:

public slots:

private:


};

#endif // QMATLABEL_H

#ifndef PROGRESSINDICATOR_H
#define PROGRESSINDICATOR_H

#include <QWidget>
#include <QTimer>

//等待提示窗口
class ProgressIndicator : public QWidget
{
    Q_OBJECT
public:
    explicit ProgressIndicator(QWidget *parent = 0);
    ~ProgressIndicator();

    bool isAnimated () const;
    int animationDelay() const;
    void setColor(const QColor &color);
    QColor & getColor();
    void setDisplayWhenStop(bool is_display_when_stop);
    bool isDisplayWhenStop() const;
    void startAnimation();
    void stopAnimation();
    void setAnimationDelay(int delay_time);

protected:
    void paintEvent(QPaintEvent *);
signals:
    
public slots:
    void updateAngle();
private:
    int angle;
    int timer_id;
    int delay_time;
    bool is_display_when_stop;
    QColor color;
    QTimer *timer;
};

#endif // PROGRESSINDICATOR_H

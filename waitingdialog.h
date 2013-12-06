#ifndef WAITINGDIALOG_H
#define WAITINGDIALOG_H

#include <QDialog>
#include "progressindicator.h"

class WaitingDialog : public QDialog
{
    Q_OBJECT
public:
    explicit WaitingDialog(QWidget *parent = 0);
    ~WaitingDialog();
    
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
    void timerEvent(QTimerEvent *);
    void paintEvent(QPaintEvent *);
signals:

public slots:

private:
    int angle;
    int timer_id;
    int delay_time;
    bool is_display_when_stop;
    QColor color;
};

#endif // WAITINGDIALOG_H

#include "waitingdialog.h"

#include <QPainter>

WaitingDialog::WaitingDialog(QWidget *parent) :
    QDialog(parent)
{
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFocusPolicy(Qt::NoFocus);

    angle = 0,
    timer_id = -1,
    delay_time = 50,
    is_display_when_stop = false,
    color = Qt::black;
    //startAnimation();
}

WaitingDialog::~WaitingDialog()
{
    //stopAnimation();
}

bool WaitingDialog::isAnimated() const
{
    return(timer_id != -1);
}

int WaitingDialog::animationDelay() const
{
    return delay_time;
}

void WaitingDialog::setColor(const QColor&color)
{
    this->color = color;
    update();
}

QColor & WaitingDialog::getColor()
{
    return color;
}

void WaitingDialog::setDisplayWhenStop(bool is_display_when_stop)
{
    this->is_display_when_stop = is_display_when_stop;
    update();
}

bool WaitingDialog::isDisplayWhenStop() const
{
    return is_display_when_stop;
}

void WaitingDialog::startAnimation()
{
    angle = 0;
    if(timer_id == -1)
    {
        timer_id = startTimer(delay_time);
    }
}

void WaitingDialog::stopAnimation()
{
    if(timer_id!= -1)
    {
        killTimer(timer_id);
    }
    timer_id =-1;
    update();
}

void WaitingDialog::setAnimationDelay(int delay_time)
{
    if(timer_id!= -1)
    {
        killTimer(timer_id);
    }

    this->delay_time = delay_time;

    if(timer_id != -1)
    {
        timer_id = startTimer(delay_time);
    }
}

void WaitingDialog::timerEvent(QTimerEvent *)
{
    angle =(angle + 30) % 360;
    update();
}

void WaitingDialog::paintEvent(QPaintEvent *)
{
    if(!is_display_when_stop && !isAnimated())
       return;

    int width = qMin(this->width(),this->height());
    QPainter p(this);

    p.setRenderHint(QPainter::Antialiasing);

    int outer_radius = (width - 1) * 0.5;
    int inner_radius = (width - 1) * 0.5 * 0.4;

    int capsule_height = outer_radius - inner_radius;
    int capsule_width  = (width > 32 ) ? capsule_height *.30 : capsule_height *.35;
    int capsule_radius = capsule_width/2;

    for(int i = 0; i < 12; i++)
    {
       color.setAlphaF(1.0f - (i/12.0f));
       p.setPen(Qt::NoPen);
       p.setBrush(color);
       p.save();
       p.translate(rect().center());
       p.rotate(angle - i*30.0f);
       p.drawRoundedRect(-capsule_width*0.5,-(inner_radius+capsule_height), capsule_width, capsule_height,capsule_radius, capsule_radius);
       p.restore();
    }
}

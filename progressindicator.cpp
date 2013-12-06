#include "progressindicator.h"

#include <QPainter>

ProgressIndicator::ProgressIndicator(QWidget *parent) :
    QWidget(parent)
{
    setWindowFlags(Qt::WindowStaysOnTopHint & Qt::FramelessWindowHint);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFocusPolicy(Qt::NoFocus);

    angle = 0,
    timer_id = -1,
    delay_time = 50,
    is_display_when_stop = false,
    color = Qt::black;

    timer = new QTimer();
    timer->setInterval(delay_time);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateAngle()));
    timer->start();
}

ProgressIndicator::~ProgressIndicator()
{
    if(timer->isActive())
        timer->stop();
    delete timer;
}

bool ProgressIndicator::isAnimated() const
{
    return timer->isActive();
}

int ProgressIndicator::animationDelay() const
{
    return delay_time;
}

void ProgressIndicator::setColor(const QColor&color)
{
    this->color = color;
    update();
}

QColor & ProgressIndicator::getColor()
{
    return color;
}

void ProgressIndicator::setDisplayWhenStop(bool is_display_when_stop)
{
    this->is_display_when_stop = is_display_when_stop;
    update();
}

bool ProgressIndicator::isDisplayWhenStop() const
{
    return is_display_when_stop;
}

void ProgressIndicator::startAnimation()
{
    angle =0;
    timer->setInterval(delay_time);
    timer->start();
}

void ProgressIndicator::stopAnimation()
{
    if(timer->isActive())
        timer->stop();
    update();
}

void ProgressIndicator::setAnimationDelay(int delay_time)
{
    timer->stop();
    timer->setInterval(delay_time);
    this->delay_time = delay_time;
}

void ProgressIndicator::updateAngle()
{
    angle =(angle + 30) % 360;
    update();
}

void ProgressIndicator::paintEvent(QPaintEvent *)
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


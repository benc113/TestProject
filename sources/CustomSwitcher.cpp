#include "CustomSwitcher.h"

#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QVariantAnimation>

#define CIRCLE_OFFSET 10

CustomSwitcher::CustomSwitcher(QWidget *parent) :
    QWidget(parent),
    m_isOn(false),
    m_AnimationFinished(true)
{
    m_CirclePositionAnim = new QVariantAnimation(this);
    m_BackgroundColorAnim = new QVariantAnimation(this);

    setupAnimation();

    //one connection will be enough for both animations
    connect(m_CirclePositionAnim, SIGNAL(valueChanged(QVariant)), this, SLOT(update()));
    connect(m_CirclePositionAnim, SIGNAL(finished()), this,SLOT(onAnimationFinished()));
}

CustomSwitcher::~CustomSwitcher()
{
    delete m_CirclePositionAnim;
    delete m_BackgroundColorAnim;
}

void CustomSwitcher::onAnimationFinished()
{
    m_AnimationFinished = true;
}

void CustomSwitcher::setupAnimation()
{
    m_CirclePositionAnim->setDuration(300);
    m_BackgroundColorAnim->setDuration(300);

    if (m_isOn)
    {
        m_BackgroundColorAnim->setStartValue(QColor(146,220,92));
        m_BackgroundColorAnim->setEndValue(QColor(230,222,211));

        m_CirclePositionAnim->setStartValue(width()/2);
        m_CirclePositionAnim->setEndValue(0);
    }
    else
    {
        m_BackgroundColorAnim->setStartValue(QColor(230,222,211));
        m_BackgroundColorAnim->setEndValue(QColor(146,220,92));

        m_CirclePositionAnim->setStartValue(0);
        m_CirclePositionAnim->setEndValue(width()/2);
    }
}

void CustomSwitcher::mousePressEvent(QMouseEvent* event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        setupAnimation();
        m_CirclePositionAnim->start();
        m_BackgroundColorAnim->start();
        m_AnimationFinished = false;

        m_isOn = !m_isOn;

        if (m_isOn)
            emit turnedOn();
        else
            emit turnedOff();
    }
}

void CustomSwitcher::paintEvent(QPaintEvent* event)
{
    int width = event->rect().width();
    int height = event->rect().height();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setBrush(QBrush(m_BackgroundColorAnim->currentValue().value<QColor>()));
    painter.setPen(m_BackgroundColorAnim->currentValue().value<QColor>());

    painter.drawEllipse(0,0,width/2, height);
    painter.drawEllipse(width/2,0,width/2, height);
    painter.drawRect(width/4,0,width/2, height);

    painter.setPen(QColor(250,250,250));
    painter.setBrush(QBrush(QColor(250,250,250)));

    QFont customFont("AlternateGotNo3D");
    customFont.setPointSize(15);

    painter.setFont(customFont);
    painter.drawText(QPoint(width/4,height/2),"ON");
    painter.drawText(QPoint(width*3/4,height/2),"OFF");


    painter.setBrush(QBrush(QColor(250,250,250)));

    int lOffset(0);
    if (m_AnimationFinished)
    {
        if (m_isOn)
            lOffset = width/2;
    }
    else
    {
        lOffset = m_CirclePositionAnim->currentValue().toInt();
    }
    painter.drawEllipse(CIRCLE_OFFSET+lOffset,CIRCLE_OFFSET,width/2-2*CIRCLE_OFFSET, height-2*CIRCLE_OFFSET);
}

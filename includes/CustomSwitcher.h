#ifndef CUSTOMSWITCHER_H
#define CUSTOMSWITCHER_H

#include <QWidget>

class QVariantAnimation;

class CustomSwitcher : public QWidget
{
    Q_OBJECT

public:
    explicit CustomSwitcher(QWidget* parent = 0);
    ~CustomSwitcher();

protected:
    void mousePressEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent* event);

protected slots:
    void onAnimationFinished();

signals:
    void turnedOn();
    void turnedOff();

private:
    void setupAnimation();


protected:
    bool m_isOn;

    QVariantAnimation* m_CirclePositionAnim;
    QVariantAnimation* m_BackgroundColorAnim;

private:
    bool m_AnimationFinished;

};

#endif // CUSTOMSWITCHER_H

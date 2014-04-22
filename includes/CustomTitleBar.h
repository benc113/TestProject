#ifndef CUSTOMTITLEBAR_H
#define CUSTOMTITLEBAR_H

#include <QWidget>

namespace Ui {
class CustomTitleBar;
}

class CustomTitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit CustomTitleBar(QWidget *parent = 0);
    ~CustomTitleBar();

    void setTitle(const QString& title);

signals:
    void customClose();
    void customMaximize();
    void customMinimize();
    void customRestore();

    void barMoved(QPoint);

protected slots:
    void onMaximizeRestore();
    void onCustomSystemMenu();

protected:
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent * event);

private:
    Ui::CustomTitleBar *ui;

    bool m_restoreIconShown;

    QPoint m_MouseOffset;
    bool m_firstEncounter;
};

#endif // CUSTOMTITLEBAR_H

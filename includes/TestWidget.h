#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QWidget>

namespace Ui {
class TestWidget;
}

class QStateMachine;
class QState;

class TestWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TestWidget(QWidget *parent = 0);
    ~TestWidget();

protected:
    void setupStates();

protected slots:
    void onCustomStateEntered();
    void onCustomStateExited();

    void moveToPont(QPoint);

private:
    Ui::TestWidget *ui;

    QStateMachine* m_stateMachine;
    QState* m_stateStandart;
    QState* m_stateCustom;
};

#endif // TESTWIDGET_H

#include "testwidget.h"
#include "ui_testwidget.h"

#include <QStateMachine>
#include <QState>
#include <QSignalTransition>
#include <QPropertyAnimation>

#include <QGraphicsDropShadowEffect>

TestWidget::TestWidget(QWidget *parent)
    :QWidget(parent),
    ui(new Ui::TestWidget),
    m_stateMachine(NULL),
    m_stateStandart(NULL),
    m_stateCustom(NULL)
{
    ui->setupUi(this);
    ui->titleWidget->setVisible(false);

    connect(ui->titleWidget, SIGNAL(customClose()), this, SLOT(close()));
    connect(ui->titleWidget, SIGNAL(customMaximize()), this, SLOT(showMaximized()));
    connect(ui->titleWidget, SIGNAL(customMinimize()), this, SLOT(showMinimized()));
    connect(ui->titleWidget, SIGNAL(customRestore()), this, SLOT(showNormal()));
    connect(ui->titleWidget, SIGNAL(barMoved(QPoint)), this, SLOT(moveToPont(QPoint)));

    m_stateMachine = new QStateMachine;
    m_stateStandart = new QState;
    m_stateCustom = new QState;

    m_stateMachine->addState(m_stateStandart);
    m_stateMachine->addState(m_stateCustom);
    m_stateMachine->setInitialState(m_stateStandart);
    m_stateMachine->setGlobalRestorePolicy(QState::RestoreProperties);

    setupStates();

    QFont customFont("AlternateGotNo3D");
    customFont.setPointSize(15);
    ui->label->setFont(customFont);

    m_stateMachine->start();
}

void TestWidget::moveToPont(QPoint point)
{
    move(point);
}

void TestWidget::setupStates()
{
    //was trying to make title change smooth
    //slots can be connected to switcher directly if needed
    //this will look like this:
    //connect(ui->switcher, SIGNAL(turnedOn()), this, SLOT(onCustomStateEntered()));
    //connect(ui->switcher, SIGNAL(turnedOff()), this, SLOT(onCustomStateExited()));
    QSignalTransition *transition = m_stateStandart->addTransition(ui->switcher, SIGNAL(turnedOn()), m_stateCustom);
    transition->addAnimation(new QPropertyAnimation(this, "windowTitle"));
    transition = m_stateCustom->addTransition(ui->switcher, SIGNAL(turnedOff()), m_stateStandart);

    m_stateCustom->assignProperty(this, "windowTitle", "Custom Window");
    m_stateCustom->assignProperty(this,"windowFlags",Qt::FramelessWindowHint);

    connect(m_stateCustom, SIGNAL(entered()), this, SLOT(onCustomStateEntered()));
    connect(m_stateCustom, SIGNAL(exited()), this, SLOT(onCustomStateExited()));
}

void TestWidget::onCustomStateEntered()
{
    QRect ownRect = geometry();
    QPoint ownPos = pos();

    setWindowFlags(Qt::FramelessWindowHint);
    show();
    ui->titleWidget->setVisible(true);
    setGeometry(ownRect);
    move(ownPos);
}

void TestWidget::onCustomStateExited()
{
    setWindowFlags(Qt::Widget);
    show();
    ui->titleWidget->setVisible(false);
}

TestWidget::~TestWidget()
{
    delete ui;

    delete m_stateMachine;
    //will be deleted by parent automatically
    //delete m_stateStandart;
    //delete m_stateCustom;
}

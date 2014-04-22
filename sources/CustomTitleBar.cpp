#include "CustomTitleBar.h"
#include "ui_CustomTitleBar.h"
#include <QMouseEvent>

#include <QMenu>

CustomTitleBar::CustomTitleBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomTitleBar),
    m_restoreIconShown(false),
    m_MouseOffset(QPoint()),
    m_firstEncounter(true)
{
    ui->setupUi(this);

    connect(ui->closeButton,SIGNAL(clicked()), this, SIGNAL(customClose()));
    connect(ui->systemMenuButton,SIGNAL(clicked()), this, SLOT(onCustomSystemMenu()));
    connect(ui->minimizeButton,SIGNAL(clicked()), this, SIGNAL(customMinimize()));
    connect(ui->maximizeButton,SIGNAL(clicked()), this, SLOT(onMaximizeRestore()));

}

void CustomTitleBar::onCustomSystemMenu()
{
    QMenu* sysMenu = new QMenu(this);

    QAction* action = new QAction(QIcon("://Assets/images/restore.png"), tr("Restore"), this);
    action->setEnabled(m_restoreIconShown);
    connect(action, SIGNAL(triggered()), this, SLOT(onMaximizeRestore()));
    sysMenu->addAction(action);

    action = new QAction(QIcon("://Assets/images/minimize.png"), tr("Minimize"), this);
    connect(action, SIGNAL(triggered()), this, SIGNAL(customMinimize()));
    sysMenu->addAction(action);

    action = new QAction(QIcon("://Assets/images/maximize.png"), tr("Maximize"), this);
    action->setEnabled(!m_restoreIconShown);
    connect(action, SIGNAL(triggered()), this, SLOT(onMaximizeRestore()));
    sysMenu->addAction(action);

    sysMenu->addSeparator();

    action = new QAction(QIcon("://Assets/images/close.png"), tr("Close"), this);
    connect(action, SIGNAL(triggered()), this, SIGNAL(customClose()));
    sysMenu->addAction(action);

    sysMenu->exec(parentWidget()->pos());

}

void CustomTitleBar::onMaximizeRestore()
{
    if (m_restoreIconShown)
    {
        ui->maximizeButton->setIcon(QIcon("://Assets/images/maximize.png"));
        emit customRestore();
    }
    else
    {
        ui->maximizeButton->setIcon(QIcon("://Assets/images/restore.png"));
        emit customMaximize();
    }

    m_restoreIconShown = !m_restoreIconShown;
}

CustomTitleBar::~CustomTitleBar()
{
    delete ui;
}

void CustomTitleBar::setTitle(const QString& title)
{
    ui->titleLabel->setText(title);
}

void CustomTitleBar::mouseReleaseEvent(QMouseEvent* event)
{
    m_firstEncounter = true;
    QWidget::mousePressEvent(event);
}

void CustomTitleBar::mouseMoveEvent(QMouseEvent * event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        if (m_firstEncounter)
        {
            QPoint eventPos = event->globalPos();
            QPoint widgetPos = parentWidget()->pos();

            m_MouseOffset = eventPos-widgetPos;
            m_firstEncounter = false;
        }

        emit barMoved(event->globalPos()- m_MouseOffset);
    }

    QWidget::mouseMoveEvent(event);
}

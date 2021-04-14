/*
#include "timer.h"
#include "ui_timer.h"

Timer::Timer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Timer)
{
    ui->setupUi(this);
}

Timer::~Timer()
{
    delete ui;
}
*/

#include "timer.h"
#include <qdebug.h>

#define Width 520
#define Height 150

/**
 */
Timer::Timer(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    setWindowFlags(Qt::Widget | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    initUi();

    m_mouseMove = true;
    m_mouseX = this->geometry().x();
    m_mouseY = this->geometry().y();
    m_absX = this->geometry().x();
    m_absY = this->geometry().y();

    connect(&m_clockThread, SIGNAL(sendTime(QString)), ui.label, SLOT(setText(QString)), Qt::QueuedConnection);
    connect(this, SIGNAL(resume()), &m_clockThread, SLOT(onResume()));
    connect(this, SIGNAL(reset()), &m_clockThread, SLOT(onReset()) );
    connect(this, SIGNAL(pause()), &m_clockThread, SLOT(onPause()) );
}


Timer::~Timer()
{
}

/**
*/
void Timer::initUi()
{
    setFixedSize(Width, Height);

    ui.label->setText("0 : 0 : 0");

    showButtons(false);

    this->setWindowOpacity(0.8);

    ui.pauseButton->setDisabled(true);
    ui.resetButton->setDisabled(true);

    QString sheet =
        "QWidget#timer {"
        " background-color: rgb(47,47,47);"
        "}"

        "QPushButton {"
        " color : white;"
        " background-color: rgb(58,134,255);"
        " border-radius : 6px;"
        "}"
        "QPushButton::hover {"
        " color : white;"
        " background-color: rgb(33,90,181);"
        " border-radius : 6px;"
        "}"
        "QPushButton::pressed {"
        " color : white;"
        " background-color: rgb(27,48,82);"
        " border-radius : 6px;"
        "}"
        "QPushButton::disabled {"
        " color : white;"
        " background-color: rgb(27,48,82);"
        " border-radius : 6px;"
        "}"
        ;

    setStyleSheet(sheet);
}

/**
 */
void Timer::on_closeButton_clicked()
{
    m_clockThread.quit();
    m_clockThread.wait();
    QCoreApplication::quit();
}

/**
 */
void Timer::on_startButton_clicked()
{
    ui.startButton->setDisabled(true);
    ui.pauseButton->setDisabled(false);
    ui.resetButton->setDisabled(false);

    if (m_clockThread.isRunning())
    {
        emit resume();
    }
    else
    {
        m_clockThread.start();
    }
}

/**
 */
void Timer::on_pauseButton_clicked()
{
    ui.startButton->setDisabled(false);
    ui.pauseButton->setDisabled(true);
    ui.resetButton->setDisabled(false);
    emit pause();
}

/**
*/
void Timer::on_resetButton_clicked()
{
    ui.startButton->setDisabled(false);
    ui.pauseButton->setDisabled(true);
    ui.resetButton->setDisabled(true);
    emit reset();
}

void Timer::showButtons(bool show)
{
    if (show)
    {
        ui.startButton->show();
        ui.pauseButton->show();
        ui.resetButton->show();
        ui.closeButton->show();
    }
    else
    {
        ui.startButton->hide();
        ui.pauseButton->hide();
        ui.resetButton->hide();
        ui.closeButton->hide();
    }
}

/**
*/
void Timer::mouseReleaseEvent(QMouseEvent*)
{
    qDebug() << "in mouseReleaseEvent";
    m_mouseMove = true;
}

/**
*/
void Timer::enterEvent(QEvent*)
{
    qDebug() << "in enterEvent";
    showButtons(true);
}

/**
*/
void Timer::leaveEvent(QEvent* event)
{
    qDebug() << "in leaveEvent";
    showButtons(false);
}


/**
*/
void Timer::mouseMoveEvent(QMouseEvent *mouse)
{
    qDebug() << "in mouseMoveEvent";
    if (mouse->button() == Qt::RightButton)
    {
        return;
    }

    m_mouseX = QCursor::pos().x();
    m_mouseY = QCursor::pos().y();

    if (m_mouseMove)
    {
        m_absX = mouse->pos().x() + 7;
        m_absY = mouse->pos().y() + 7;
        m_mouseMove = false;
    }
    this->move(m_mouseX - m_absX, m_mouseY - m_absY);
}

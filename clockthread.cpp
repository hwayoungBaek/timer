#include "clockthread.h"

#include <QTimer>

ClockThread::ClockThread(QObject* parent)
: QThread(parent)
{
    init();
}

ClockThread::~ClockThread()
{
}

void ClockThread::init()
{
    m_running = false;
    m_hours = 0;
    m_minutes = 0;
    m_seconds = 0;

    QString time = QString("%1 : %2 : %3").arg(m_hours).arg(m_minutes).arg(m_seconds);
    emit sendTime(time);
}

void ClockThread::onResume()
{
    m_running = true;
}

void ClockThread::onPause()
{
    m_running = false;
}

void ClockThread::onReset()
{
    init();
    quit();
}

void ClockThread::run()
{
    m_running = true;

    QTimer timer;
    connect(&timer, SIGNAL(timeout()), this, SLOT(timerHit()), Qt::DirectConnection);
    timer.setInterval(1000); // 1000msc = 1 sec
    timer.start();
    exec();
}

void ClockThread::timerHit()
{
    if(m_running)
    {
        m_seconds++;
        if(m_seconds>60)
        {
            m_minutes++;
            m_seconds = 0;
        }
        if(m_minutes>60)
        {
            m_hours++;
            m_minutes = 0;
        }

        QString time = QString("%1 : %2 : %3").arg(m_hours).arg(m_minutes).arg(m_seconds);
        emit sendTime(time);
    }
}

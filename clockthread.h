#ifndef CLOCKTHREAD_H
#define CLOCKTHREAD_H

#include <QThread>
#include <QObject>

class ClockThread : public QThread
{
    Q_OBJECT;

public:
    ClockThread(QObject* parent=Q_NULLPTR);
    virtual ~ClockThread();

private:
    bool m_firstTime;
    bool m_running;
    int m_hours;
    int m_minutes;
    int m_seconds;

private:
    void init();
    void run();

signals:
    void sendTime(QString time);

private slots:
    void onResume();
    void onPause();
    void onReset();
    void timerHit();
};

#endif

#pragma once

#ifndef TIMER_H
#define TIMER_H

#include "clockthread.h"
#include <QWidget>
#include <QMouseEvent>
#include "ui_timer.h"

class ClockThread;

namespace Ui{
    class Timer;
}

class Timer : public QWidget
{
    Q_OBJECT

public:
    Timer(QWidget *parent = Q_NULLPTR);
    ~Timer();

private:
    Ui::Timer ui;
    ClockThread m_clockThread;

    bool m_mouseMove;
    int m_mouseX;
    int m_mouseY;
    int m_absX;
    int m_absY;

private:
    void initUi();
    void showButtons(bool show);

protected:
    virtual void mouseReleaseEvent(QMouseEvent*);
    virtual void mouseMoveEvent(QMouseEvent*);
    virtual void enterEvent(QEvent* event);
    virtual void leaveEvent(QEvent* event);

signals:
    void resume();
    void pause();
    void reset();

private slots:
    void on_closeButton_clicked();
    void on_startButton_clicked();
    void on_pauseButton_clicked();
    void on_resetButton_clicked();
};

#endif

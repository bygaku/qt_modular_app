#ifndef POMODORO_TIMER_H
#define POMODORO_TIMER_H

#include <QObject>
#include <QTimer>
#include <QTime>

class PomodoroTimer : public QObject {
    Q_OBJECT

    Q_PROPERTY(int currentTime READ currentTime NOTIFY timeChanged)
    Q_PROPERTY(bool isRunning READ isRunning NOTIFY runningChanged)
    Q_PROPERTY(TimerState state READ state NOTIFY stateChanged)

public:
    /**
     * @brief Current state.
     */
    enum TimerState {
        WORK,       // 25 min
        BREAK,      // 5 min
    };
    Q_ENUM(TimerState)

    /**
     * @brief Construct an instance of the PomodoroTimer.
     */
    explicit PomodoroTimer(QObject* parent = nullptr);

    /**
     * @brief Get current time value.
     * @return current_time_
     *
     * @note this value is milliseconds.
     * @note 1sec = 1000ms.
     */
    int currentTime()   const;

    /**
     * @brief Check is timer running.
     */
    bool isRunning()    const;

    /**
     * @brief Get current state.
     * @retval WORK
     * @retval BREAK
     */
    TimerState state()  const;

    /**
     * @brief setTargetTime
     */
    void setTargetTime();

public slots:
    void start();
    void stop();
    void reset();

signals:
    void timeChanged();
    void runningChanged();
    void stateChanged();
    void finished();

private slots:
    void onTimeout();

private:
    QTimer      timer_;
    int         remaining_seconds_;
    TimerState  state_;
    bool        is_running_;

    const int WORK_TIME  = 25 * 60;
    const int BREAK_TIME =  5 * 60;

};

#endif // POMODORO_TIMER_H

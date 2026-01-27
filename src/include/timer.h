#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include <QTimer>
#include <QElapsedTimer>
#include <QTime>

class TimerModule : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool      isRunning      READ isRunning                              NOTIFY runningChanged    )
    Q_PROPERTY(bool      notifyState    READ notifyState                            NOTIFY notifyStateChanged)
    Q_PROPERTY(int       currentTime    READ currentTime                            NOTIFY timeChanged       )
    Q_PROPERTY(TimerMode mode           READ mode           WRITE setMode           NOTIFY modeChanged       )
    Q_PROPERTY(int       interval       READ interval       WRITE setInterval       NOTIFY intervalChanged   )
    Q_PROPERTY(int       targetDuration READ targetDuration WRITE setTargetDuration NOTIFY targetChanged     )
    Q_ENUMS(TimerMode)

public:
    /**
     * @brief The TimerMode enum
     */
    enum TimerMode {
        CountUp,    // count-up timer.
        CountDown,  // count-down timer.
        Pomodoro    // loop "work: 25 + break: 5".
    };

    /**
     * @brief constructs the Timer class instance.
     */
    explicit TimerModule(QObject* parent = nullptr);

    /**
     * @brief Get current time value.
     * @return current_time_
     *
     * @note this value is milliseconds.
     * @note 1sec = 1000ms.
     */
    int currentTime() const;

    /**
     * @brief Get current TimerMode.
     * @return mode_
     */
    TimerMode mode() const { return mode_; }

    /**
     * @brief setMode
     * @param m TimerMode
     */
    void setMode(const TimerMode& m);

    /**
     * @brief Check timer count is running.
     * @return is_running_ true or false.
     */
    bool isRunning() const { return is_running_; }

    /**
     * @brief setInterval
     * @param ms milliseconds.
     *
     * @note this value is milliseconds.
     * @note 1sec = 1000ms.
     */
    void setInterval(const uint32_t& ms);

    /**
     * @brief Get interval value.
     * @return interval_
     *
     * @note this value is milliseconds.
     * @note 1sec = 1000ms.
     */
    const uint32_t& interval() const { return interval_; }

    /**
     * @brief setTargetDuration
     * @param ms milliseconds.
     *
     * @note this value is milliseconds.
     * @note 1sec = 1000ms
     */
    void setTargetDuration(const uint32_t& ms);

    /**
     * @brief Get targetDuration value.
     * @return target_duration_
     *
     * @note this value is milliseconds.
     * @note 1sec = 1000ms.
     */
    const uint32_t& targetDuration() const { return target_duration_; }

    /**
     * @brief Get notify state.
     * @return notify_state_, true or false.
     */
    bool notifyState() const { return notify_state_; }

public slots:
    /**
     * @brief Start the count.
     */
    void start();

    /**
     * @brief Stop the count.
     */
    void stop();

    /**
     * @brief Reset the initial value.
     */
    void reset();

    /**
     * @brief notify
     */
    void notify();

signals:
    void runningChanged();
    void notifyStateChanged();
    void timeChanged();
    void modeChanged();
    void intervalChanged();
    void targetChanged();
    void finished();

private slots:
    void onTimeout();

private:
    QTimer          timer_;
    QElapsedTimer   elapsed_;
    QTime           target_time_;

    TimerMode       mode_;
    bool            is_running_;
    bool            notify_state_;

    uint32_t        target_duration_;
    uint32_t        interval_;

};

#endif // TIMER_H

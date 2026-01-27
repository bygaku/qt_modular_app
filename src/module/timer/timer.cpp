#include <timer.h>

TimerModule::TimerModule(QObject* parent)
    : QObject(parent)
    , is_running_(false)
    , notify_state_(false)
    , interval_(1000)
    , target_duration_(0) {
    connect(&timer_, &QTimer::timeout, this, &TimerModule::onTimeout);
}

void TimerModule::setMode(const TimerMode& m) {
    if(mode_ == m) return;

    mode_ = m;
    emit modeChanged();

    // reset signals.
    if (is_running_) {
        reset();
    }
}

void TimerModule::setTargetDuration(const uint32_t& ms) {
    if(target_duration_ == ms && ms < 0) return;

    target_duration_ = ms;
    emit targetChanged();
}

void TimerModule::setInterval(const uint32_t& ms) {
    if (interval_ == ms && ms < 0) return;

    interval_ = ms;
    emit intervalChanged();
}

int TimerModule::currentTime() const {
    switch (mode_) {
    case CountUp:
        return elapsed_.elapsed();
    case CountDown:
        return 0;
    case Pomodoro:
        if (!target_time_.isValid()) return 0;
        return qMax(0, target_time_.msecsTo(QTime::currentTime()));
    }
}

void TimerModule::start() {
    if (is_running_) stop();

    elapsed_.start();

    // Setting
    switch (mode_) {
    case Pomodoro:
        target_duration_ = 25 * 60 * 1000;

        break;
    case CountDown:
        if (target_duration_ > 0) {
        }

        break;
    case CountUp:
        target_time_ = QTime();

        break;
    default:
        break;
    }

    if (target_duration_ > 0) {
        target_time_ = QTime::currentTime().addMSecs(target_duration_);
    }

    timer_.start(interval_);
    is_running_ = true;

    emit runningChanged();
    emit timeChanged();
}

void TimerModule::stop() {
    if (is_running_) {
        timer_.stop();
        is_running_ = false;
        emit runningChanged();
        emit timeChanged();
    }
}

void TimerModule::reset() {
    stop();
    elapsed_.invalidate();
    target_time_ = QTime();
    emit timeChanged();
}

void TimerModule::notify() {
    notify_state_ = !notify_state_;
    emit notifyStateChanged();
}

void TimerModule::onTimeout() {
    emit timeChanged();
    if ((mode_ == CountDown || mode_ == Pomodoro) && currentTime() <= 0) {
        stop();
        emit finished();
    }
}

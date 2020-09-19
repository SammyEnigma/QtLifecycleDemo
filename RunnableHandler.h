#pragma once

#include <qrunnable.h>
#include <qthreadpool.h>

#include <functional>

//T:调用者类 P:函数参数结构体
template<typename T, typename...params> class RunnableHandler;
template<typename T, typename param, typename...params>
class RunnableHandler<T, param, params...> : public QRunnable {
private:
    RunnableHandler() = delete;
    RunnableHandler(const RunnableHandler&) = delete;
    RunnableHandler& operator=(const RunnableHandler&) = delete;

    RunnableHandler(T* t, const std::function<void(T*, param, params...)>& call, const param& p, const params&...p1) {
        caller = [=]() {
            call(t, p, p1...);
        };
    }

    void run() override {
        caller();
    }

public:
    static void exec(T* t, const std::function<void(T*, param, params...)>& call, const param& p, const params&...p1) {
        QThreadPool::globalInstance()->start(new RunnableHandler(t, call, p, p1...));
    }

private:
    std::function<void()> caller;
};

template<typename T>
class RunnableHandler<T> : public QRunnable {
private:
    RunnableHandler() = delete;
    RunnableHandler(const RunnableHandler&) = delete;
    RunnableHandler& operator=(const RunnableHandler&) = delete;

    explicit RunnableHandler(T* t, const std::function<void(T*)>& call) {
        caller = [=]() {
            call(t);
        };
    }

    void run() override {
        caller();
    }

public:
    static void exec(T* t, const std::function<void(T*)>& call) {
        QThreadPool::globalInstance()->start(new RunnableHandler(t, call));
    }

private:
    std::function<void()> caller;
};
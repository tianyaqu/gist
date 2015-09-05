#ifndef BLOCKINGQUEUE_H
#define BLOCKINGQUEUE_H
#include "noncopyable.h"
#include "task.h"
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>

class BlockingQueue : public NonCopyable
{
public:
    BlockingQueue();
    ~BlockingQueue();
    void put(std::function<void()>&& f);
    std::function<void()> take();
    int size();
    void wakeupAndQuit();
private:
    std::queue<std::function<void()>> queue;
    std::mutex mtx;
    std::condition_variable cond;
    bool quit;
};

#endif // BLOCKINGQUEUE_H

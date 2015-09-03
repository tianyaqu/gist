#ifndef BLOCKINGQUEUE_H
#define BLOCKINGQUEUE_H
#include "noncopyable.h"
#include "task.h"
#include <queue>
#include <mutex>
#include <condition_variable>

class BlockingQueue : public NonCopyable
{
public:
    BlockingQueue();
    ~BlockingQueue();
    void put(Task&&);
    Task take();
    int size();
    void wakeupAndQuit();
private:
    std::queue<Task> queue;
    std::mutex mtx;
    std::condition_variable cond;
    bool quit;
};

#endif // BLOCKINGQUEUE_H

#ifndef THREADPOOL_H
#define THREADPOOL_H
#include "noncopyable.h"
#include "blockingqueue.h"

#include <vector>
#include <thread>
#include <queue>
class ThreadPool : public NonCopyable
{
public:
    ThreadPool(int size);
    ~ThreadPool();
    void start();
    void stop();
    void submit(Task&&);
    BlockingQueue queue;
private:
    void run();
    std::vector<std::thread> pool;
    int size;

    bool running;
};

#endif // THREADPOOL_H

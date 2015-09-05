#include "task.h"

unsigned long long Task::uid = 0;
#if 0
Task::Task(std::string task_name)
{
    name = task_name;
    //task generation is in single thread
    id = uid++;
    name += std::to_string(id);
}
#endif

template<class F, class... Args>
Task::Task(std::string task_name,F&& f, Args&&... args)
{
    name = task_name;
    //task generation is in single thread
    id = uid++;
    name += std::to_string(id);

    using return_type = typename std::result_of<F(Args...)>::type;

    auto task = std::make_shared< std::packaged_task<return_type()> >(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

    std::future<return_type> res = task->get_future();
}

Task::~Task()
{

}

void Task::execute()
{

}


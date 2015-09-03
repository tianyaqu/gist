#include "task.h"

unsigned long long Task::uid = 0;
Task::Task(std::string task_name)
{
    name = task_name;
    //task generation is in single thread
    id = uid++;
    name.append(1,char('0'+id));
}

Task::~Task()
{

}

void Task::execute()
{

}


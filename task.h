#ifndef TASK_H
#define TASK_H
#include <string>

class Task
{
public:
    Task(std::string);
    ~Task();
    unsigned long long get_id(){return id;}
    void execute();
    std::string get_name(){return name;}
private:
    unsigned long long id;
    std::string name;
    static unsigned long long uid;
};

#endif // TASK_H

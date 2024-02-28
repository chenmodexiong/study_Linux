#include <iostream>
#include <vector>

typedef void (*task_t)();

void task1()
{
    std::cout << "lol 刷新日志" << std::endl;
}
void task2()
{
    std::cout << "lol 更新野区，刷新出野怪" << std::endl;
}
void task3()
{
    std::cout << "lol 检测软件更新，如果需要则提示用户" << std::endl;
}
void task4()
{
    std::cout << "lol 用户释放技能，更新血条和蓝量" << std::endl;
}

void LoadTask(std::vector<task_t> *tasks)
{
    tasks->push_back(task1);
    tasks->push_back(task2);
    tasks->push_back(task3);
    tasks->push_back(task4);
}

#include <iostream>
#include <string>

typedef int (*func_t)(void *);

class task_t
{
private:
    /* data */
public:
    std::string name;
    func_t func;
    void *arg;
    int handle_init(int (*fun)(void *),void *arg); 
    int task_start();
    task_t();
    task_t(std::string n,func_t f) : name(n),func(f){}
    ~task_t();
};

task_t::task_t()
{

}
task_t::~task_t()
{
    std::cout << "task END" << std::endl;
}

int task_t::handle_init(int (*fun)(void *),void *arg)
{
    this->arg = arg;
    func = fun;
    return 0;
}
int task_t::task_start()
{
    func((void*)this->arg);
    return 0;
}
int banzhuan(void *arg)
{
    int count = *(int*)arg;
    while(count--)
    {
        std::cout << "还需搬砖数量: " << count << std::endl;
    }
    std::cout << "搬完了" << std::endl;
    return 0;
}
int main()
{
    int a = 10;
    task_t *work = new task_t();
    work->name = "小明";
    work->handle_init(banzhuan,(void*)&a);
    work->task_start();

    delete(work);
}


#include <iostream>
#include <list>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
using namespace std;

class car {
public:
    car(string n, string c) : m_name(n), color(c) {}
    string m_name;
    string color;
    void print() {
        cout << "name: " << m_name << ", color: " << color << endl;
    }
};

list<function<void()>> tasks;
mutex mtx;
condition_variable cv;
bool running = true;

int main() {
    car car1("car1", "red");
    car car2("car2", "blue");
    car car3("car3", "green");

    thread worker([&]() {
        while (running) {
            function<void()> task;

            {
                unique_lock<mutex> lock(mtx);
                cv.wait(lock, [] {
                    return !tasks.empty() || !running;//任务不为空的时候或者线程准备退出的时候，唤醒线程
                });

                if (!running && tasks.empty())
                    return;

                task = move(tasks.front());
                tasks.pop_front();
            }

            task();  // 在锁外执行
        }
    });

    {
        lock_guard<mutex> lock(mtx);
        tasks.push_back([&car1] { car1.print(); });
        tasks.push_back([&car2] { car2.print(); });
        tasks.push_back([&car3] { car3.print(); });
    }
    cv.notify_one();

    for (int i = 0; i < 10; ++i) {
        this_thread::sleep_for(chrono::seconds(1));
        {
            lock_guard<mutex> lock(mtx);
            tasks.push_back([i] {
                cout << "car " << i << " is printing\n";
            });
        }
        cv.notify_one();
    }

    /* 优雅退出 */
    {
        lock_guard<mutex> lock(mtx);
        running = false;
    }
    cv.notify_all();

    worker.join();
    return 0;
}
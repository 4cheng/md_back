#include <iostream>
#include <pthread.h>
#include <mutex>
#include <thread>
using namespace std;

class Singleton 
{
private:
    static Singleton* pinstance_;
    static std::mutex mutex_;

protected:
    Singleton (const std::string value): value_(value)
    {
    }
    ~Singleton(){}
    std::string value_;

public:
    Singleton(Singleton &other) = delete;

    void operator=(const Singleton &) = delete;

    static Singleton *GetInstance(const std::string& value);

    void SomeBusinessLogic()
    {

    }

    std::string value() const {
        return value_;
    }
}; 


Singleton* Singleton::pinstance_{nullptr};
std::mutex Singleton::mutex_;

Singleton *Singleton::GetInstance(const std::string& value)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (pinstance_ == nullptr)
    {
        pinstance_ = new Singleton(value);
    }
    return pinstance_;
}

void ThreadFoo(){
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton* singleton = Singleton::GetInstance("Foo");
    std::cout << singleton->value() << "\n";
}

int main() {

}




#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

class Singleton
{
    private:
        std::string message;
        Singleton(const std::string& m) : message(m) {};
        ~Singleton() {};
    
    protected:
        static std::mutex mutex;

    public:
        Singleton(Singleton& other) = delete;
        void operator=(const Singleton&) = delete;

        static Singleton& getInstance(const std::string& m) 
        {
            std::lock_guard<std::mutex> lock(mutex);
            static Singleton instance(m);
            return instance;
        }

        void printMessage()
        {
            std::cout << message << std::endl;
        }
};

void ThreadOne(const std::string& m)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton& singleton = Singleton::getInstance(m);
    singleton.printMessage();
}

void ThreadTwo(const std::string& m)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton& singleton = Singleton::getInstance(m);
    singleton.printMessage();
}

std::mutex Singleton::mutex;

int main()
{
    std::thread t1(ThreadOne, "One");
    std::thread t2(ThreadTwo, "Two");
    t1.join();
    t2.join();
    return 0;
}
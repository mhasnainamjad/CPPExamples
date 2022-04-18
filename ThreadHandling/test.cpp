#include <iostream>
#include <thread>
#include <time.h>
#include <unistd.h>

#include "thread_guard.h"


void foo() {
    std::cout << "Hello from foo" << std::endl;
}

void raise_exception() {
    usleep(1000);
    std::cout << "Going to raise a runtime exception" << std::endl;
    throw  std::runtime_error("this is run time error");
}

int main()  
{
    std::thread foo_thread(foo);
    ThreadGuard thread_guard(foo_thread);
    try
    {
        raise_exception();
    }
    catch(...) {
        
    }
    return 0;
}
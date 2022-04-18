#pragma once 

#include <iostream>
#include <thread>


class ThreadGuard {
    
    private:
        std::thread &t_;
    
    public:
        explicit ThreadGuard(std::thread & _t) : t_(_t){}

        ~ThreadGuard() {
            if(this->t_.joinable()) {
                std::cout << "Joining thread" << std::endl;
            } else {
                std::cout << " thread is already joined" << std::endl;
            }
        }
        // To make non-copy able
        ThreadGuard(ThreadGuard &) = delete;
        ThreadGuard & operator= (ThreadGuard &) = delete;
};

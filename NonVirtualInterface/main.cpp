#include <iostream>
#include <memory>

class Base 
{
    public:
        void doPrint(const std::string& message)
        {
            std::cout << "Message printed from base class before calling pure virtual function" << std::endl;
            this->print(message);
            std::cout << "Message printed from base class after calling pure virtual function" << std::endl;
        }
        virtual ~Base() {};
    private:
        virtual void print(const std::string& message) = 0;
};

class Derived final: public Base 
{
    public:
        ~Derived() {};
    private:
        void print(const std::string& message) override
        {
            std::cout << "Message printed from derived class " << message << std::endl;
        }

};

int main()
{
    std::unique_ptr<Base> obj = std::make_unique<Derived>();
    std::string m = "hello world";
    obj->doPrint(m);
    return 0;
}

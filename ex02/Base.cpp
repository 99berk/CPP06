#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>
#include <cstdlib>

Base::~Base() {}

Base* Base::genereate()
{
    srand(time(NULL));
    int derived = rand();

    switch (derived % 3)
    {
        case 0:{
            std::cout << "Generated class is A" << std::endl;
            A* ptr = new A;
            return ptr;
        }
        case 1:{
            std::cout << "Generated class is B" << std::endl;
            B* ptr2 = new B;
            return ptr2;
        }
        case 2: {
            std::cout << "Generated class is C" << std::endl;
            C* ptr3 = new C;
            return ptr3;
        }
    }
    std::cout << "derived: " << derived % 3 << std::endl;
    return NULL;
}

void Base::idenitify(Base* p)
{
    if (dynamic_cast<A*>(p))
    {
        std::cout << "The object is A!" << std::endl;
        return ;
    }
    if (dynamic_cast<B*>(p))
    {
        std::cout << "The object is B!" << std::endl;
        return ;
    }
    if (dynamic_cast<C*>(p))
    {
        std::cout << "The object is C!" << std::endl;
        return ;
    }
    std::cout << "Object is not idenified" << std::endl;
}

void Base::idenitify(Base& p)
{
    try
    {
        A& d = dynamic_cast<A&>(p);
        (void)d;
        std::cout << "The object is A!" << std::endl;
        return;
    }
    catch(const std::exception& e){}
    
	try
    {
        B& d = dynamic_cast<B&>(p);
        (void)d;
        std::cout << "The object is B!" << std::endl;
        return;
    }
    catch(const std::exception& e) {}
    
	try
    {
        C& d = dynamic_cast<C&>(p);
        (void)d;
        std::cout << "The object is C!" << std::endl;
        return;
    }
    catch(const std::exception& e) {}
}

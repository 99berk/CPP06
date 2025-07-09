#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>

int main()
{
    Base base;

    {
        Base* ptr;
        
        ptr = base.genereate();
        std::cout << "Test case idenify(Base& p): "; 
        base.idenitify(ptr);
        std::cout << "Test case idenify(Base* p): "; 
        base.idenitify(*ptr);
        
        delete ptr;
    }
}

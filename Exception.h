#ifndef MYEXCEPTION
#define MYEXCEPTION

#include <exception>
#include <string>

class myException :public std::exception
{
public:
    myException(const char* msg = "", int i = -1)
        :msg(msg), indx(i){}
    const char* what()const noexcept override { return msg; }

    const char* msg;
    int indx;
};

#endif // !MYEXCEPTION

#include <iostream>
#ifdef _WIN32
#include <process.h>
#else
#include <unistd.h>
#endif

int main()
{
    #pragma omp parallel
    {
        std::cout << "Hello world, pid = " << getpid();
    }
}
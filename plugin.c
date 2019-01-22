#include <stdio.h>

#ifdef _WIN32
#define PLUGIN_API __declspec(dllexport)
#else
#define PLUGIN_API
#endif

PLUGIN_API const char *myname = "foobar";

PLUGIN_API int adder(int a, int b)
{
    return a+b;
}

PLUGIN_API void printer()
{
    printf("Hello World");
}
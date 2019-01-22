#ifdef _WIN32
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

#include <stdio.h>

typedef int (*adder_signature)(int a, int b);

int main(int argc, char **argv)
{
#ifdef _WIN32
    HMODULE handle = LoadLibrary("plugin.dll");
    if (!handle)
    {
        printf("Error loading library: %s\n");
        return -1;
    }
    adder_signature adder = (adder_signature)GetProcAddress(handle, "adder");
#else
    void *handle = dlopen("plugin.so", RTLD_LAZY);
    if (!handle)
    {
        printf("Error loading library: %s\n", dlerror());
        return -1;
    }
    adder_signature adder = (adder_signature)dlsym(handle, "adder");
#endif
    if (!adder)
    {
        printf("Unable to find symbol adder\n");
        return -1;
    }

    printf("adder() result is %d\n", adder(1, 2));
    return 0;
}
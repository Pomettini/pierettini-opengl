clang -shared -o plugin.so plugin.c
clang -o main main.c
./main
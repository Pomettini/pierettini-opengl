clang -shared -o plugin.so plugin.c
clang -o main main.c
clang -o draw draw.c src/glad.c -lSDL2 -Iinclude/ -L. -lfbxc
./draw
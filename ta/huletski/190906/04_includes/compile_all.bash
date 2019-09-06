# cpp src/main.c -Iinclude ; preporcessor

mkdir -p bin # use bin for binary files, -p - @see man

echo Compile my_fav_func.o
gcc -c src/my_fav_func.c -o bin/my_fav_func.o -Iinclude
echo Compile main.o
gcc -c src/main.c -o bin/main.o -Iinclude
echo Link main
gcc bin/my_fav_func.o bin/main.o -o main

# Undefined recerence
#gcc bin/main.o -o main

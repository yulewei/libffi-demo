编译运行示例：

``` sh
$ brew install libffi
$ gcc -I/usr/local/Cellar/libffi/3.0.13/lib/libffi-3.0.13/include  \
-L/usr/local/Cellar/libffi/3.0.13/lib -lffi main.c -o ffidemo
$ ./ffidemo 4 1 2 3 4
10
```

或者用 cmake 方式编译运行：
```
$ brew install cmake
$ cmake .
$ make
$ ./ffidemo 4 1 2 3 4
10
```

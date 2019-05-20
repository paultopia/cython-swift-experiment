## Stage 1: get python code runnable from c.

from in a pipenv shell, 

`cython hello.pyx` produces hello.c

```
gcc `python2-config --cflags --ldflags` -o compiledhi hello.c sayhi.c
```

seems to get it all compiled and runnable from the command line.  After some [strugs](https://stackoverflow.com/questions/56212765/gcc-cant-see-my-cython-hello-world-function?noredirect=1#comment99046691_56212765)



## Stage 2: build an easy c library to put into swift:

more or less working from [this](https://www.cs.swarthmore.edu/~newhall/unixhelp/howto_C_libraries.html) and [this](https://oleb.net/blog/2017/12/importing-c-library-into-swift/)

putting everything in files entitled `hilib`

compiling into an object file with 

```
gcc `python2-config --cflags --ldflags` -o hilib.o -c hello.c hilib.c
```

fails with: 

```
clang: warning: -lpython2.7: 'linker' input unused [-Wunused-command-line-argument]
clang: warning: -ldl: 'linker' input unused [-Wunused-command-line-argument]
clang: warning: -framework CoreFoundation: 'linker' input unused [-Wunused-command-line-argument]
clang: error: cannot specify -o when generating multiple output files
```


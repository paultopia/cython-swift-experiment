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

trying a two stage version for shits and giggles.  First trying to get the python thing compiled on its own: 

```
gcc `python2-config --cflags --ldflags` -o hello.o -c hello.c
```

which I *believe/hope* will get me an object file for the stuff from python to shove into the c library...  running generates: 

```
clang: warning: -lpython2.7: 'linker' input unused [-Wunused-command-line-argument]
clang: warning: -ldl: 'linker' input unused [-Wunused-command-line-argument]
clang: warning: -framework CoreFoundation: 'linker' input unused [-Wunused-command-line-argument]
clang: warning: argument unused during compilation: '-L/usr/local/opt/python@2/Frameworks/Python.framework/Versions/2.7/lib/python2.7/config' [-Wunused-command-line-argument]
```

and then to get the ultimate library:

```
gcc `python2-config --cflags --ldflags` -o hilib.o -c hilib.c
```

which throws more warnings: 

```
clang: warning: -lpython2.7: 'linker' input unused [-Wunused-command-line-argument]
clang: warning: -ldl: 'linker' input unused [-Wunused-command-line-argument]
clang: warning: -framework CoreFoundation: 'linker' input unused [-Wunused-command-line-argument]
clang: warning: argument unused during compilation: '-L/usr/local/opt/python@2/Frameworks/Python.framework/Versions/2.7/lib/python2.7/config' [-Wunused-command-line-argument]
In file included from hilib.c:3:
./hilib.h:4:17: warning: this function declaration is not a prototype [-Wstrict-prototypes]
extern void pyhi();
                ^
                 void
1 warning generated.
```

but it compiles, so who knows, maybe it'll work?

creating the swift lib from that second tutorial above at [https://github.com/paultopia/cython-swift-experiment-swiftlib](https://github.com/paultopia/cython-swift-experiment-swiftlib) because I don't wanna muck around with sub-repos and such.

----

but swift run fails with: 

```
ld: warning: Could not find auto-linked library 'hilib'
Undefined symbols for architecture x86_64:
  "_pyhi", referenced from:
      _main in main.swift.o
ld: symbol(s) not found for architecture x86_64
```

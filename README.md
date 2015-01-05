##Building

###Native
```
mkdir build
cd build
CXX=`which clang++` cmake ..
make
./main
```

###Web
```
mkdir build
cd build
emcmake cmake ..
make
open main.html
```

##Notes
When switching builds, you __need__ to clobber the `build` dir.
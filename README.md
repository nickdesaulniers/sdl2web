##Building

###Native
```
mkdir build
cd build
CXX=`which clang++` cmake ..
make
./main
```

###iOS
```
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=../iOS.cmake -DIOS_PLATFORM=SIMULATOR -DCMAKE_IOS_SDK_ROOT=/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator7.1.sdk/ -GXcode ..
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
# Arduino + threepp

This is a demo of connecting an Arduino with a desktop C++ program.
Communication is done through serial and the data is serialized on the wire as JSON.

Threepp is used to visualise the data received from the Arduino.
[PlatformIO](https://platformio.org/), which is integrated in CLion, is used to handle the Arduino code.

## Arduino program

On the Arduino side, the program assumes that two potensiometers are available and connected to pin `A0` and `A1`.

## Desktop program

As `vcpkg` is used, you need to tell CMake about it in order for dependency resolution to work: 

`-DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake`

###### Building under MinGW

Under MinGW you'll need to specify the vcpkg triplet:
```shell
-DVCPKG_TARGET_TRIPLET=x64-mingw-[static|dynamic]  # choose either `static` or `dynamic`.
-DVCPKG_HOST_TRIPLET=x64-mingw-[static|dynamic]    # <-- needed only if MSVC cannot be found. 
```

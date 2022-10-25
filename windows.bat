mkdir build
cd build && conan install .. --build=missing && cmake -DCMAKE_BUILD_TYPE="Release" .. -G "Visual Studio 17" -A x64 && cmake --build . --config Release && cpack -G WIX -C Release

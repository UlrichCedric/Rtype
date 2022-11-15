mkdir build
cd build && conan install .. --build=missing -o SFML:static=True -s build_type=Release && cmake -DCMAKE_BUILD_TYPE="RELEASE" .. -G "Visual Studio 17" -A x64 && cmake --build . --config Release && cpack -G WIX -C Release

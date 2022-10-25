cmake_minimum_required(VERSION 3.18)
project(rtype)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)

include(build/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)
set(CMAKE_BUILD_TYPE Release)

if (MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++20 -D_WIN32_WINNT=0x0A00")
else()
  set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -lstdc++fs -std=c++2a -pthread")
  SET(CMAKE_CXX_FLAGS "-g")
endif()

find_package(Boost)

set(SRC_CLIENT src/client/main.cpp
	src/client/Windows.cpp
	src/client/Image.cpp
	src/client/Music.cpp
	src/client/Text.cpp
	src/client/Config.cpp
	src/client/Paralax.cpp
	src/client/Client.cpp
)

set(SRC_SERVER
	src/server/main.cpp
	src/server/Server.cpp
)

INCLUDE_DIRECTORIES(
        "${CMAKE_CURRENT_SOURCE_DIR}/src/client/"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/server/"
		"${CMAKE_CURRENT_SOURCE_DIR}/src/server/ecs/"
		"${CMAKE_CURRENT_SOURCE_DIR}/src/server/ecs/Systems"
		"${CMAKE_CURRENT_SOURCE_DIR}/src/server/ecs/Components"
)

add_executable(r-type_client ${SRC_CLIENT})
target_link_libraries(r-type_client CONAN_PKG::asio
	CONAN_PKG::boost
	CONAN_PKG::sfml
)

target_include_directories(r-type_client PUBLIC
			${CONAN_INCLUDE_DIRS_SFML}
			${CONAN_INCLUDE_DIRS_ASIO}
			${CONAN_INCLUDE_DIRS_BOOST}
			)

add_executable(r-type_server ${SRC_SERVER})
target_link_libraries(r-type_server CONAN_PKG::asio
									CONAN_PKG::boost
									)
target_include_directories(r-type_server PUBLIC
			${CONAN_INCLUDE_DIRS_ASIO}
			${CONAN_INCLUDE_DIRS_BOOST}
			)

SET_PROPERTY(TARGET r-type_client PROPERTY CXX_STANDARD 20)
SET_PROPERTY(TARGET r-type_server PROPERTY CXX_STANDARD 20)
ADD_CUSTOM_COMMAND(TARGET r-type_client POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets/ $<TARGET_FILE_DIR:r-type_client>/assets/)
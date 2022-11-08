cmake_minimum_required(VERSION 3.18)
project(rtype)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)

include(build/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)
set(CMAKE_BUILD_TYPE REALASE)

if (MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++20 -D_WIN32_WINNT=0x0A00")
else()
  set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -lstdc++fs -std=c++2a -pthread")
  SET(CMAKE_CXX_FLAGS "-g")
endif()

find_package(Boost)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(SRC_CLIENT src/client/main.cpp
	src/client/Windows.cpp
	src/client/game/Health.cpp
	src/client/utils/Image.cpp
	src/client/utils/Music.cpp
	src/client/utils/Text.cpp
	src/client/utils/Config.cpp
	src/client/utils/Paralax.cpp
	src/client/game/Client.cpp
	src/client/game/InGame.cpp
	src/client/game/Event.cpp
	src/client/game/Player.cpp
	src/client/game/Ennemy.cpp
	src/client/pause/Pause.cpp
	src/client/game/Shoot.cpp
	src/client/utils/Button.cpp
	src/client/menu/Display.cpp
	src/client/menu/Events.cpp
	src/client/menu/GameLobby.cpp
	src/client/menu/Initialisations.cpp
	src/client/menu/Menu.cpp
	src/client/utils/Sound.cpp
)

set(SRC_SERVER
	src/server/udp_server.cpp
	src/server/Server.cpp
)

INCLUDE_DIRECTORIES(
        "${CMAKE_CURRENT_SOURCE_DIR}/src/client/"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/client/game/"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/client/utils/"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/client/pause/"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/client/menu/"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/server/"
		"${CMAKE_CURRENT_SOURCE_DIR}/src/server/ecs/"
		"${CMAKE_CURRENT_SOURCE_DIR}/src/server/ecs/Systems"
		"${CMAKE_CURRENT_SOURCE_DIR}/src/server/ecs/Components"
)

add_executable(r-type_client ${SRC_CLIENT})
target_link_libraries(r-type_client
	CONAN_PKG::boost
	CONAN_PKG::sfml
)

target_include_directories(r-type_client PUBLIC
			${CONAN_INCLUDE_DIRS_SFML}
			${CONAN_INCLUDE_DIRS_BOOST}
			)

add_executable(r-type_server ${SRC_SERVER})
target_link_libraries(r-type_server CONAN_PKG::boost)

target_include_directories(r-type_server PUBLIC
			${CONAN_INCLUDE_DIRS_BOOST}
			)

SET_PROPERTY(TARGET r-type_client PROPERTY CXX_STANDARD 20)
SET_PROPERTY(TARGET r-type_server PROPERTY CXX_STANDARD 20)

if (MSVC)
	set(CPACK_GENERATOR "WIX")
	set(CPACK_WIX_UPGRADE_GUID "C0C0C0C0-C0C0-C0C0-C0C0-C0C0C0C0C0C0")
	set(CPACK_WIX_PRODUCT_GUID "C0C0C0C0-C0C0-C0C0-C0C0-C0C0C0C0C0C0")
	set(CPACK_WIX_PRODUCT_ICON "${CMAKE_SOURCE_DIR}/assets/icon.ico")
	set(CPACK_DESKTOP_SHORTCUTS "R-Type")
	set(CPACK_START_MENU_SHORTCUTS "R-Type")
	set(CPACK_CREATE_DESKTOP_LINKS "R-Type")
	set(CPACK_PACKAGE_EXECUTABLES "R-Type-cli" "R-Type-server")
	set(CPACK_PACKAGE_NAME "R-Type")
	set(CPACK_PACKAGE_VENDOR "R-Type")
	set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "R-Type")
	configure_file("${CMAKE_SOURCE_DIR}/LICENSE"
  		"${CMAKE_BINARY_DIR}/LICENSE.txt" COPYONLY)
	set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_BINARY_DIR}/LICENSE.txt")
	install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/assets" DESTINATION bin)
	 install(TARGETS r-type_client
	 RUNTIME
	 DESTINATION bin
	 COMPONENT applications
	 )
   install(TARGETS r-type_server
	RUNTIME
	DESTINATION bin
	COMPONENT applications
	 )
else()
	install(TARGETS r-type_client
	  COMPONENT linapp
	  RUNTIME DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/Compilateur"
	  LIBRARY DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/Compilateur"
	  DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/Compilateur"
  	)
	install(TARGETS r-type_server
	  COMPONENT linapp
	  RUNTIME DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/Compilateur"
	  LIBRARY DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/Compilateur"
	  DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/Compilateur"
  	)
  	SET(CMAKE_CXX_FLAGS "-g")
  	SET(CPACK_GENERATOR "DEB")
	SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "KK") #required
endif()

INCLUDE(CPack)
ADD_CUSTOM_COMMAND(TARGET r-type_client POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets/ $<TARGET_FILE_DIR:r-type_client>/assets/)
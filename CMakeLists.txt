project(PetrolStation)
cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_definitions(-DGTEST_STDLIB_CXX11 -DGTEST_LANG_CXX11)

include_directories(.)
include_directories(SYSTEM libs/gtest/include)

FILE(GLOB HEADERS_LIST *.h)
FILE(GLOB SRC_LIST *.cpp)

add_executable(${PROJECT_NAME} 
               ${SRC_LIST} 
			   ${HEADERS_LIST}
               ${PROJECT_SOURCE_DIR}/libs/gtest/src/gmock_main
			   ${PROJECT_SOURCE_DIR}/libs/gtest/src/gmock-gtest-all
			   )

if (${UNIX})
	target_link_libraries(${PROJECT_NAME} pthread)
endif (${UNIX})


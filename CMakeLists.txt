project(PetrolStation)
cmake_minimum_required(VERSION 3.1)

#set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(.)
include_directories(SYSTEM libs/gtest/include)

aux_source_directory(. SRC_LIST)

add_executable(${PROJECT_NAME} 
               ${SRC_LIST} 
               ${PROJECT_SOURCE_DIR}/libs/gtest/src/gmock_main
			   ${PROJECT_SOURCE_DIR}/libs/gtest/src/gmock-gtest-all
			   )

if (${UNIX})
	target_link_libraries(${PROJECT_NAME} pthread)
endif (${UNIX})
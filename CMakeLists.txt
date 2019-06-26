cmake_minimum_required (VERSION 3.0)
set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -I /Users/nelson/Downloads/usr/local/include")
FILE(GLOB_RECURSE sources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
FILE(GLOB_RECURSE headers RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)
project (CannonBall)
# add the executable
#add_executable(
	#fire src/main_long_int.cpp#${sources}
	#)

add_executable(
	cnl src/cnl_types.cpp#${sources}
)

add_executable(
	std src/std_types.cpp#${sources}
)

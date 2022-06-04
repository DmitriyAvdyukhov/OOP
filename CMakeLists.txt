cmake_minimum_required(VERSION 3.0)

project(OOP)
set(CMAKE_CXX_STANDARD 17)

set(FILES_PROJECT main.cpp 
                  dz1.h 
				  dz2.h
				  dz3.h dz3.cpp
				  dz4.h dz4.cpp
				  dz5.h dz5.cpp
				  dz6.h
				  dz7.h
				  black_jack.h black_jack.cpp)
				  
add_executable(main ${FILES_PROJECT})
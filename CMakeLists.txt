cmake_minimum_required(VERSION 3.10)
project(corefincpp)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# path include directory
include_directories(include/headers)

# Add the executable
add_executable(corefincpp 
src/main.cpp
src/modules/auth.cpp
src/modules/fileio.cpp
src/modules/financeCRUD.cpp
src/modules/clearScreen.cpp
src/extlib/color.cpp
)
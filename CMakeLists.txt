cmake_minimum_required(VERSION 3.5)

project(CppBench LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(CppBench
    include/cppbench.hpp
    examples/simple.cpp)

target_include_directories(CppBench PRIVATE include)

include(GNUInstallDirs)
install(TARGETS CppBench
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

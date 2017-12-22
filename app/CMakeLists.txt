#指定需要CMAKE的最小版本
cmake_minimum_required(VERSION 3.4.1)


#设置生成的so动态库最后输出的路径
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../jniLibs/${ANDROID_ABI})


#多文件cpp指定路径
file(GLOB cpp_srcs "src/main/cpp/*.c" "src/main/cpp/*.cpp" "src/main/cpp/*.h")
#添加库文件
add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             ${cpp_srcs} )


# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )


# 设置头文件
#target_include_directories(hello-libs PRIVATE ${distribution_DIR}/gmath/include ${distribution_DIR}/gperf/include)



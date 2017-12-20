#指定需要CMAKE的最小版本
cmake_minimum_required(VERSION 3.4.1)

#设置头文件搜索路径（和此txt同个路径的头文件无需设置），可选
#INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/common)


#指定用到的系统库或者NDK库或者第三方库的搜索路径，可选。
#LINK_DIRECTORIES(/usr/local/lib)


#设置生成的so动态库最后输出的路径
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../jniLibs/${ANDROID_ABI})


# 创建一个静态库 lib_gmath 直接引用libgmath.a
#add_library(lib_gmath STATIC IMPORTED)
#set_target_properties(lib_gmath PROPERTIES IMPORTED_LOCATION
#    ${distribution_DIR}/gmath/lib/${ANDROID_ABI}/libgmath.a)

# 创建一个动态库 lib_gperf 直接引用libgperf.so
#add_library(lib_gperf SHARED IMPORTED)
#set_target_properties(lib_gperf PROPERTIES IMPORTED_LOCATION
#    ${distribution_DIR}/gperf/lib/${ANDROID_ABI}/libgperf.so)

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


#设置链接库
target_link_libraries( # Specifies the target library.
                       native-lib
                       android
                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )


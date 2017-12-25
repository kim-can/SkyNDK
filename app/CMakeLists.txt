#指定需要CMAKE的最小版本
cmake_minimum_required(VERSION 3.4.1)

#设置生成的so动态库最后输出的路径
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../jniLibs/${ANDROID_ABI})

#去掉二进制无用改代码
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -s")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s")

#多文件cpp指定路径
file(GLOB cpp_src "src/main/cpp/*.cpp" "src/main/cpp/*.h")
#添加库文件
add_library( # Sets the name of the library.
             SkyClientSDK

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             ${cpp_src} )

#日志
find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

#设置链接库
target_link_libraries( # Specifies the target library.
                       SkyClientSDK
                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )

#share——抽出
function(get_stl_info stl_path stl_name)
   # assume app not uses shared stl lib
   set(${stl_path} "" PARENT_SCOPE)
   if(NOT ${ANDROID_STL} MATCHES "_shared")
       return()
   endif()

   # using shared lib, config lib name and path
   if("${ANDROID_STL}" MATCHES "c\\\+\\\+_")
       # app uses c++_shared for stl type
       set(stlPath "llvm-libc++/libs/${ANDROID_ABI}")
       set(stlName "libc++_shared.so")
   elseif(${ANDROID_STL} MATCHES "gnustl_")
       set(stlPath "gnu-libstdc++/4.9/libs/${ANDROID_ABI}")
       set(stlName "libgnustl_shared.so")
   else()
       # this sample not supporting other stl types
       message(FATAL_ERROR "Not Suppored STL type: ${ANDROID_STL}")
       return()
   endif()

   set(${stl_path} ${ANDROID_NDK}/sources/cxx-stl/${stlPath} PARENT_SCOPE)
   set(${stl_name} ${stlName} PARENT_SCOPE)
endfunction()

# force copying needed shared stl lib into ${project}/app/src/main/jniLibs
# so it will be packed into APK
get_stl_info(ndk_stl_path  ndk_stl_name)
if(NOT ${ndk_stl_path} STREQUAL "")
    set(jniLibs_dir "${CMAKE_CURRENT_SOURCE_DIR}/../jniLibs")
    add_custom_command(TARGET SkyClientSDK PRE_BUILD
                   COMMAND "${CMAKE_COMMAND}" -E
                   copy ${ndk_stl_path}/${ndk_stl_name}
                   "${jniLibs_dir}/${ANDROID_ABI}/${ndk_stl_name}"
                   COMMENT "Copying Shared library to the packing directory")
endif()

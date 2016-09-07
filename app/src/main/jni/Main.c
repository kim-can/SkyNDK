//引入上面生成的头文件，并实现头文件中声明的方法
#include "sky_skyndk_MainActivity.h"
JNIEXPORT jstring JNICALL Java_sky_skyndk_MainActivity_getSkyNDKText
        (JNIEnv *env, jobject obj){
    char *str="我是skyJC, 这里是C语言返回的内容";
    return (*env)->NewStringUTF(env, str);
}
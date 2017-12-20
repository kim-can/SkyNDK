#include <jni.h>
#include <string>

extern "C"
JNIEXPORT jstring

JNICALL
Java_sky_skyndk_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++1111";
    return env->NewStringUTF(hello.c_str());
}

//
// Created by 金灿 on 2017/12/17.
//

#include <jni.h>
#include <string>
#include <map>
#include <iostream>
#include <android/log.h>

#include "md5.h"

#define LOG_TAG "System.out.cpp"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
using namespace std;

//java hashmap转c map
map<string, string> jmap2cmap(JNIEnv *env, jobject jobj) {
    map<string, string> cmap;
    jclass jmapclass = env->FindClass("java/util/HashMap");
    jmethodID jkeysetmid = env->GetMethodID(jmapclass, "keySet", "()Ljava/util/Set;");
    jmethodID jgetmid = env->GetMethodID(jmapclass, "get",
                                         "(Ljava/lang/Object;)Ljava/lang/Object;");
    jobject jsetkey = env->CallObjectMethod(jobj, jkeysetmid);
    jclass jsetclass = env->FindClass("java/util/Set");
    jmethodID jtoArraymid = env->GetMethodID(jsetclass, "toArray", "()[Ljava/lang/Object;");
    jobjectArray jobjArray = (jobjectArray) env->CallObjectMethod(jsetkey, jtoArraymid);
    jsize arraysize = env->GetArrayLength(jobjArray);
    int i = 0;
    for (i = 0; i < arraysize; i++) {
        jstring jkey = (jstring) env->GetObjectArrayElement(jobjArray, i);
        jstring jvalue = (jstring) env->CallObjectMethod(jobj, jgetmid, jkey);
        if (jvalue == NULL) {
            continue;
        }
        char *key = (char *) env->GetStringUTFChars(jkey, 0);
        char *value = (char *) env->GetStringUTFChars(jvalue, 0);
        cmap[key] = value;
    }
    return cmap;
}

extern "C"

JNIEXPORT jstring
JNICALL
Java_sky_skyndk_MainActivity_md5(
        JNIEnv *env,
        jobject obj, jobject hashmap) {
    if (hashmap == NULL) {
//        LOGD("param is NULL");
        return NULL;
    }

    //获得参数
    map<string, string> mapStudent = jmap2cmap(env, hashmap);
    //开始遍历
    map<string, string>::iterator iter;
    iter = mapStudent.begin();
    string needMD5;

    while (iter != mapStudent.end()) {
        if (iter->second.empty()) {
            iter++;
            continue;
        }
        needMD5 += iter->first + "=" + iter->second;
        iter++;
        if (iter != mapStudent.end()) {
            needMD5 += "&";
        }
    }

    string print = "加密前:" + needMD5;

//    LOGD("加密前: %s", print.c_str());

    MD5 md5;
    string sMD5 = md5.ToMD5(needMD5);

    print = "加密后:" + sMD5;

//    LOGD("加密后: %s", print.c_str());

    cout << "加密后:" << sMD5 << endl;
    return env->NewStringUTF(sMD5.c_str());
}




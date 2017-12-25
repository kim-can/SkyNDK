//
// Created by 金灿 on 2017/12/17.
//

#include <jni.h>
#include <map>
//#include <android/log.h>
#include "md5.h"

//#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "security", __VA_ARGS__))
//#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "security", __VA_ARGS__))

using namespace std;


static int verifySign(JNIEnv *env);

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = NULL;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) {
        return JNI_ERR;
    }
    if (verifySign(env) == JNI_OK) {
        return JNI_VERSION_1_4;
    }
//    LOGE("签名不一致!");
    return JNI_ERR;
}


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
//        LOGI("param is NULL");
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

//    LOGI("加密前: %s", print.c_str());

    MD5 md5;
    string sMD5 = md5.ToMD5(print);

    print = "加密后:" + sMD5;

//    LOGI("加密后: %s", print.c_str());
    return env->NewStringUTF(sMD5.c_str());
}


static const char *SIGN = "3082030d308201f5a003020102020470ff5bf8300d06092a864886f70d01010b05003037310b30090603550406130255533110300e060355040a1307416e64726f6964311630140603550403130d416e64726f6964204465627567301e170d3134313232373033323534365a170d3434313231393033323534365a3037310b30090603550406130255533110300e060355040a1307416e64726f6964311630140603550403130d416e64726f696420446562756730820122300d06092a864886f70d01010105000382010f003082010a0282010100c7c3a3e55f749d8ac080fa6fc624fd1421121de6673a073ab03d6fc4dca9d115f51311c6ade528f1f071272853b365d073ce5b6b49e6a90a1949df816f154c741a3c1599b913f2bda1be3050dc3685154dd21616a053728cdb8fa02d9adb86e8debc3b27b6bb5f7bd7d09af2ccb9b0e8d31aad0bcab55e1041d1b87dd230ff81890dd6c6bb8077c7d4946a55229863133bfcdfb8190e6579df7b0248be4395117ca867152b18f8882ebc74cfc578cb0e777eef7ef6c43a683b45dc2f75be1bf477051a88e77df48180f6aa5c734a0cfa71b88df3795589c2cd7ebd118b4d13789c73e3f3418e0ac1688ded0cd139d995edd0f6fa3c102e1d2aab987e0334b5510203010001a321301f301d0603551d0e041604144ef07e54a861a7854d26f24b9853a6773f1e6bdf300d06092a864886f70d01010b050003820101007e9f3e9320ead920ffa4659aab1a0f4cd413e47722e9f09ebce8de355974a2901530f72e8787cc794afc7d605eb42df655801b75e7054891f9de7245a83787c46a2c3cad5e4432dfe1bf1b7022eb5e97b505f9262f2a78fe12cce8139574bf0933ae3b166e4f2e75f53faceccb558580b885f5f9334b450957ff63a3e88a3ff7d1c96186f74ca885e0558f34d55450a205cacd21c7157781f4907c47e33395d15c9f67b083caa58eac91f512dd81441f577330a18c1f374c6fc9ea7ea85dd902498a823628dbff5263a5eb58601be7f7de11334e810e8a3237e1ed9bd509bc398caa4b9831510def4fceddbc12f35df342b5a4db9e51027a936d006b914ff26e";

static jobject getApplication(JNIEnv *env) {
    jobject application = NULL;
    jclass activity_thread_clz = env->FindClass("android/app/ActivityThread");
    if (activity_thread_clz != NULL) {
        jmethodID currentApplication = env->GetStaticMethodID(
                activity_thread_clz, "currentApplication", "()Landroid/app/Application;");
        if (currentApplication != NULL) {
            application = env->CallStaticObjectMethod(activity_thread_clz, currentApplication);
        } else {
//            LOGE("Cannot find method: currentApplication() in ActivityThread.");
        }
        env->DeleteLocalRef(activity_thread_clz);
    } else {
//        LOGE("Cannot find class: android.app.ActivityThread");
    }

    return application;
}

int verifySign(JNIEnv *env) {
    // Application object
    jobject application = getApplication(env);
    if (application == NULL) {
        return JNI_ERR;
    }
    // Context(ContextWrapper) class
    jclass context_clz = env->GetObjectClass(application);
    // getPackageManager()
    jmethodID getPackageManager = env->GetMethodID(context_clz, "getPackageManager",
                                                   "()Landroid/content/pm/PackageManager;");
    // android.content.pm.PackageManager object
    jobject package_manager = env->CallObjectMethod(application, getPackageManager);
    // PackageManager class
    jclass package_manager_clz = env->GetObjectClass(package_manager);
    // getPackageInfo()
    jmethodID getPackageInfo = env->GetMethodID(package_manager_clz, "getPackageInfo",
                                                "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
    // context.getPackageName()
    jmethodID getPackageName = env->GetMethodID(context_clz, "getPackageName",
                                                "()Ljava/lang/String;");
    // call getPackageName() and cast from jobject to jstring
    jstring package_name = (jstring) (env->CallObjectMethod(application, getPackageName));
    // PackageInfo object
    jobject package_info = env->CallObjectMethod(package_manager, getPackageInfo, package_name,
                                                 64);
    // class PackageInfo
    jclass package_info_clz = env->GetObjectClass(package_info);
    // field signatures
    jfieldID signatures_field = env->GetFieldID(package_info_clz, "signatures",
                                                "[Landroid/content/pm/Signature;");
    jobject signatures = env->GetObjectField(package_info, signatures_field);
    jobjectArray signatures_array = (jobjectArray) signatures;
    jobject signature0 = env->GetObjectArrayElement(signatures_array, 0);
    jclass signature_clz = env->GetObjectClass(signature0);

    jmethodID toCharsString = env->GetMethodID(signature_clz, "toCharsString",
                                               "()Ljava/lang/String;");
    // call toCharsString()
    jstring signature_str = (jstring) (env->CallObjectMethod(signature0, toCharsString));

    // release
    env->DeleteLocalRef(application);
    env->DeleteLocalRef(context_clz);
    env->DeleteLocalRef(package_manager);
    env->DeleteLocalRef(package_manager_clz);
    env->DeleteLocalRef(package_name);
    env->DeleteLocalRef(package_info);
    env->DeleteLocalRef(package_info_clz);
    env->DeleteLocalRef(signatures);
    env->DeleteLocalRef(signature0);
    env->DeleteLocalRef(signature_clz);

    const char *sign = env->GetStringUTFChars(signature_str, NULL);
    if (sign == NULL) {
//        LOGE("分配内存失败");
        return JNI_ERR;
    }

//    LOGI("应用中读取到的签名为 ：%s", sign);
//    LOGI("native中预置的签名为：%s", SIGN);
    int result = strcmp(sign, SIGN);
    // 使用之后要释放这段内存
    env->ReleaseStringUTFChars(signature_str, sign);
    env->DeleteLocalRef(signature_str);
    if (result == 0) { // 签名一致
        return JNI_OK;
    }

    return JNI_ERR;
}


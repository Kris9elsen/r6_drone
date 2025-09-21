#include <jni.h>
#include <string>
#include "UDP_Receiver.h"

UDP_Reciever udp_connection(5000);

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_drone_1controller_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello nigger from C++ with counter: ";


    return env->NewStringUTF(hello.c_str());
}

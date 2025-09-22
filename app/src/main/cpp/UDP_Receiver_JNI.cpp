#include "UDP_Receiver.h"
#include <jni.h>


static UDP_Receiver* receiver = nullptr;

extern "C" {
// Start UDP_receiver on a given port
JNIEXPORT jboolean JNICALL
Java_com_example_drone_1controller_MainActivity_start_1UDP_1receiver(JNIEnv *env, jobject, jint port) {
    if (receiver != nullptr) {
        delete receiver;
    }

    receiver = new UDP_Receiver(port);
    return receiver->start_UDP_receiver() ? JNI_TRUE : JNI_FALSE;
}

// Stop UDP receiver
JNIEXPORT jboolean JNICALL
Java_com_example_drone_1controller_MainActivity_close_1UDP_1receiver(JNIEnv *env, jobject) {
    if (receiver != nullptr) {
        jboolean result = receiver->close_UDP_receiver() ? JNI_TRUE : JNI_FALSE;
        delete receiver;
        receiver = nullptr;
        return result;
    }

    return JNI_TRUE; // Does not exist
}

// Receive UDP packet and send data to Kotlin
JNIEXPORT jbyteArray JNICALL
Java_com_example_drone_1controller_MainActivity_get_1frame(JNIEnv *env, jobject) {
    auto packet = receiver->receive_packet();
    if (packet.empty()) return nullptr;

    jbyteArray byte_array = env->NewByteArray(packet.size());
    env->SetByteArrayRegion(byte_array, 0, packet.size(),
                            reinterpret_cast<const jbyte *>(packet.data()));
    return byte_array;
}

} // Extern C



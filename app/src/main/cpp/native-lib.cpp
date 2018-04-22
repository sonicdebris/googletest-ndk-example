#include <jni.h>
#include <string>
#include <sstream>
#include "Foo.h"

extern "C"
JNIEXPORT jstring

JNICALL
Java_sonicdebris_gtestexample_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    Foo foo;
    std::stringstream hello;
    hello << "Hello from C++" << foo.get();
    return env->NewStringUTF(hello.str().c_str());
}

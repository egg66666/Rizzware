#include "Minecraft.h"
#include <stdio.h>

Minecraft::Minecraft(JNIEnv* env) : env(env), classInstance(nullptr), classPtr(nullptr) {}

bool Minecraft::exceptionCheck(const char* funcName) {
    if (env->ExceptionCheck()) {
        env->ExceptionDescribe();
        env->ExceptionClear();
        printf("%s returned false\n", funcName);
        return true;
    }
    return false;
}

bool Minecraft::Init() {
    classPtr = env->FindClass("ave");
    jfieldID class_instance_field_id = env->GetStaticFieldID(classPtr, "S", "Lave;");
    classInstance = env->GetStaticObjectField(classPtr, class_instance_field_id);

    if (exceptionCheck(__func__) || !classPtr || !class_instance_field_id || !classInstance) {
        printf("Minecraft initialization failed\n");
        return false;
    }

    printf("Minecraft initialized\n");
    return true;
}

void Minecraft::setRightClickDelay(int delay) {
    jfieldID mouseDelayId = env->GetFieldID(classPtr, "ap", "I");
    env->SetIntField(classInstance, mouseDelayId, delay);

    if (exceptionCheck(__func__) || !mouseDelayId) {
        printf("Failed to set right click delay\n");
        return;
    }
}

#include "EntityPlayerSP.h"

EntityPlayerSP::EntityPlayerSP(JNIEnv* env) : env(env), classInstance(nullptr), classPtr(nullptr) {}

bool EntityPlayerSP::exceptionCheck(const char* funcName) {

    if (env->ExceptionCheck()) {
        env->ExceptionDescribe();
        env->ExceptionClear();
        printf("%s returned false\n", funcName);
        return true;
    }
    return false;
}

bool EntityPlayerSP::Init() {

    classPtr = env->FindClass("bew");
    jfieldID classInstanceFieldID = env->GetFieldID(minecraftClass, "h", "Lbew;");
    classInstance = env->GetObjectField(minecraftObject, classInstanceFieldID);

    if (exceptionCheck(__func__) || !classPtr || !classInstanceFieldID || !classInstance) {
        printf("EntityPlayerSP initialization failed\n");
        return false;
    }

    printf("EntityPlayerSP initialized\n");
    return true;
}

Vector3<jdouble> EntityPlayerSP::getMotionVector() {

    Vector3<jdouble> motionVector;

    jfieldID field_id_x = env->GetFieldID(classPtr, "v", "D");
    jfieldID field_id_y = env->GetFieldID(classPtr, "w", "D");
    jfieldID field_id_z = env->GetFieldID(classPtr, "x", "D");

    if (exceptionCheck(__func__) || !field_id_x || !field_id_y || !field_id_z) {
        printf("Error in getMotionVector\n");
        return motionVector;
    }

    motionVector.setX(env->GetDoubleField(classInstance, field_id_x));
    motionVector.setY(env->GetDoubleField(classInstance, field_id_y));
    motionVector.setZ(env->GetDoubleField(classInstance, field_id_z));

    exceptionCheck(__func__);

    return motionVector;
}

bool EntityPlayerSP::setVelocity(Vector3<jdouble> motion) {

    jfieldID field_id_x = env->GetFieldID(classPtr, "v", "D");
    jfieldID field_id_y = env->GetFieldID(classPtr, "w", "D");
    jfieldID field_id_z = env->GetFieldID(classPtr, "x", "D");

    if (exceptionCheck(__func__) || !field_id_x || !field_id_y || !field_id_z) return false;

    env->SetDoubleField(classInstance, field_id_x, motion.getX());
    env->SetDoubleField(classInstance, field_id_y, motion.getY());
    env->SetDoubleField(classInstance, field_id_z, motion.getZ());

    return !exceptionCheck(__func__);
}

bool EntityPlayerSP::setXZVelocity(Vector3<jdouble> motion) {

    jfieldID field_id_x = env->GetFieldID(classPtr, "v", "D");
    jfieldID field_id_z = env->GetFieldID(classPtr, "x", "D");

    if (exceptionCheck(__func__) || !field_id_x || !field_id_z) return false;

    env->SetDoubleField(classInstance, field_id_x, motion.getX());
    env->SetDoubleField(classInstance, field_id_z, motion.getZ());

    return !exceptionCheck(__func__);
}

jfloat EntityPlayerSP::getYaw() {

    jfieldID field_id = env->GetFieldID(classPtr, "y", "F");

    if (exceptionCheck(__func__) || !field_id) return 0.0f;

    jfloat yaw = env->GetFloatField(classInstance, field_id);

    if (yaw <= -180.0f) yaw += 360.0f;
    if (yaw > 180.0f) yaw -= 360.0f;

    return yaw;
}

void EntityPlayerSP::setSprinting(jboolean isSprinting) {

    jmethodID method_id = env->GetMethodID(classPtr, "d", "(Z)V");

    if (exceptionCheck(__func__) || !method_id) return;

    env->CallBooleanMethod(classInstance, method_id, (jvalue*)isSprinting);
}
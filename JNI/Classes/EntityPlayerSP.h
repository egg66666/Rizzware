#pragma once
#include <array>
#include <jni.h>
#include <iostream>
#include <math.h>
#include "../../math/vector.h"
#define minecraftClass env->FindClass("ave")
#define minecraftObject env->GetStaticObjectField(minecraftClass, env->GetStaticFieldID(minecraftClass, "S", "Lave;"))

class EntityPlayerSP final {
public:

    EntityPlayerSP(JNIEnv* env);
    
    Vector3<jdouble> getMotionVector();

    bool setVelocity(Vector3<jdouble> motion);

    bool setXZVelocity(Vector3<jdouble> motion);

    jfloat getYaw();

    void setSprinting(jboolean isSprinting);

    bool Init();

private:
    bool exceptionCheck(const char* funcName);
	jclass classPtr;
	JNIEnv* env;
	jobject classInstance;
    jdouble motionX{}, motionY{}, motionZ{};
	const char name[15] = "EntityPlayerSP";
};
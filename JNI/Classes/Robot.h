#pragma once
#include <jni.h>
class Robot final {
public:
	Robot(JNIEnv* env) : env(env) {
		Init();
	}
	bool Init() {
		classPtr = env->FindClass("java/awt/Robot");
		if (!classPtr) 
		{
			printf("Failed to get java/awt/Robot");
			return false;
		}
		jmethodID constructor = env->GetMethodID(classPtr, "<init>", "()V");
		classInstance = env->NewObject(classPtr, constructor);

		if (!classInstance) 
		{
			printf("Failed to get class instance");
			return false;
		}
return true;
	}
	void MousePress(jint button) 
	{
		jmethodID method = env->GetMethodID(classPtr, "mousePress", "(I)V");
		env->CallVoidMethodA(classInstance, method, (jvalue*)&button);
	}
	void MouseRelease(jint button) 
	{
		jmethodID method = env->GetMethodID(classPtr, "mouseRelease", "(I)V");
		env->CallVoidMethodA(classInstance, method, (jvalue*)&button);
	}
	void Delay(jint ms) 
	{
		jmethodID method = env->GetMethodID(classPtr, "delay", "(I)V");
		env->CallVoidMethodA(classInstance, method, (jvalue*)&ms);
	}
private:
	jclass classPtr;
	JNIEnv* env;
	jobject classInstance;
	const char name[6] = "Robot";
};
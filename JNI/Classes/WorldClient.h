#pragma once
#include <jni.h>
#define minecraftClass env->FindClass("ave")
#define minecraftObject env->GetStaticObjectField(minecraftClass, env->GetStaticFieldID(minecraftClass, "S", "Lave;"))

class WorldClient final {
public:
	WorldClient(JNIEnv* env) : env(env), classInstance(nullptr), classPtr(nullptr) {
		
	}
	bool Init() {
		classPtr = env->FindClass("bdb");
		if (!classPtr || env->ExceptionCheck()) {
			env->ExceptionDescribe();
			env->ExceptionClear();
			return false;
		}

		jfieldID classInstanceFieldID = env->GetFieldID(minecraftClass, "f", "Lbdb;");

		if (!classInstanceFieldID || env->ExceptionCheck()) {
			env->ExceptionDescribe();
			env->ExceptionClear();
			return false;
		}

		classInstance = env->GetObjectField(minecraftObject, classInstanceFieldID);

		if (!classInstance || env->ExceptionCheck()) {
			env->ExceptionDescribe();
			env->ExceptionClear();
			return false;
		}
		printf("WorldClient initialized\n");
		return true;
	}
	auto getEntityList() {
		jfieldID field_id = env->GetFieldID(classPtr, "c", "Ljava/util/List;"); //j = all players, h = all tile entities, f = all entities
	}
private:
	jclass classPtr;
	JNIEnv* env;
	jobject classInstance;
	
	const char name[12] = "WorldClient";
};

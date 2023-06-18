#include <jni.h>

class Minecraft final {
public:
	Minecraft(JNIEnv* env);
	bool Init();
	void setRightClickDelay(int delay);

private:
	bool exceptionCheck(const char* funcName);
	jclass classPtr;
	JNIEnv* env;
	jobject classInstance;
	const char name[10] = "Minecraft";
};
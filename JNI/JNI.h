#pragma once
#include <memory>
#include <Windows.h>
#include <jni.h>
#include "Classes/Robot.h"
#include "Classes/Minecraft.h"
#include "Classes/EntityPlayerSP.h"
#include "Classes/WorldClient.h"


class JNI final {
public:
    struct ClassPointers {
        std::unique_ptr<EntityPlayerSP> entityPlayerSP{};
        std::unique_ptr<WorldClient> worldClient{};
        std::unique_ptr<Robot> robot{};
        std::unique_ptr<Minecraft> minecraft{};
    } classPtrs;

    JNI()
        : env(nullptr), jvm(nullptr), isInit(false) // initialize member variables
    {
        jint res = JNI_GetCreatedJavaVMs(&jvm, 1, nullptr);
        if (res != JNI_OK) {
            printf("failed to get jvm");
            MessageBox(0, L"ERROR", L"Check console", MB_ICONASTERISK);
            return;
        }

        // Attach current thread to the JVM and get the JNIEnv pointer.
        if (jvm->AttachCurrentThread((void**)&env, nullptr) != 0) {
            printf("failed to attach current thread");
            MessageBox(0, L"ERROR", L"Check console", MB_ICONASTERISK);
            return;
        }

        // Initialize game classes
        classPtrs.robot = std::make_unique<Robot>(env);
        classPtrs.minecraft = std::make_unique<Minecraft>(env);
        classPtrs.entityPlayerSP = std::make_unique<EntityPlayerSP>(env);
        classPtrs.worldClient = std::make_unique<WorldClient>(env);
        isInit = true;
    }
    ~JNI() {
        if (jvm) {
            jint ret = jvm->DetachCurrentThread();
            if (ret == JNI_OK) {
                isInit = false;
            }
            else {
                // Handle error
                printf("Failed to detach thread from JVM, error: %d", ret);
            }
        }
    }
    bool GetInit() {
        return isInit;
    }

private:
    JNIEnv* env{};
    JavaVM* jvm{};
    bool isInit{};
};

inline std::unique_ptr<JNI> jni{};
#pragma once
// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>
#include <cstdio>
#include <thread>
#include <jni.h>
#include <iostream>
#include "JNI/JNI.h"
#include "Hooks/hooks.h"
class MainClass final {
	public:
		bool Init() {
			velocity = 1;
			toggleVelocity = false;
			toggleSprint = false;
			return true;

		}

	void Velocity() {
		jdouble forwardSpeed = 0.0;
		jdouble lateralSpeed = 0.0;

		if (hooks->KeyListener['W']) {
			forwardSpeed += velocity;
		}
		if (hooks->KeyListener['S']) {
			forwardSpeed -= velocity;
		}
		if (hooks->KeyListener['A']) {
			lateralSpeed -= velocity;
		}
		if (hooks->KeyListener['D']) {
			lateralSpeed += velocity;
		}

		jdouble resultantSpeed = sqrt(forwardSpeed * forwardSpeed + lateralSpeed * lateralSpeed);
		jdouble angle = atan2(lateralSpeed, forwardSpeed);

		jfloat yaw = jni->classPtrs.entityPlayerSP->getYaw() * M_PI / 180.0f;

		angle += yaw;

		jdouble newVelocityX = -resultantSpeed * sin(angle);
		jdouble newVelocityZ = resultantSpeed * cos(angle);

		Vector3<jdouble> newVelocity(newVelocityX, 0.0, newVelocityZ);

		jni->classPtrs.entityPlayerSP->setXZVelocity(newVelocity);
	}

	bool initClasses() {
		bool minecraftInit = false;
		bool entityPlayerSPInit = false;
		bool worldClientInit = false;

		while (true) {
			if (!minecraftInit) {
				minecraftInit = jni->classPtrs.minecraft->Init();
			}
			if (!entityPlayerSPInit) {
				entityPlayerSPInit = jni->classPtrs.entityPlayerSP->Init();
			}
			if (!worldClientInit) {
				worldClientInit = jni->classPtrs.worldClient->Init();
			}

			if (minecraftInit && entityPlayerSPInit && worldClientInit) {
				return true;
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}
	}
	bool toggleVelocity{};
	bool toggleSprint{};
private:
	int velocity{};
};		
inline std::unique_ptr<MainClass> mainClass {};
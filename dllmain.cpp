// dllmain.cpp : Defines the entry point for the DLL application.
#include "dllmain.h"
int velocityMultiplier = 2;



void MainThread(HMODULE instance) {

	jni = std::make_unique<JNI>();
	hooks = std::make_unique<Hooks>();
	mainClass = std::make_unique<MainClass>();
	mainClass->Init();
	mainClass->initClasses();
	

	while (!hooks->KeyListener[VK_END]) {

		if (hooks->KeyListener['O']) {
			mainClass->initClasses();
		}

		if (hooks->KeyListener['2']) {
			mainClass->toggleSprint = !mainClass->toggleSprint;
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		if (mainClass->toggleSprint) {
			jni->classPtrs.entityPlayerSP->setSprinting(true);
		}

		if (hooks->KeyListener['1']) {
			mainClass->toggleVelocity = !mainClass->toggleVelocity;
			printf("Toggle Velocity: %d\n", mainClass->toggleVelocity);
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		if (mainClass->toggleVelocity) {
			mainClass->Velocity();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		jni->classPtrs.minecraft->setRightClickDelay(0);
		if(GetAsyncKeyState(VK_XBUTTON1)) {
			jni->classPtrs.robot->MousePress(16);
			jni->classPtrs.robot->MouseRelease(16);
			jni->classPtrs.robot->Delay(100);
		}
		
	}

	FreeLibraryAndExitThread(instance, 0);
}

bool __stdcall DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved)
{
	static FILE* f{nullptr};
	static std::thread main_thread;

	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
	{
		AllocConsole() || AttachConsole(ATTACH_PARENT_PROCESS);
		if (freopen_s(&f, "CONOUT$", "w", stdout) != 0 ||
			freopen_s(&f, "CONOUT$", "w", stderr) != 0 ||
			freopen_s(&f, "CONIN$", "r", stdin) != 0) {
			// handle error
		}

		main_thread = std::thread([instance] { MainThread(instance); });
		if (main_thread.joinable())
			main_thread.detach();

		break;
	}
	case DLL_PROCESS_DETACH:
	{
		// Signal to the main thread that it should exit
		
		hooks->KeyListener[VK_END] = true;

		// Wait for the main thread to exit
		if (main_thread.joinable())
			main_thread.join();

		if (f) { fclose(f); }
		FreeConsole();

		break;
	}

	default:
		break;

	}
		return true;

}

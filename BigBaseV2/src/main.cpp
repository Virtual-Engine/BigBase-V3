#include "common.hpp"
#include "features.hpp"
#include "fiber_pool.hpp"
#include "gui.hpp"
#include "logger.hpp"
#include "hooking.hpp"
#include "pointers.hpp"
#include "renderer.hpp"
#include "script_mgr.hpp"
#include "UI/UIManager.hpp"
#include "gui/list/mainscript.hpp"
#include "UI/settings.hpp"
#include "Discord/handler.h"

BOOL APIENTRY DllMain(HMODULE hmod, DWORD reason, PVOID)
{
	using namespace big;
	if (reason == DLL_PROCESS_ATTACH)
	{

		DisableThreadLibraryCalls(hmod);

		g_hmodule = hmod;
		g_main_thread = CreateThread(nullptr, 0, [](PVOID) -> DWORD
		{
			while (!FindWindow(L"grcWindow", L"Grand Theft Auto V"))
				std::this_thread::sleep_for(20ms);

			auto logger_instance = std::make_unique<logger>();
			try
			{
				LOG(RAW) << u8R"kek(
 ______  _       ______                         ______  
(____  \(_)     (____  \                       (_____ \ 
 ____)  )_  ____ ____)  )_____  ___ _____ _   _ _____) )
|  __  (| |/ _  |  __  ((____ |/___) ___ | | | (_____ ( 
| |__)  ) ( (_| | |__)  ) ___ |___ | ____|\ V / _____) )
|______/|_|\___ |______/\_____(___/|_____) \_/ (______/ 
          (_____|                                       
					)kek";
				auto pointers_instance = std::make_unique<pointers>();
				auto renderer_instance = std::make_unique<renderer>();
				auto fiber_pool_instance = std::make_unique<fiber_pool>(10);
				auto hooking_instance = std::make_unique<hooking>();
				LOG(INFO) << "Components initialized.";

				g_script_mgr.add_script(std::make_unique<script>(&features::script_func));
				g_script_mgr.add_script(std::make_unique<script>(&gui::script_func));
				LOG(INFO) << "Scripts registered.";

				g_hooking->enable();
				LOG(INFO) << "Hooking enabled.";

				if (*g_pointers->m_loading_screen_state != eLoadingScreenState::Finished)
				{
					LOG(INFO) << "Waiting Loading Screen";
					while (*g_pointers->m_loading_screen_state != eLoadingScreenState::Finished)
					{
						std::this_thread::sleep_for(1000ms);
					}
				}
				g_Settings.Initialize();
				LOG(INFO) << "Settings Loaded.";
				LOG(INFO) << "UI Manager Loading...";
				g_UiManager = std::make_unique<UserInterface::UIManager>();
				g_MainScript = std::make_shared<MainScript>();
				g_script_mgr.add_script(std::make_unique<script>(&MainScript::Tick));
				LOG(INFO) << "UI Manager Loaded";

				g_Discord->Init();

				while (g_running)
				{
				     if (GetAsyncKeyState(VK_END)) g_running = false;
				     std::this_thread::sleep_for(200ms);
				}

				g_hooking->disable();
				LOG(INFO) << "Hooking disabled.";

				std::this_thread::sleep_for(200ms);

				g_script_mgr.remove_all_scripts();
				LOG(INFO) << "Scripts unregistered.";

				hooking_instance.reset();
				fiber_pool_instance.reset();
				renderer_instance.reset();
				pointers_instance.reset();
				g_MainScript.reset();
				g_UiManager.reset();
				g_Discord->Shutdown();
				LOG(INFO) << "Components uninitialized.";
			}
			catch (std::exception const &ex)
			{
				LOG(FATAL) << ex.what();
				MessageBoxA(nullptr, ex.what(), nullptr, MB_OK | MB_ICONEXCLAMATION);
			}

			LOG(INFO) << "Farewell!";
			logger_instance.reset();

			CloseHandle(g_main_thread);
			FreeLibraryAndExitThread(g_hmodule, 0);
		}, nullptr, 0, &g_main_thread_id);
	}

	return true;
}

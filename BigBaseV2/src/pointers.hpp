#pragma once
#include "common.hpp"
#include "gta/fwddec.hpp"
#include "gta/enums.hpp"
#include "function_types.hpp"

namespace big
{
	enum class eLoadingScreenState : int32_t
	{
		Invalid = -1,
		Finished,
		PreLegal,
		Unknown_2,
		Legals,
		Unknown_4,
		LandingPage,
		Transition,
		Unknown_7,
		Unknown_8,
		Unknown_9,
		SessionStartLeave
	};

	class pointers
	{
	public:
		explicit pointers();
		~pointers();
	public:
		HWND m_hwnd{};

		eLoadingScreenState* m_loading_screen_state{};

		bool *m_is_session_started{};

		CPedFactory **m_ped_factory{};
		CNetworkPlayerMgr **m_network_player_mgr{};

		PVOID m_init_native_tables;
		rage::scrNativeRegistrationTable *m_native_registration_table{};
		functions::get_native_handler_t m_get_native_handler{};
		functions::fix_vectors_t m_fix_vectors{};

		rage::atArray<GtaThread*> *m_script_threads{};
		rage::scrProgramTable *m_script_program_table{};
		functions::run_script_threads_t m_run_script_threads{};
		std::int64_t **m_script_globals{};

		CGameScriptHandlerMgr **m_script_handler_mgr{};

		IDXGISwapChain **m_swapchain{};

		PVOID m_model_spawn_bypass;
	};

	inline pointers *g_pointers{};
}

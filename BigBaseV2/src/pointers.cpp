#include "common.hpp"
#include "logger.hpp"
#include "pointers.hpp"
#include "memory/all.hpp"

namespace big
{
	pointers::pointers()
	{
		memory::pattern_batch main_batch;

		main_batch.add("LSS", "83 3D ? ? ? ? ? 75 17 8B 43 20 25", [this](memory::handle ptr)
			{
				m_loading_screen_state = ptr.add(2).rip().add(1).as<eLoadingScreenState*>();
			});

		main_batch.add("ISS", "40 38 35 ? ? ? ? 75 0E 4C 8B C3 49 8B D7 49 8B CE", [this](memory::handle ptr)
			{
				m_is_session_started = ptr.add(3).rip().as<bool*>();
			});

		main_batch.add("PF", "48 8B 05 ? ? ? ? 48 8B 48 08 48 85 C9 74 52 8B 81", [this](memory::handle ptr)
			{
				m_ped_factory = ptr.add(3).rip().as<CPedFactory**>();
			});

		main_batch.add("NPM", "48 8B 0D ? ? ? ? 8A D3 48 8B 01 FF 50 ? 4C 8B 07 48 8B CF", [this](memory::handle ptr)
			{
				m_network_player_mgr = ptr.add(3).rip().as<CNetworkPlayerMgr**>();
			});

		main_batch.add("NH", "48 8D 0D ? ? ? ? 48 8B 14 FA E8 ? ? ? ? 48 85 C0 75 0A", [this](memory::handle ptr)
			{
				m_init_native_tables = ptr.sub(37).as<PVOID>();
				m_native_registration_table = ptr.add(3).rip().as<rage::scrNativeRegistrationTable*>();
				m_get_native_handler = ptr.add(12).rip().as<functions::get_native_handler_t>();
			});

		main_batch.add("FV", "83 79 18 00 48 8B D1 74 4A FF 4A 18 48 63 4A 18 48 8D 41 04 48 8B 4C CA", [this](memory::handle ptr)
			{
				m_fix_vectors = ptr.as<functions::fix_vectors_t>();
			});

		main_batch.add("ST", "45 33 F6 8B E9 85 C9 B8", [this](memory::handle ptr)
			{
				m_script_threads = ptr.sub(4).rip().sub(8).as<decltype(m_script_threads)>();
				m_run_script_threads = ptr.sub(0x1F).as<functions::run_script_threads_t>();
			});

		main_batch.add("SP", "48 8B 1D ? ? ? ? 41 83 F8 FF", [this](memory::handle ptr)
			{
				m_script_program_table = ptr.add(3).rip().as<decltype(m_script_program_table)>();
			});

		main_batch.add("SG", "48 8D 15 ? ? ? ? 4C 8B C0 E8 ? ? ? ? 48 85 FF 48 89 1D", [this](memory::handle ptr)
			{
				m_script_globals = ptr.add(3).rip().as<std::int64_t**>();
			});

		main_batch.add("S", "48 8B 0D ? ? ? ? 48 8B 01 44 8D 43 01 33 D2 FF 50 40 8B C8", [this](memory::handle ptr)
			{
				m_swapchain = ptr.add(3).rip().as<IDXGISwapChain**>();
			});

		main_batch.add("MSB", "48 8B C8 FF 52 30 84 C0 74 05 48", [this](memory::handle ptr)
		{
			m_model_spawn_bypass = ptr.add(8).as<PVOID>();
		});

		main_batch.run(memory::module(nullptr));

		m_hwnd = FindWindowW(L"grcWindow", nullptr);
		if (!m_hwnd)
			throw std::runtime_error("Failed to find the game's window.");

		g_pointers = this;
	}

	pointers::~pointers()
	{
		g_pointers = nullptr;
	}
}

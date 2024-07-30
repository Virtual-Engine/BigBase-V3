#pragma once
#include "Script.hpp"

namespace big
{
	inline bool ipstuff{ false };
	inline bool scidstuff{ false };
	inline bool discordRpc{ true };
	inline bool alpha = false;
	inline int alpha_level = 0;
	inline std::size_t iterator = 0;
	inline const char* name[3] = {
		"BigBase",
		"XIFI",
		"Poseidon"
	};
	class MainScript
	{
	public:
		explicit MainScript() = default;
		~MainScript() noexcept = default;

		void Initialize();
		void Destroy();
		static void Tick();
		bool m_Initialized{};
	};

	inline std::shared_ptr<MainScript> g_MainScript;
}

#pragma once
#include "common.hpp"
#include "natives.hpp"

namespace big {
	void TeleportToPlayer();
	void loop();


	inline void SetWantedLevel(int level)
	{
		PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), level, 0);
		PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), 0);
	}
	inline void doAnimation(const char* anim, const char* animid)
	{
		int pPlayer = PLAYER::PLAYER_PED_ID();
		STREAMING::REQUEST_ANIM_DICT(anim);
		if (STREAMING::HAS_ANIM_DICT_LOADED((anim)))
		{
			TASK::TASK_PLAY_ANIM(pPlayer, anim, animid, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);
		}
	}

	inline bool g_Invincible{ true };
	inline bool g_NeverWanted{ true };
	inline bool g_NoRagdoll{ true };
	inline bool g_AlwaysRagdoll{ false };
	inline bool g_DieOnRagdoll{ false };
	inline bool g_Invisible{ false };
	inline int g_WantedLevel{ 0 };
	inline bool g_Fakewanted{ false };
	inline bool g_SpinBot{ false };
	void PTFXCALLBoneless(const char* call1, const char* call2, const char* name, int bone);
	void GlowManager(bool toggle);
	inline bool m_Head{ false };
	inline bool m_RightHand{ false };
	inline bool m_LeftHand{ false };
	inline bool m_RightFood{ false };
	inline bool m_LeftFood{ false };
	inline bool m_EnableGlow{ false };
	inline float m_GlowScale{ 0.1f };
	inline std::array<const char*, 6> m_Particle = { "Alien", "Glow", "Clown", "Lightning", "Ghost", "Electric" };
	inline std::array<const char*, 6> m_ParticleCalls0 = { "scr_rcbarry1", "scr_rcbarry1", "scr_rcbarry2", "scr_rcbarry2", "scr_agencyheist", "scr_agencyheistb" };
	inline std::array<const char*, 6> m_ParticleCalls1 = { "scr_alien_disintegrate", "scr_alien_teleport", "scr_clown_appears", "scr_clown_death", "scr_fbi_dd_breach_smoke", "scr_agency3b_elec_box" };
	inline std::size_t m_ParticleIterator{ 0 };

}
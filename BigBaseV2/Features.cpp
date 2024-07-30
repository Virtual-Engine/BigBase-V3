#include "common.hpp"
#include "Features.hpp"
#include "natives.hpp"
#include "gta_util.hpp"

namespace big {
	void TeleportToPlayer()
	{
		
	}
	void Invincible(bool toggle)
	{
		ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), toggle);
	}

	void NeverWanted(bool toggle)
	{
		if (toggle)
		{
			PLAYER::SET_MAX_WANTED_LEVEL(6);
			PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), 0, 0);
			PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), 0);
			g_WantedLevel = 0;
		}
	}
	void NoRagodoll(bool toggle)
	{
		if (toggle)
		{
			PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(PLAYER::PLAYER_PED_ID(), false);
			PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), false);
		}
		else
		{
			PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(PLAYER::PLAYER_PED_ID(), true);
			PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), true);
		}
	}
	void AlwaysRagdoll(bool toggle)
	{
		if (toggle)
		{
			PED::SET_PED_RAGDOLL_ON_COLLISION(PLAYER::PLAYER_PED_ID(), true);
		}
		else
		{
			PED::SET_PED_RAGDOLL_ON_COLLISION(PLAYER::PLAYER_PED_ID(), false);
		}
	}

	void DieOnRagdoll(bool toggle)
	{
		if (toggle)
		{
			PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 33, true);
		}
		else
		{
			PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 33, false);
		}
	}

	void Invisible(bool toggle)
	{
		if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
		{
			if (toggle)
			{
				ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), false, 0);
			}
			else ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), true, 0);
		}

	}
	void fakewanted(bool toggle)
	{
		if (toggle)
		{

			MISC::SET_FAKE_WANTED_LEVEL(6);

		}
		else
		{

			MISC::SET_FAKE_WANTED_LEVEL(0);
		}
	}
	void SpinBot(bool toggle)
	{
		if (toggle)
		{
			static int Heading;
			Heading++;
			Heading++;
			Heading++;
			Heading++;
			Heading++;
			Heading++;
			Heading++;
			Heading++;
			Heading++;
			Heading++;
			Heading++;
			Heading++;
			ENTITY::SET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID(), Heading);
		}
		else
		{
			!NULL;
		}
	}
	void PTFXCALLBoneless(const char* call1, const char* call2, const char* name, int bone)
	{
		STREAMING::REQUEST_NAMED_PTFX_ASSET(call1);
		GRAPHICS::USE_PARTICLE_FX_ASSET(call2);
		int ptfx = GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(name, PLAYER::PLAYER_PED_ID(), 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.0f, bone, m_GlowScale, 1, 1, 1);
		STREAMING::REMOVE_PTFX_ASSET();
	}
	void GlowManager(bool toggle)
	{
		if (toggle)
		{
			if (m_Head) { PTFXCALLBoneless(m_ParticleCalls0[m_ParticleIterator], m_ParticleCalls0[m_ParticleIterator], m_ParticleCalls1[m_ParticleIterator], 0x796e); }
			if (m_RightHand) { PTFXCALLBoneless(m_ParticleCalls0[m_ParticleIterator], m_ParticleCalls0[m_ParticleIterator], m_ParticleCalls1[m_ParticleIterator], 0xdead); }
			if (m_LeftHand) { PTFXCALLBoneless(m_ParticleCalls0[m_ParticleIterator], m_ParticleCalls0[m_ParticleIterator], m_ParticleCalls1[m_ParticleIterator], 0x8cbd); }
			if (m_RightFood) { PTFXCALLBoneless(m_ParticleCalls0[m_ParticleIterator], m_ParticleCalls0[m_ParticleIterator], m_ParticleCalls1[m_ParticleIterator], 0xcc4d); }
			if (m_LeftFood) { PTFXCALLBoneless(m_ParticleCalls0[m_ParticleIterator], m_ParticleCalls0[m_ParticleIterator], m_ParticleCalls1[m_ParticleIterator], 0x3779); }
		}
	}
	void loop()
	{
		Invincible(g_Invincible);
		NeverWanted(g_NeverWanted);
		NoRagodoll(g_NoRagdoll);
		AlwaysRagdoll(g_AlwaysRagdoll);
		DieOnRagdoll(g_DieOnRagdoll);
		Invisible(g_Invisible);
		fakewanted(g_Fakewanted);
		SpinBot(g_SpinBot);
		SetWantedLevel(g_WantedLevel);
		GlowManager(m_EnableGlow);
	}
}
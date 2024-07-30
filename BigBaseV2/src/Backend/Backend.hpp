#pragma once
#include "common.hpp"
#include "natives.hpp"

namespace big {
	inline bool bReset = true;
	inline bool spectating = false;
	inline static bool override_cam_distance = false;
	inline int cam_distance = 10;

	class Backend
	{
	public:
		static void specate()
		{
			const auto vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
			const auto ped = PLAYER::PLAYER_PED_ID();

			if (!g_SelectedPlayer || !spectating) {
				if (spectating)
					spectating = false;

				if (!bReset) {
					bReset = true;

					NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(false, -1);
					NETWORK::NETWORK_OVERRIDE_RECEIVE_RESTRICTIONS_ALL(false);
					HUD::SET_MINIMAP_IN_SPECTATOR_MODE(false, -1);
					HUD::SET_BLIP_ALPHA(HUD::GET_MAIN_PLAYER_BLIP_ID(), 255);

					STREAMING::SET_FOCUS_ENTITY(ped);
				}

				return;
			}

			const auto target =
				PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);

			NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(true, target);
			NETWORK::NETWORK_OVERRIDE_RECEIVE_RESTRICTIONS_ALL(false);
			HUD::SET_MINIMAP_IN_SPECTATOR_MODE(true, target);
			HUD::SET_BLIP_ALPHA(HUD::GET_MAIN_PLAYER_BLIP_ID(), 255);

			STREAMING::SET_FOCUS_ENTITY(target);

			if (override_cam_distance)
				CAM::SET_THIRD_PERSON_CAM_ORBIT_DISTANCE_LIMITS_THIS_UPDATE(
					1.f,
					(float)cam_distance);

			bReset = false;
		}
		static void globals()
		{

			while (true)
			{
				specate();
				script::get_current()->yield();
			}
		}
	};
	inline Backend g_backend;
}
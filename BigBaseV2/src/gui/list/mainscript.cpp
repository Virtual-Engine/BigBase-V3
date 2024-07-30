#include "MainScript.hpp"
#include "Natives.hpp"
#include "UI/Timer.hpp"
#include "UI/UIManager.hpp"
#include "UI/option/BoolOption.hpp"
#include "UI/option/ChooseOption.hpp"
#include "UI/option/NumberOption.hpp"
#include "UI/option/RegularOption.hpp"
#include "UI/option/SubOption.hpp"
#include "UI/submenu/RegularSubmenu.hpp"
#include "UI/submenu/PlayerSubmenu.hpp"
#include "UI/option/BreakOption.hpp"
#include "submenu.hpp"
#include "Discord/handler.h"
#include "../Features.hpp"
#include "Backend/Backend.hpp"

void ScriptEventLog()
{
	HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
	HUD::BEGIN_TEXT_COMMAND_THEFEED_POST((char*)"STRING");
	HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Open Key ~g~[F5] ~w~BigBase Loaded");
	HUD::END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT_WITH_CREW_TAG_AND_ADDITIONAL_ICON("Virtual_X_T", (char*)"notify", true, 5, (char*)"~g~BigBase V3", (char*)"", 1.f, (char*)"", 5, 0);
	HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(false, false);
}
using namespace big::UserInterface;
namespace big
{

	void MainScript::Initialize()
	{
		//Auth(); 

		if (true)
		{
			ScriptEventLog();
			m_Initialized = true;

			g_UiManager->AddSubmenu<RegularSubmenu>("Home", Submenu::SubmenuHome, [](RegularSubmenu* sub)
				{
					sub->AddOption<SubOption>("Self", "Personal option", Submenu::SubmenuSelf);
					sub->AddOption<SubOption>("Players", "Player in your session", Submenu::SubmenuPlayers);
					sub->AddOption<SubOption>("Network", "Network functionality", Submenu::SubmenuNetwork);
					sub->AddOption<SubOption>("Vehicle", "Setting up your vehicles", Submenu::SubmenuVehicle);
					sub->AddOption<SubOption>("Weapon", "Modify or donate weapons", Submenu::SubmenuWeapon);
					sub->AddOption<SubOption>("Recovery", "Money, rp and casino ...", Submenu::SubmenuRecovery);
					sub->AddOption<SubOption>("Teleports", "Teleport where you want", Submenu::SubmenuTeleports);
					sub->AddOption<SubOption>("Protection", "Protect yourself against modders ", Submenu::SubmenuProtection);
					sub->AddOption<SubOption>("World", "Changing the world of GTA V", Submenu::SubmenuWorld);
					sub->AddOption<SubOption>("Settings", "Edit and customize your menu", Submenu::SubmenuSettings);
				});

			g_UiManager->AddSubmenu<RegularSubmenu>("Self", Submenu::SubmenuSelf, [](RegularSubmenu* sub)
				{
					static int nignog{ 0 };
					sub->AddOption<SubOption>("Animation", nullptr, Submenu::SubmenuSelfAnimation);
					sub->AddOption<SubOption>(("Particles"), nullptr, Submenu::SubmenuSelfGlow);
					sub->AddOption<BoolOption<bool>>(("Invincible"), nullptr, &g_Invincible, BoolDisplay::OnOff);
					sub->AddOption<NumberOption<int>>(("Wanted Level"), nullptr, &g_WantedLevel, 0, 5, 1, 3);
					sub->AddOption<BoolOption<bool>>(("Never Wanted"), nullptr, &g_NeverWanted, BoolDisplay::OnOff);
					sub->AddOption<BoolOption<bool>>(("Fake Wanted"), nullptr, &g_Fakewanted, BoolDisplay::OnOff);
					sub->AddOption<BoolOption<bool>>(("Spin"), nullptr, &g_SpinBot, BoolDisplay::OnOff);
					sub->AddOption<BoolOption<bool>>(("No Ragdoll"), nullptr, &g_NoRagdoll, BoolDisplay::OnOff);
					sub->AddOption<BoolOption<bool>>(("Always Ragdoll"), nullptr, &g_AlwaysRagdoll, BoolDisplay::OnOff);
					sub->AddOption<BoolOption<bool>>(("Die On Ragdoll"), nullptr, &g_DieOnRagdoll, BoolDisplay::OnOff);
					sub->AddOption<BoolOption<bool>>(("Invisible"), nullptr, &g_Invisible, BoolDisplay::OnOff);

				});

			g_UiManager->AddSubmenu<RegularSubmenu>("Particles", Submenu::SubmenuSelfGlow, [](RegularSubmenu* sub)
				{
					sub->AddOption<BoolOption<bool>>(("Enable"), nullptr, &m_EnableGlow, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<NumberOption<float>>(("Scale"), nullptr, &m_GlowScale, 0, 2, 0.1f, 1, true, "", "", [] {});
					sub->AddOption<ChooseOption<const char*, std::size_t>>(("Particle"), nullptr, &m_Particle, &m_ParticleIterator);
					sub->AddOption<BoolOption<bool>>(("Head"), nullptr, &m_Head, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(("Right Hand"), nullptr, &m_RightHand, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(("Left Hand"), nullptr, &m_LeftHand, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(("Right Foot"), nullptr, &m_RightFood, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(("Left Foot"), nullptr, &m_LeftFood, BoolDisplay::OnOff, false, [] {});
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(("Animations"), Submenu::SubmenuSelfAnimation, [](RegularSubmenu* sub)
				{
					sub->AddOption<RegularOption>(("Stop All Animations"), nullptr, [] { TASK::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID()); TASK::CLEAR_PED_SECONDARY_TASK(PLAYER::PLAYER_PED_ID()); });
					sub->AddOption<RegularOption>(("SexReceiver"), nullptr, [] { doAnimation("rcmpaparazzo_2", "shag_loop_poppy"); });
					sub->AddOption<RegularOption>(("SexGiver"), nullptr, [] { doAnimation("rcmpaparazzo_2", "shag_loop_a"); });
					sub->AddOption<RegularOption>(("StripperDance"), nullptr, [] { doAnimation("mini@strip_club@private_dance@part1", "priv_dance_p1"); });
					sub->AddOption<RegularOption>(("PoleDance"), nullptr, [] { doAnimation("mini@strip_club@pole_dance@pole_dance1", "pd_dance_01"); });
					sub->AddOption<RegularOption>(("PushUps"), nullptr, [] { doAnimation("amb@world_human_push_ups@male@base", "base"); });
					sub->AddOption<RegularOption>(("SitUps"), nullptr, [] { doAnimation("amb@world_human_sit_ups@male@base", "base"); });
					sub->AddOption<RegularOption>(("Celebrate"), nullptr, [] { doAnimation("rcmfanatic1celebrate", "celebrate"); });
					sub->AddOption<RegularOption>(("Electrocution"), nullptr, [] { doAnimation("ragdoll@human", "electrocute"); });
					sub->AddOption<RegularOption>(("Suicide"), nullptr, [] { doAnimation("mp_suicide", "pistol"); });
					sub->AddOption<RegularOption>(("Showering"), nullptr, [] { doAnimation("mp_safehouseshower@male@", "male_shower_idle_b"); });
				});

			g_UiManager->AddSubmenu<RegularSubmenu>("Players", Submenu::SubmenuPlayers, [](RegularSubmenu* sub)
				{
					for (std::uint32_t i = 0; i < 32; ++i)
					{
						if (auto ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i))
						{
							std::string name = PLAYER::GET_PLAYER_NAME(i);

							sub->AddOption<SubOption>(name.c_str(), nullptr, SubmenuSelectedPlayer, [=]
								{
									g_SelectedPlayer = i;
								});
						}
					}

				});
			g_UiManager->AddSubmenu<PlayerSubmenu>(&g_SelectedPlayer, Submenu::SubmenuSelectedPlayer, [](PlayerSubmenu* sub)
				{
					sub->AddOption<BoolOption<bool>>("Spectate Player", nullptr, &spectating, BoolDisplay::OnOff);
					sub->AddOption<RegularOption>("Teleport To Player", nullptr, [] { TeleportToPlayer(); });
					sub->AddOption<SubOption>("Friendly", nullptr, Submenu::SubmenuPlayerFriendly);
					sub->AddOption<SubOption>("Griefing", nullptr, Submenu::SubmenuPlayerEvil);
					sub->AddOption<SubOption>("Vehicle Options", nullptr, Submenu::SubmenuPlayerVehicle);
				});

			g_UiManager->AddSubmenu<RegularSubmenu>("Settings", Submenu::SubmenuSettings, [](RegularSubmenu* sub)
				{
					bool alpha = false;
					sub->AddOption<ChooseOption<const char*, std::size_t>>("Indicator", nullptr, &g_UiManager->IndicatorList, &g_UiManager->IndicatorIterator);
					sub->AddOption<SubOption>("Exemple", "Exemple Of Indicators Textures", Submenu::SubmenuVehicle);
					sub->AddOption<BreakOption>("Option");
					sub->AddOption<ChooseOption<const char*, std::size_t>>("Textures Toggle", nullptr, &g_UiManager->ToggleList, &g_UiManager->ToggleIterator);
					sub->AddOption<BoolOption<bool>>("Exemple", "Exemple Of Toggle Tetxures", &alpha, BoolDisplay::OnOff);

				});
		}
	}


	void MainScript::Tick()
	{
		g_MainScript->Initialize();
		while (true)
		{
			g_UiManager->OnTick();
			g_Discord->Tick();
			loop();
			script::get_current()->yield();
		}
	}
}
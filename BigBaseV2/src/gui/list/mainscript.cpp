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

void ScriptEventLog()
{
	HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
	HUD::BEGIN_TEXT_COMMAND_THEFEED_POST((char*)"STRING");
	HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Open Key ~g~[F5] ~w~BigBase Loaded");
	HUD::END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT_WITH_CREW_TAG_AND_ADDITIONAL_ICON("Virtual_X_T", (char*)"notify", true, 5, (char*)"~p~Virtual X", (char*)"", 1.f, (char*)"", 5, 0);
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
					sub->AddOption<SubOption>("Option", "Option Of The Menu", Submenu::SubmenuOptions);
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
			
			g_UiManager->AddSubmenu<RegularSubmenu>("Option", Submenu::SubmenuOptions, [](RegularSubmenu* sub)
				{
					sub->AddOption<BoolOption<bool>>("Bool Option", "This Bool Option", &alpha, BoolDisplay::OnOff);
					sub->AddOption<NumberOption<int>>("Number Option [Int]", "This Number Option", &alpha_level, 0, 255, 1); // 0 = MIN; 255 = MAX; 1 = STEPS;
					sub->AddOption<ChooseOption<const char*, std::size_t>>("Choose Option", "This Choose Option", &name, &iterator, false, [] {
						switch (iterator)
						{
						case 0:
							g_UiManager->textkek = "BigBase";
							break;
						case 1:
							g_UiManager->textkek = "XIFI";
							break;
						case 2:
							g_UiManager->textkek = "Poseidon";
							break;
						}
						});
					sub->AddOption<BreakOption>("Break Option");
					sub->AddOption<RegularOption>("Button Option", "This Button Option", [] {
						PED::CLONE_PED(PLAYER::PLAYER_PED_ID(), true, false, true);
						});

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
			script::get_current()->yield();
		}
	}
}
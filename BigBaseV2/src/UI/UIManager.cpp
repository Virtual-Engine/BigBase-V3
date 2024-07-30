#include "UIManager.hpp"
#include "Timer.hpp"
#include "../Natives.hpp"
#include "../gta_util.hpp"
std::string properRightText;

float selectedTarget = 0;
double current = 0;
int currentOpacity;
int targetOpacity = 1000;
float scrollCurrent = 0;
float scrollTarget = 0;
int currentSelected, fullAmount;

float X_Info{};
float Y_Info{};
float X_GameInfo{ 0.96f };
float Y_GameInfo{};

float X_Notify{};
float Y_Notify{};

bool first = true;
bool cooldown = false;
bool negative = false;
bool editing = false;

float X_InfoFloat{};
float Y_InfoFloat{};

float X_HostMigration{};
float Y_HostMigration{};

double lerp(double start, double end, double amount) {
	return start * (1 - amount) + end * amount;
}

double opt_start = 0;
double opt_end = 0;


namespace big::UserInterface
{

	void UIManager::OnTick()
	{
		minusOpacity = 255;
		{
			if (minusOpacity != 0 && GetTickCount() % 12 == 0)
			{
				minusOpacity--;
			}
		}
		{
			if (currentOpacity != targetOpacity) currentOpacity = lerp(currentOpacity, targetOpacity, m_ScrollSpeed * 2);
			if ((currentOpacity > targetOpacity - 0.0005) && (currentOpacity < targetOpacity + 0.0005))
			{
				currentOpacity = targetOpacity;
			}
			minusOpacity = currentOpacity;
		}
		{
			if (scrollCurrent != scrollTarget) scrollCurrent = lerp(scrollCurrent, scrollTarget, m_ScrollSpeed);
			if ((scrollCurrent > scrollTarget - 0.0005) && (scrollCurrent < scrollTarget + 0.0005))
			{
				scrollCurrent = scrollTarget;
			}
		}
		{
			if (current != selectedTarget) current = lerp(current, selectedTarget, m_ScrollSpeed);
			if ((current > selectedTarget - 0.0005) && (current < selectedTarget + 0.0005))
			{
				current = selectedTarget;
			}
		}
		{
			if (minusOpacity != targetOpacity) minusOpacity = lerp(minusOpacity, targetOpacity, 0.0025f);
			if ((minusOpacity > targetOpacity - 2) && (minusOpacity < targetOpacity + 2))
			{
				minusOpacity = targetOpacity;
			}
			minusOpacity = currentOpacity;
		}

		std::lock_guard lock(m_Mutex);

		if (IsMouseLocked())
		{
			PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
			ShowCursor(true);
			//SetCursor(LoadCursorA(NULL, IDC_ARROW));

			if (GetMenuRect().IsInBounds(GetMousePos()))
			{
				LOG(INFO) << "Log";
			}
		}

		if (g_UiManager->m_Opened && g_Settings.m_LockMouse)
		{
			PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
		}

		CheckForInput();
		HandleInput();

		if (m_Opened)
		{
			PAD::DISABLE_CONTROL_ACTION(0, 27, true);
			m_DrawBaseY = m_PosY;
			if (!m_SubmenuStack.empty())
			{
				auto sub = m_SubmenuStack.top();
				sub->Reset();
				sub->Execute();
				DrawHeader(sub);
				if (m_ShowSubmenubar)
				{
					DrawSubmenuBar(sub);
				}
				if (sub->GetNumOptions() != 0)
				{
					std::size_t startPoint = 0;
					std::size_t endPoint = sub->GetNumOptions() > m_OptionsPerPage ? m_OptionsPerPage : sub->GetNumOptions();
					if (sub->GetNumOptions() > m_OptionsPerPage && sub->GetSelectedOption() >= m_OptionsPerPage - 6)
					{
						for (int i = 0; i < 6; i++)
						{
							if (sub->GetSelectedOption() < sub->GetNumOptions() - i)
							{
								startPoint = sub->GetSelectedOption() - g_UiManager->m_OptionsPerPage + i + 1;
								endPoint = sub->GetSelectedOption() + i + 1;
							}
						}
					}
					float tmp_base = m_DrawBaseY;

					for (std::size_t i = startPoint, j = 0; i < endPoint; ++i, ++j)
					{
						float tmp_point = tmp_base + ((m_OptionHeight) / 2.f);
						if (i == startPoint) opt_start = tmp_point;
						if (i == endPoint - 1) opt_end = tmp_point;

						if (loadscroller)
						{

							DrawSprite(
								FullHeaderName.c_str(),
								"scroller",
								m_PosX,
								tmp_point,
								m_Width,
								m_OptionHeight,
								{ 0,255,255,255 },
								0);
							if (m_Smoothscroll)
							{
								DrawSprite(
									FullHeaderName.c_str(),
									"scroller",
									m_PosX,
									tmp_point,
									m_Width,
									m_OptionHeight,
									{ 0,0,0,255 },
									0);
							}
						}
						else
						{
							DrawRect(
								m_PosX,
								tmp_point,
								m_Width,
								m_OptionHeight,
								m_OptionUnselectedBackgroundColor);


							if (m_Smoothscroll)
							{
								DrawRect(
									m_PosX,
									scrollCurrent,
									m_Width,
									m_OptionHeight,
									m_OptionSelectedBackgroundColor);

							}
						}
						fullAmount = endPoint;
						tmp_base += m_OptionHeight;
					}
					for (std::size_t i = startPoint, j = 0; i < endPoint; ++i, ++j)
					{
						currentSelected = sub->GetSelectedOption();

						DrawOption(sub->GetOption(i), sub, (i == sub->GetSelectedOption()));

					}
				}
			}

			DrawFooter();
			DrawDescription();
		}
	}

	void UIManager::CheckForInput()
	{
		ResetInput();
		
		m_OpenKeyPressed = gta_util::IsKeyPressed(VK_F5);
		m_BackKeyPressed = gta_util::IsKeyPressed(VK_BACK);
		m_EnterKeyPressed = gta_util::IsKeyPressed(VK_RETURN);
		m_UpKeyPressed = gta_util::IsKeyPressed(VK_UP);
		m_DownKeyPressed = gta_util::IsKeyPressed(VK_DOWN);
		m_LeftKeyPressed = gta_util::IsKeyPressed(VK_LEFT);
		m_RightKeyPressed = gta_util::IsKeyPressed(VK_RIGHT);
	}

	void UIManager::HandleInput()
	{
		if (m_Opened && m_Controllerinput)
		{
			// Disable Controls
			PAD::DISABLE_CONTROL_ACTION(2, INPUT_NEXT_CAMERA, true);
			PAD::DISABLE_CONTROL_ACTION(2, INPUT_CHARACTER_WHEEL, true);
			PAD::DISABLE_CONTROL_ACTION(2, INPUT_MELEE_ATTACK_LIGHT, true);
			//CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_MELEE_ATTACK_HEAVY, true);
			PAD::DISABLE_CONTROL_ACTION(2, INPUT_MULTIPLAYER_INFO, true);
			PAD::DISABLE_CONTROL_ACTION(2, INPUT_PHONE, true);
			//CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_MELEE_ATTACK_ALTERNATE, true);
			PAD::DISABLE_CONTROL_ACTION(2, INPUT_VEH_CIN_CAM, true);
			PAD::DISABLE_CONTROL_ACTION(2, INPUT_MAP_POI, true);
			PAD::DISABLE_CONTROL_ACTION(2, INPUT_PHONE, true);
			PAD::DISABLE_CONTROL_ACTION(2, INPUT_VEH_RADIO_WHEEL, true);
			PAD::DISABLE_CONTROL_ACTION(2, INPUT_VEH_HEADLIGHT, true);
		}
		static auto openTicker = GetTickCount();
		if (m_OpenKeyPressed && GetTickCount() - openTicker >= static_cast<std::uint32_t>(m_OpenDelay) || PAD::IS_DISABLED_CONTROL_PRESSED(0, ControlScriptRB) && PAD::IS_DISABLED_CONTROL_PRESSED(0, ControlPhoneRight) && m_Controllerinput && GetTickCount() - openTicker >= static_cast<std::uint32_t>(m_OpenDelay))
		{
			openTicker = GetTickCount();
			m_Opened ^= true;

			if (m_Sounds)
				AUDIO::PLAY_SOUND_FRONTEND(-1, m_Opened ? "SELECT" : "BACK", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);
		}

		static Timer backTimer(0ms);
		backTimer.SetDelay(std::chrono::milliseconds(m_BackDelay));
		if (m_Opened && m_BackKeyPressed && backTimer.Update() || m_Opened && PAD::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendCancel) && m_Controllerinput && backTimer.Update())
		{
			if (m_Sounds)
				AUDIO::PLAY_SOUND_FRONTEND(-1, "BACK", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

			if (m_SubmenuStack.size() <= 1)
			{
				m_Opened = false;
			}
			else
			{
				m_SubmenuStack.pop();
			}
		}

		if (m_Opened && !m_SubmenuStack.empty())
		{
			auto sub = m_SubmenuStack.top();

			static Timer enterTimer(0ms);
			enterTimer.SetDelay(std::chrono::milliseconds(m_EnterDelay));
			if (m_EnterKeyPressed && sub->GetNumOptions() != 0 && enterTimer.Update() || PAD::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept) && m_Controllerinput && sub->GetNumOptions() != 0 && enterTimer.Update())
			{
				if (m_Sounds)
					AUDIO::PLAY_SOUND_FRONTEND(-1, "SELECT", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

				if (auto opt = sub->GetOption(sub->GetSelectedOption()))
				{
					opt->HandleAction(OptionAction::EnterPress);
				}
			}

			static Timer upTimer(0ms);
			upTimer.SetDelay(std::chrono::milliseconds(m_VerticalDelay));
			if (m_UpKeyPressed && sub->GetNumOptions() != 0 && upTimer.Update() || PAD::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendUp) && m_Controllerinput && sub->GetNumOptions() != 0 && upTimer.Update())
			{
				if (m_Sounds)
					AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

				sub->ScrollBackward();
			}

			static Timer downTimer(0ms);
			downTimer.SetDelay(std::chrono::milliseconds(m_VerticalDelay));
			if (m_DownKeyPressed && sub->GetNumOptions() != 0 && downTimer.Update() || PAD::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendDown) && m_Controllerinput && sub->GetNumOptions() != 0 && downTimer.Update())
			{
				if (m_Sounds)
					AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

				sub->ScrollForward();

			}

			static Timer leftTimer(0ms);
			leftTimer.SetDelay(std::chrono::milliseconds(m_HorizontalDelay));
			if (m_LeftKeyPressed && sub->GetNumOptions() != 0 && leftTimer.Update() || PAD::IS_DISABLED_CONTROL_PRESSED(0, ControlPhoneLeft) && m_Controllerinput && sub->GetNumOptions() != 0 && leftTimer.Update())
			{
				if (m_Sounds)
					AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_LEFT_RIGHT", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

				if (auto opt = sub->GetOption(sub->GetSelectedOption()))
				{
					opt->HandleAction(OptionAction::LeftPress);
				}
			}

			static Timer rightTimer(0ms);
			rightTimer.SetDelay(std::chrono::milliseconds(m_HorizontalDelay));
			if (m_RightKeyPressed && sub->GetNumOptions() != 0 && rightTimer.Update() || PAD::IS_DISABLED_CONTROL_PRESSED(0, ControlPhoneRight) && m_Controllerinput && sub->GetNumOptions() != 0 && rightTimer.Update())
			{
				if (m_Sounds)
					AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_LEFT_RIGHT", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

				if (auto opt = sub->GetOption(sub->GetSelectedOption()))
				{
					opt->HandleAction(OptionAction::RightPress);
				}
			}
		}
	}

	void UIManager::ResetInput()
	{
		m_OpenKeyPressed = false;
		m_BackKeyPressed = false;
		m_EnterKeyPressed = false;
		m_UpKeyPressed = false;
		m_DownKeyPressed = false;
		m_LeftKeyPressed = false;
		m_RightKeyPressed = false;
	}

	void UIManager::DrawHeader(AbstractSubmenu* sub)
	{

		switch (m_HeaderType)
		{
		case HeaderType::Static:

			DrawSprite("arcadeui_kitty_claw",
				"arcadeui_kitty_claw",
				m_PosX - (m_HeaderGradientStretch / 2.f),
				m_DrawBaseY + (m_HeaderHeight / 2.f),
				m_Width + m_HeaderGradientStretch + m_HeaderGradientFiller,
				m_HeaderHeight,
				{ 255, 255, 255, m_HeaderBackgroundColor.a },
				0);

			break;
		}

		if (m_HeaderText)
		{
			if (TextKek)
			{
				DrawCenteredText(
					textkek.c_str(),
					m_PosX,
					m_DrawBaseY + (m_HeaderHeight / 2.f) - (GetTextHeight(m_HeaderFont, m_HeaderTextSize) / 2.f),
					m_HeaderTextSize,
					m_HeaderFont,
					m_HeaderTextColor,
					false, true);
			}
			else
			{
				DrawCenteredText(
					sub->GetName(),
					m_PosX,
					m_DrawBaseY + (m_HeaderHeight / 2.f) - (GetTextHeight(m_HeaderFont, m_HeaderTextSize) / 2.f),
					m_HeaderTextSize,
					m_HeaderFont,
					m_HeaderTextColor,
					false, true);
			}
		}

		m_DrawBaseY += m_HeaderHeight;
	}

	void UIManager::DrawSubmenuBar(AbstractSubmenu* sub)
	{
		char leftText[64] = {};
		std::strncpy(&leftText[0], sub->GetName(), sizeof(leftText) - 1);
		std::transform(std::begin(leftText), std::end(leftText), std::begin(leftText), [](char c) { return static_cast<char>((c)); });
		char rightText[32] = {};
		std::snprintf(rightText, sizeof(rightText) - 1, "%zu / %zu", sub->GetSelectedOption() + 1, sub->GetNumOptions());


		DrawRect(
			m_PosX,
			m_DrawBaseY + (m_SubmenuBarHeight / 2.f),
			m_Width, m_SubmenuBarHeight,
			m_SubmenuBarBackgroundColor);
		DrawRect(
			m_PosX,
			m_DrawBaseY - 0.0001f + m_SubmenuBarHeight,
			m_Width + 0.0005f, 0.0026f,
			m_linecolor);
		DrawLeftText(
			&leftText[0],
			m_PosX - (m_Width / m_SubmenuBarPadding),
			m_DrawBaseY + (m_SubmenuBarHeight / 2.f) - (GetTextHeight(m_SubmenuBarFont, m_SubmenuBarTextSize) / 1.5f),
			m_SubmenuBarTextSize, m_SubmenuBarFont,
			m_SubmenuBarTextColor,
			false, true);
		DrawRightText(
			&rightText[0],
			m_PosX + (m_Width / m_SubmenuBarPadding),
			m_DrawBaseY + (m_SubmenuBarHeight / 2.f) - (GetTextHeight(m_SubmenuBarFont, m_SubmenuBarTextSize) / 1.5f),
			m_SubmenuBarTextSize, m_SubmenuBarFont,
			m_SubmenuBarTextColor,
			false, true);
		if (m_ShowScrollbar2)
		{
			DrawRect(
				(m_PosX - (m_Width / 2) - 0.008f),
				m_DrawBaseY + (0.021f / 1.f),
				0.009f, 0.021f,
				{ 0, 0, 0, 255 });
			const char* texture = "arrowright";
			float size = 0.02f;
			auto sizee = GetSpriteScale(size);
			DrawSprite(
				"commonmenu",
				texture,
				(m_PosX - (m_Width / 2) - 0.008f),
				m_DrawBaseY + (0.021f / 1.f),
				sizee.x,
				sizee.y,
				{ 255,255,255,255 },
				270.f);

		}

		m_DrawBaseY += m_SubmenuBarHeight;
	}

	void UIManager::DrawOption(AbstractOption* opt, AbstractSubmenu* sub, bool selected)
	{
		if (opt->GetFlag(OptionFlag::Enterable))
		{
			if (IndicatorIterator == 0)
			{
				float size = 0.02f;
				auto sizee = GetSpriteScale(size);
				DrawSprite(
					"helicopterhud",
					"hudarrow",
					(m_PosX + (m_Width / 15.11) + 0.085f),
					m_DrawBaseY + (0.021f / 1.f),
					sizee.x,
					sizee.y,
					{ 255,255,255,255 },
					90.f);
			}
			else if (IndicatorIterator == 1)
			{
				float size = 0.02f;
				auto sizee = GetSpriteScale(size);
				DrawSprite(
					"commonmenu",
					"arrowright",
					(m_PosX + (m_Width / 15.11) + 0.085f),
					m_DrawBaseY + (0.021f / 1.f),
					sizee.x,
					sizee.y,
					{ 255,255,255,255 },
					0.f);
			}
			else if (IndicatorIterator == 2)
			{
				DrawRect(m_PosX + (m_Width / m_OptionPadding) + 0.003f,
					m_DrawBaseY + ((m_OptionHeight) / 2.f), 0.0055,
					m_OptionHeight,
					{ m_HeaderBackgroundColor.r, m_HeaderBackgroundColor.g, m_HeaderBackgroundColor.b, 190 });
			}

		}

		if (opt->GetFlag(OptionFlag::BoolOption))
		{
			auto res = GetSpriteScale(m_ToggleScale);
			if (ToggleIterator == 0)
			{
				if (ToggledOn)
				{
					GRAPHICS::DRAW_SPRITE("CommonMenu", "shop_box_tick",
						g_UiManager->m_PosX + (g_UiManager->m_Width / g_UiManager->m_OptionPadding - 0.005f)
						, g_UiManager->m_DrawBaseY + (g_UiManager->m_OptionHeight / 2.f) - (g_UiManager->GetTextHeight(g_UiManager->m_OptionFont
							, g_UiManager->m_OptionTextSize) / 1.5f) + 0.014f
						, res.x, res.y, 0.0, m_SelectedToggle.r, m_SelectedToggle.g, m_SelectedToggle.b, m_SelectedToggle.a, 1, 0);
				}
				else if (!ToggledOn)
				{
					GRAPHICS::DRAW_SPRITE("CommonMenu", "shop_box_blank",
						g_UiManager->m_PosX + (g_UiManager->m_Width / g_UiManager->m_OptionPadding - 0.005f)
						, g_UiManager->m_DrawBaseY + (g_UiManager->m_OptionHeight / 2.f) - (g_UiManager->GetTextHeight(g_UiManager->m_OptionFont
							, g_UiManager->m_OptionTextSize) / 1.5f) + 0.014f
						, res.x, res.y, 0.0, m_UnselectedToggle.r, m_UnselectedToggle.g, m_UnselectedToggle.b, m_UnselectedToggle.a, 1, 0);
				}
			}
			else if (ToggleIterator == 1)
			{
				if (ToggledOn)
				{
					GRAPHICS::DRAW_SPRITE("commonmenu", "common_medal",
						g_UiManager->m_PosX + (g_UiManager->m_Width / g_UiManager->m_OptionPadding - 0.005f)
						, g_UiManager->m_DrawBaseY + (g_UiManager->m_OptionHeight / 2.f) - (g_UiManager->GetTextHeight(g_UiManager->m_OptionFont
							, g_UiManager->m_OptionTextSize) / 1.5f) + 0.014f
						, res.x, res.y, 0.0, 255, 255, 255, 255, 1, 0);
				}
				else if (!ToggledOn)
				{
					GRAPHICS::DRAW_SPRITE("commonmenu", "common_medal",
						g_UiManager->m_PosX + (g_UiManager->m_Width / g_UiManager->m_OptionPadding - 0.005f)
						, g_UiManager->m_DrawBaseY + (g_UiManager->m_OptionHeight / 2.f) - (g_UiManager->GetTextHeight(g_UiManager->m_OptionFont
							, g_UiManager->m_OptionTextSize) / 1.5f) + 0.014f
						, res.x, res.y, 0.0, 255, 0, 0, 255, 1, 0);
				}
			}
		}
		if (opt->GetFlag(OptionFlag::BreakOption))
		{
			DrawLeftText(
				opt->GetMiddleText(),
				(m_PosX - (m_Width / 10) - 0.0022f),
				m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(m_OptionFont, m_OptionTextSize) / 1.5f),
				0.38,
				Font::HouseScript,
				{ m_separatorcolor },
				false, false);
		}
		if (opt->GetFlag(OptionFlag::BreakOption) && selected)
		{
			if (m_DownKeyPressed)
			{
				if (sub->GetOption(sub->GetSelectedOption())->GetFlag(OptionFlag::BreakOption))
				{
					sub->SetSelectedOption(sub->GetSelectedOption() + 1);
				}
			}
			else if (m_UpKeyPressed)
			{
				if (sub->GetOption(sub->GetSelectedOption())->GetFlag(OptionFlag::BreakOption))
				{
					sub->SetSelectedOption(sub->GetSelectedOption() - 1);
				}
			}
		}
		if (m_ShowScrollbar2)
		{
			DrawRect(
				(m_PosX - (m_Width / 2) - 0.008f),
				m_DrawBaseY + (m_OptionHeight / 2.f),
				0.009f, m_OptionHeight,
				{ 0,0,0,170 });

		}
		if (selected)
		{
			if (!m_Smoothscroll)
			{

				DrawRect(
					m_PosX,
					m_DrawBaseY + (m_OptionHeight / 2.f),
					m_Width,
					m_OptionHeight,
					m_OptionSelectedBackgroundColor);

			}
			else
			{
				scrollTarget = m_DrawBaseY + (m_OptionHeight / 2.f);
			}

		}
		if (selected, m_ShowScrollbar2)
		{
			DrawRect(
				m_PosX - 0.113 - ((m_Width - 0.21) / 2),
				scrollCurrent,
				0.008,
				m_OptionHeight,
				m_OptionSelectedBackgroundColor);

		}
		DrawLeftText(
			opt->GetLeftText(),
			m_PosX - (m_Width / m_OptionPadding),
			m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(m_OptionFont, m_OptionTextSize) / 1.5f),
			m_OptionTextSize,
			m_OptionFont,
			selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor,
			false, false);

		DrawRightText(
			opt->GetRightText(),
			m_PosX + (m_Width / m_OptionPadding),
			m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(m_OptionFont, m_OptionTextSize) / 1.5f),
			m_OptionTextSize,
			m_OptionFont,
			selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor,
			false, false);

		m_DrawBaseY += m_OptionHeight;
	}

	void UIManager::DrawFooter()
	{
		char leftText[64] = {};
		std::strncpy(&leftText[0], "By XIFI", sizeof(leftText) - 1);
		std::transform(std::begin(leftText), std::end(leftText), std::begin(leftText), [](char c) { return static_cast<char>((c)); });
		char rightText[64] = {};
		std::strncpy(&rightText[0], ".gg/poseidoncheats", sizeof(leftText) - 1);
		std::transform(std::begin(rightText), std::end(rightText), std::begin(rightText), [](char c) { return static_cast<char>((c)); });

		float size = m_FooterSpriteSize;
		float rotation = 0.f;
		const char* texture = "shop_arrows_upanddown";

		auto sizee = GetSpriteScale(size);


		DrawRect(
			m_PosX,
			m_DrawBaseY + (m_FooterHeight / 2.f),
			m_Width,
			m_FooterHeight,
			m_FooterBackgroundColor);
		DrawRect(
			m_PosX,
			m_DrawBaseY - 0.0001f,
			m_Width + 0.0005f, 0.0026f,
			m_linecolor);

		if (!m_SubmenuStack.empty())
		{
			auto sub = m_SubmenuStack.top();
			if (sub->GetSelectedOption() == 0)
			{
				rotation = 90.f;
				texture = "arrowright";
				size *= 0.8f;
			}
			else if (sub->GetSelectedOption() + 1 == sub->GetNumOptions())
			{
				rotation = 270.f;
				texture = "arrowright";
				size *= 0.8f;
			}
		}

		DrawSprite(
			"commonmenu",
			texture,
			m_PosX,
			m_DrawBaseY + (m_FooterHeight / 2.f),
			sizee.x,
			sizee.y,
			m_FooterSpriteColor,
			rotation);
		DrawLeftText(
			&leftText[0],
			m_PosX - (m_Width / m_SubmenuBarPadding),
			m_DrawBaseY + (m_SubmenuBarHeight / 2.f) - (GetTextHeight(m_SubmenuBarFont, m_SubmenuBarTextSize) / 1.5f),
			m_SubmenuBarTextSize, m_SubmenuBarFont,
			m_SubmenuBarTextColor,
			false, true);
		DrawRightText(
			&rightText[0],
			m_PosX + (m_Width / m_SubmenuBarPadding),
			m_DrawBaseY + (m_SubmenuBarHeight / 2.f) - (GetTextHeight(m_SubmenuBarFont, m_SubmenuBarTextSize) / 1.5f),
			m_SubmenuBarTextSize, m_SubmenuBarFont,
			m_SubmenuBarTextColor,
			false, true);
		if (m_ShowScrollbar2)
		{

			DrawRect(
				(m_PosX - (m_Width / 2) - 0.008f),
				m_DrawBaseY + (0.021f / 2.f),
				0.009f, 0.021f,
				{ 0, 0, 0, 255 });
			const char* texture = "arrowleft";
			float size = 0.02f;
			auto sizee = GetSpriteScale(size);
			DrawSprite(
				"commonmenu",
				texture,
				(m_PosX - (m_Width / 2) - 0.008f),
				m_DrawBaseY + (0.021f / 2.f),
				sizee.x,
				sizee.y,
				{ 255,255,255,255 },
				270.f);
		}
		m_DrawBaseY += m_FooterHeight;
	}

	void UIManager::DrawDescription()
	{
		const char* description{};

		if (!m_SubmenuStack.empty())
		{
			auto sub = m_SubmenuStack.top();
			if (sub->GetNumOptions())
			{
				if (auto opt = sub->GetOption(sub->GetSelectedOption()))
				{
					description = opt->GetDescription();
				}
			}
		}

		if (!description || !*description)
			return;

		m_DrawBaseY += m_DescriptionHeightPadding;

		DrawRect(
			m_PosX,
			m_DrawBaseY + (m_DescriptionHeight / 2.f),
			m_Width,
			m_DescriptionHeight,
			m_DescriptionBackgroundColor);
		DrawRect(
			m_PosX,
			m_DrawBaseY - 0.0001f,
			m_Width + 0.0005f, 0.0026f,
			m_linecolor);

		auto spriteSize = GetSpriteScale(m_DescriptionSpriteSize);

		DrawLeftText(
			description,
			m_PosX - (m_Width / m_DescriptionPadding) + (spriteSize.x * 1.15f),
			m_DrawBaseY + (m_DescriptionHeight / 2.f) - (GetTextHeight(m_DescriptionFont, m_DescriptionTextSize) / 1.5f),
			m_DescriptionTextSize,
			m_DescriptionFont,
			m_DescriptionTextColor,
			false, false
		);

		m_DrawBaseY += m_DescriptionHeight;
	}
	void UIManager::DrawRect(float x, float y, float width, float height, Color color)
	{
		GRAPHICS::DRAW_RECT(x, y, width, height, color.r, color.g, color.b, color.a, 0);
	}

	void UIManager::DrawSprite(const char* dict, const char* texture, float x, float y, float width, float height, Color color, float rotation)
	{
		if (GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(dict))
		{
			GRAPHICS::DRAW_SPRITE(dict, texture, x, y, width, height, rotation, color.r, color.g, color.b, color.a, 0, 0);
		}
		else
		{
			GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(dict, false);
		}
	}

	void UIManager::DrawLeftText(const char* text, float x, float y, float size, Font font, Color color, bool outline, bool shadow)
	{
		HUD::SET_TEXT_SCALE(size, size);
		HUD::SET_TEXT_FONT(static_cast<int>(font));
		HUD::SET_TEXT_COLOUR(color.r, color.g, color.b, color.a);
		if (outline)
			HUD::SET_TEXT_OUTLINE();
		if (shadow)
			HUD::SET_TEXT_DROP_SHADOW();

		HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
		HUD::END_TEXT_COMMAND_DISPLAY_TEXT(x, y, 0);
	}

	void UIManager::DrawCenteredText(const char* text, float x, float y, float size, Font font, Color color, bool outline, bool shadow)
	{
		HUD::SET_TEXT_CENTRE(true);
		DrawLeftText(text, x, y, size, font, color, outline, shadow);
	}

	void UIManager::DrawRightText(const char* text, float x, float y, float size, Font font, Color color, bool outline, bool shadow)
	{
		HUD::SET_TEXT_WRAP(0.f, x);
		HUD::SET_TEXT_RIGHT_JUSTIFY(true);
		DrawLeftText(text, x, y, size, font, color, outline, shadow);
	}

	void UIManager::Spriter(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a)
	{
		if (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED((char*)Streamedtexture.c_str()))
		{
			GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT((char*)Streamedtexture.c_str(), false);
		}
		else
		{
			GRAPHICS::DRAW_SPRITE((char*)Streamedtexture.c_str(), (char*)textureName.c_str(), x, y, width, height, rotation, r, g, b, a, 0, 0);
		}
	}
	float UIManager::GetTextHeight(Font font, float size)
	{
		return HUD::GET_RENDERED_CHARACTER_HEIGHT(size, static_cast<int>(font));
	}

	Vector2 UIManager::GetSpriteScale(float size)
	{
		int x;
		int y;
		GRAPHICS::GET_ACTUAL_SCREEN_RESOLUTION(&x, &y);

		return { (static_cast<float>(y) / static_cast<float>(x)) * size, size };
	}

	bool UIManager::IsMouseLocked()
	{
		return m_Opened && m_MouseLocked;
	}

	Rectangle UIManager::GetMenuRect()
	{
		float height = m_HeaderHeight;
		height += m_SubmenuBarHeight;

		if (!m_SubmenuStack.empty())
		{
			height += m_OptionHeight * std::min(m_SubmenuStack.top()->GetNumOptions(), m_OptionsPerPage);
		}

		height += m_FooterHeight;

		return
		{
			{ m_PosX + (m_Width / 2.f), m_PosY + (height / 2.f) },
			{ m_Width, height }
		};
	}

	Vector2 UIManager::GetMousePos()
	{
		POINT point;
		GetCursorPos(&point);

		return Vector2{ static_cast<float>(point.x), static_cast<float>(point.y) };
	}
}

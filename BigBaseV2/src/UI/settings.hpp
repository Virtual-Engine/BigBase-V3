#pragma once
#include "Logger.hpp"
#include <nlohmann/json.hpp>
#include "Types.hpp"

namespace big
{
    inline bool g_InPlayerList{ false };
    inline bool g_IsPlayerMe{ false };

    class Settings
    {
    public:
        nlohmann::json m_Options;

        std::string appdatapath = getenv("appdata") + std::string("\\BigBaseV2");

        std::atomic_bool m_LogWindow = false;
        std::atomic_bool m_LockMouse = false;
        std::atomic_bool m_Auth = true;
        bool m_EnableRGBWheel = false;
        bool m_EnableThemeWindow = false;
        Vector2 screenResolution;

        nlohmann::json m_DefaultOptions
        {
            { "IndicatorIterator", 0},
            { "ToggleIterator" , 0 },
            { "ToggleIterator" , 0 },
            { "m_BackDelay" , 300 },
            { "m_linecolor.a" , 255 },
            { "m_linecolor.b" , 255 },
            { "m_linecolor.g" , 5 },
            { "m_linecolor.r" , 107 },
            { "m_ShowScrollbar" , false },
            { "m_ShowScrollbar2" , true },
            { "m_lineactivate" , false },
            { "m_DescriptionBackgroundColor.a" , 20 },
            { "m_DescriptionBackgroundColor.b" , 20 },
            { "m_DescriptionBackgroundColor.g",  20 },
            { "m_DescriptionBackgroundColor.r" , 20 },
            { "m_DescriptionHeight" , 0.33 },
            { "m_DescriptionHeightPadding" , 0.01 },
            { "m_DescriptionPadding" , 2.0999999046325684 },
            { "m_DescriptionSpriteColor.a" , 255 },
            { "m_DescriptionSpriteColor.b" , 255 },
            { "m_DescriptionSpriteColor.g" , 255 },
            { "m_DescriptionSpriteColor.r" , 255 },
            { "m_DescriptionSpriteSize" , 0.02500000037252903 },
            { "m_DescriptionTextColor.a" , 255 },
            { "m_DescriptionTextColor.b" , 255 },
            { "m_DescriptionTextColor.g" , 255 },
            { "m_DescriptionTextColor.r" , 255 },
            { "m_DescriptionTextSize" , 0.2800000011920929 },
            { "m_EnterDelay" , 300 },
            { "m_FooterBackgroundColor.a" , 0 },
            { "m_FooterBackgroundColor.b" , 255 },
            { "m_FooterBackgroundColor.g" , 255 },
            { "m_FooterBackgroundColor.r" , 0 },
            { "m_FooterHeight" , 0.007 },
            { "m_FooterSpriteColor.a" , 255 },
            { "m_FooterSpriteColor.b" , 255 },
            { "m_FooterSpriteColor.g" , 255 },
            { "m_FooterSpriteColor.r" , 255 },
            { "m_FooterSpriteSize" , 0.005 },
            { "m_HeaderBackgroundColor.a" , 255 },
            { "m_HeaderBackgroundColor.b" , 0 },
            { "m_HeaderBackgroundColor.g" , 0 },
            { "m_HeaderBackgroundColor.r" , 0 },
            { "m_HeaderGradientColorLeft.a" , 255 },
            { "m_HeaderGradientColorLeft.b" , 255 },
            { "m_HeaderGradientColorLeft.g" , 255 },
            { "m_HeaderGradientColorLeft.r" , 0 },
            { "m_HeaderGradientColorRight.a" , 253 },
            { "m_HeaderGradientColorRight.b" , 252 },
            { "m_HeaderGradientColorRight.g" , 211 },
            { "m_HeaderGradientColorRight.r" , 0 },
            { "m_HeaderGradientFiller" , 0.0 },
            { "m_HeaderGradientFlip" , false },
            { "m_HeaderGradientStretch" , 0.0 },
            { "m_HeaderGradientTransparent" , false },
            { "m_HeaderHeight" , 0.10 },
            { "m_HeaderText" , true },
            { "m_HeaderTextColor.a" , 255 },
            { "m_HeaderTextColor.b" , 0 },
            { "m_HeaderTextColor.g" , 0 },
            { "m_HeaderTextColor.r" , 0 },
            { "m_HeaderTextSize" , 1.0 },
            { "m_HorizontalDelay" , 120 },
            { "m_OpenDelay" , 200 },
            { "m_OptionHeight" , 0.04 },
            { "m_OptionPadding" , 2.1 },
            { "m_OptionSelectedBackgroundColor.a" , 255 },
            { "m_OptionSelectedBackgroundColor.b" , 255 },
            { "m_OptionSelectedBackgroundColor.g" , 255 },
            { "m_OptionSelectedBackgroundColor.r" , 255 },
            { "m_OptionSelectedTextColor.a" , 255 },
            { "m_OptionSelectedTextColor.b" , 0 },
            { "m_OptionSelectedTextColor.g" , 0 },
            { "m_OptionSelectedTextColor.r" , 0 },
            { "m_OptionTextSize" , 0.30000001192092896 },
            { "m_OptionUnselectedBackgroundColor.a" , 255 },
            { "m_OptionUnselectedBackgroundColor.b" , 255 },
            { "m_OptionUnselectedBackgroundColor.g" , 255 },
            { "m_OptionUnselectedBackgroundColor.r" , 255 },
            { "m_OptionUnselectedTextColor.a" , 255 },
            { "m_OptionUnselectedTextColor.b" , 255 },
            { "m_OptionUnselectedTextColor.g" , 255 },
            { "m_OptionUnselectedTextColor.r" , 255 },
            { "m_OptionsPerPage" , 11 },
            { "m_PosX" , 0.84 },
            { "m_PosY" , 0.15 },
            { "m_SelectedToggle.a" , 255 },
            { "m_SelectedToggle.b" , 255 },
            { "m_SelectedToggle.g" , 255 },
            { "m_SelectedToggle.r" , 255 },
            { "m_ShowSubmenubar" , false },
            { "m_SubmenuBarBackgroundColor.a" , 255 },
            { "m_SubmenuBarBackgroundColor.b" , 0 },
            { "m_SubmenuBarBackgroundColor.g" , 0 },
            { "m_SubmenuBarBackgroundColor.r" , 0 },
            { "m_SubmenuBarHeight" , 0.023f },
            { "m_SubmenuBarPadding" , 2.1f },
            { "m_SubmenuBarTextColor.a" , 225 },
            { "m_SubmenuBarTextColor.b" , 255 },
            { "m_SubmenuBarTextColor.g" , 255 },
            { "m_SubmenuBarTextColor.r" , 255 },
            { "m_SubmenuBarTextSize" , 0.31f },
            { "m_ToggleScale" , 0.04 },
            { "m_UnselectedToggle.a" , 255 },
            { "m_UnselectedToggle.b" , 255 },
            { "m_UnselectedToggle.g" , 255 },
            { "m_UnselectedToggle.r" , 255 },
            { "m_VerticalDelay" , 120 },
            { "m_Width" , 0.2200000137090683 },
            { "m_HeaderType", 2 },
            { "m_Smoothscroll", true },
            { "m_ScrollSpeed", 0.1f },
            { "TextKek", false },
            { "textkek", "OverKill" }
        };

        void WriteDefaultConfig()
        {
            std::string path = appdatapath + "\\Themes\\Settings.json";
            //g_Logger->Info(path.c_str());
            std::ofstream file(path, std::ios::out);
            file << m_DefaultOptions.dump(4);
            file.close();
            m_Options.clear();
            m_Options = m_DefaultOptions;
        }

        void Initialize()
        {
            std::string path = appdatapath + "\\Themes\\";
            if (!std::filesystem::exists(path))
            {
                std::filesystem::create_directory(path);
            }

            path = appdatapath + "\\Themes\\Settings.json";
            // g_Logger->Info(path.c_str());
            if (!std::filesystem::exists(path))
            {
                LOG(INFO) << "Creating settings...";
                WriteDefaultConfig();
            }
            std::ifstream file(path);
            file.open(path);

            file >> m_Options;

            for (auto& e : m_Options.items())
            {
                if (m_Options.count(e.key()) == 0)
                {
                    path = true;
                    m_Options[e.key()] = e.value();
                }
            }
            LOG(INFO) << "Successfully loaded settings...";
        }
    };
    inline Settings g_Settings;
}
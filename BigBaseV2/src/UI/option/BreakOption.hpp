#pragma once
#include "UI/option/BaseOption.hpp"
#include "UI/UIManager.hpp"

namespace big::UserInterface
{

	class BreakOption : public BaseOption<BreakOption>
	{
	public:
		explicit BreakOption() = default;
		explicit BreakOption(const char* breaktext, const char* description = nullptr, std::function<void()> action = [] {})
		{
			SetMiddleText(((std::string)breaktext).c_str());
			if (description)
				SetDescription(description);
			SetAction(std::move(action));
		}

		bool GetFlag(OptionFlag flag) override
		{
			if (flag == OptionFlag::BreakOption)
			{
				return true;
			}

			return false;
		}
		~BreakOption() noexcept = default;
		BreakOption(BreakOption const&) = default;
		BreakOption& operator=(BreakOption const&) = default;
		BreakOption(BreakOption&&) = default;
		BreakOption& operator=(BreakOption&&) = default;
	};
}

#pragma once

namespace big::UserInterface
{
	enum class OptionAction
	{
		LeftPress,
		RightPress,
		EnterPress,
		click
	};

	enum class OptionFlag
	{
		Horizontal = (1 << 0),
		Enterable = (1 << 1),
		BoolOption = (1 << 2),
		NumberOption = (1 << 3),
		BreakOption = 5
	};

	class AbstractOption
	{
	public:
		virtual ~AbstractOption() noexcept = default;

		virtual const char* GetLeftText() = 0;
		virtual const char* GetRightText() = 0;
		virtual const char* GetMiddleText() = 0;
		virtual const char* GetDescription() = 0;
		virtual void HandleAction(OptionAction action) = 0;
		virtual bool GetFlag(OptionFlag flag) = 0;
	protected:
		explicit AbstractOption() = default;
		AbstractOption(AbstractOption const&) = default;
		AbstractOption& operator=(AbstractOption const&) = default;
		AbstractOption(AbstractOption&&) = default;
		AbstractOption& operator=(AbstractOption&&) = default;
	};
}

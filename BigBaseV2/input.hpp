#pragma once
#include "common.hpp"
#include <set>
namespace big {
	class Input {
	public:
		typedef void(*KeyboardFunction)(DWORD key, WORD repeats, uint8_t scanCode, BOOL isExtended, BOOL isWithAlt, BOOL wasDownBefore, BOOL isUpNow);
		static bool Initialize();
		static void Cleanup();

		static std::set<KeyboardFunction> g_keyboardFunctions;
	private:
		static LRESULT APIENTRY WindowProcess(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		static WNDPROC m_windowProc;
	};
}
#include "common.hpp"
#include "input.hpp"
#include "keyboard.hpp"

WNDPROC big::Input::m_windowProc;
std::set<big::Input::KeyboardFunction> big::Input::g_keyboardFunctions;
namespace big {
	bool Input::Initialize() {
		m_windowProc = (WNDPROC)SetWindowLongPtrA(m_hWindow, GWLP_WNDPROC, (__int3264)(LONG_PTR)WindowProcess);

		if (m_windowProc == nullptr) return false;
		LOG(INFO) << "IH initialized";
		return true;
	}

	LRESULT APIENTRY Input::WindowProcess(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

		switch (uMsg) {
		case WM_SIZE: return DefWindowProc(hwnd, uMsg, wParam, lParam);
		case WM_KEYDOWN:
		case WM_KEYUP:
		case WM_SYSKEYDOWN:
		case WM_SYSKEYUP: {
			GetKeyboard()->OnKeyboardMessage((DWORD)wParam, lParam & 0xFFFF, (lParam >> 16) & 0xFF, (lParam >> 24) & 1, (uMsg == WM_SYSKEYDOWN || uMsg == WM_SYSKEYUP), (lParam >> 30) & 1, (uMsg == WM_SYSKEYUP || uMsg == WM_KEYUP));
			auto functions = g_keyboardFunctions; for (auto& function : functions) function((DWORD)wParam, lParam & 0xFFFF, (lParam >> 16) & 0xFF, (lParam >> 24) & 1, (uMsg == WM_SYSKEYDOWN || uMsg == WM_SYSKEYUP), (lParam >> 30) & 1, (uMsg == WM_SYSKEYUP || uMsg == WM_KEYUP));
			break;
		}
		}
		return CallWindowProc(m_windowProc, hwnd, uMsg, wParam, lParam);
	}

	void Input::Cleanup() {
		SetWindowLongPtrA(m_hWindow, GWLP_WNDPROC, (LONG_PTR)m_windowProc);
		LOG(INFO) << "Disabled IH";
	}
}
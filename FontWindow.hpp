#pragma once
#include "BaseWindow.hpp"

class FontWindow : public BaseWindow<FontWindow> {
	public:
		FontWindow();
		FontWindow(const wchar_t*, int, int, int, int);
		PCWSTR className() const;
		LRESULT handleMessage(UINT, WPARAM, LPARAM);
	private:
		void addWidgets();
};
#include "FontWindow.hpp"

FontWindow::FontWindow(): BaseWindow() {};

FontWindow::FontWindow(const wchar_t* name, int x, int y, int width, int height) : BaseWindow(name, x, y, width, height) {}

PCWSTR FontWindow::className() const {
	return L"Font window";
}
LRESULT FontWindow::handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		case WM_CREATE: {
			addWidgets();
		}
		default: {
			return DefWindowProc(window_handler, uMsg, wParam, lParam);
		}
	}

	return TRUE;
}


void FontWindow::addWidgets() {
	//CreateWindowExW(WS_EX_CLIENTEDGE, L"", NULL, WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_HSCROLL | WS_VSCROLL, 5, 0, 100, 100, getWindow(), NULL, NULL, NULL);
}
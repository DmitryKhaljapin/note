#pragma once
#include "BaseWindow.hpp"
#include "FontWindow.hpp"

#define onFileLoad 2
#define onFileSave 3
#define onExitSimpleWindow 6
#define onFontChange 19

class MainWindow : public BaseWindow<MainWindow> {
	private:
		HWND text_area_handler = 0;
		OPENFILENAMEA open_file_params;
		char file_name[260]{};
		HFONT font{};

		void setMenu();
		void addWidgets();
		void setFont();

	public:
		FontWindow font_window;

		MainWindow(const wchar_t*, int, int, int, int);
		PCWSTR className() const;
		LRESULT handleMessage(UINT, WPARAM, LPARAM);

		void fileSaveHandler(LPCSTR path) const;
		void fileLoadHandler(LPCSTR path);

		void openFontChangeWindow() const;
};
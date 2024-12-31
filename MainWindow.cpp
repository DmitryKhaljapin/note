#include "MainWindow.hpp"
#include "FontWindow.hpp"

MainWindow::MainWindow(const wchar_t* window_name, int x, int y, int width, int height) : BaseWindow(window_name, x, y, width, height), open_file_params({}) {
	ZeroMemory(&open_file_params, sizeof(open_file_params));
	open_file_params.lStructSize = sizeof(open_file_params);
	open_file_params.hwndOwner = window_handler;
	open_file_params.lpstrFile = file_name;
	open_file_params.nMaxFile = sizeof(file_name);
	open_file_params.lpstrFilter = ".txt";
	open_file_params.lpstrFileTitle = NULL;
	open_file_params.nMaxFileTitle = 0;
	open_file_params.lpstrInitialDir = NULL;
	open_file_params.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
};

PCWSTR MainWindow::className() const  {
	return L"Main window class";
}


LRESULT MainWindow::handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		case WM_CREATE: {
			setMenu();
			addWidgets();
			setFont();
			break;
		}
		case WM_COMMAND: {
			switch (wParam) {
				case onFileSave: {
					if (GetSaveFileNameA(&open_file_params)) { fileSaveHandler(file_name); }
					break;
				}
				case onFileLoad: {
					if (GetOpenFileNameA(&open_file_params)) { fileLoadHandler(file_name); }
					break;
				}
				case onFontChange: {
					openFontChangeWindow();
					break;
				}
				case onExitSimpleWindow: {
					if (MessageBox(window_handler, L"Are you shure?", L"Closing", MB_OKCANCEL) == IDOK) {
						DestroyWindow(window_handler);
					}
					return 0;
				}
			}
			break;
		}
		case WM_SIZE: {
			SetWindowPos(text_area_handler, nullptr, 0, 0, LOWORD(lParam) - 5, HIWORD(lParam), SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER);
			break;
		}
		case WM_DESTROY: {

			PostQuitMessage(0);

			return 0;
		}
		/*case WM_LBUTTONDOWN: {

			pos_x = pos_x - 10;

			MoveWindow(window_handler, pos_x, pos_y, width, height, TRUE);
			break;
		}
		case WM_RBUTTONDOWN: {

			pos_x = pos_x + 10;

			MoveWindow(window_handler, pos_x, pos_y, width, height, TRUE);
			break;
		}*/
		case WM_PAINT: {
			PAINTSTRUCT ps;

			HDC hdc = BeginPaint(window_handler, &ps);

			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

			EndPaint(window_handler, &ps);
			break;
		}
		case WM_CLOSE: {
			if (MessageBox(window_handler, L"Are you shure?", L"Closing", MB_OKCANCEL) == IDOK) {
				DestroyWindow(window_handler);
			}
			return 0;
		}
		default: {
			return DefWindowProc(window_handler, uMsg, wParam, lParam);
		}
	}

	return TRUE;
}

void MainWindow::setMenu() {
	HMENU root_menu = CreateMenu();

	HMENU file_sub_menu = CreateMenu();

	AppendMenu(file_sub_menu, MF_STRING, NULL, L"New...&\tCtrl+N");
	AppendMenu(file_sub_menu, MF_STRING, onFileLoad, L"Open...&\tCtrl+O");
	AppendMenu(file_sub_menu, MF_STRING, onFileSave, L"Save&\tCtrl+S");
	AppendMenu(file_sub_menu, MF_STRING, NULL, L"Save as...&\tCtrl+Shift+S");
	AppendMenu(file_sub_menu, MF_SEPARATOR, 0, NULL);
	AppendMenu(file_sub_menu, MF_STRING, NULL, L"Print...&\tCtrl+P");
	AppendMenu(file_sub_menu, MF_SEPARATOR, 0, NULL);
	AppendMenu(file_sub_menu, MF_STRING, onExitSimpleWindow, L"Exit&\tAlt+F4");

	HMENU edit_sub_menu = CreateMenu();

	AppendMenu(edit_sub_menu, MF_DISABLED, NULL, L"Undo &\tCtrl+Z");
	AppendMenu(edit_sub_menu, MF_SEPARATOR, 0, NULL);
	AppendMenu(edit_sub_menu, MF_DISABLED, NULL, L"Cut &\tCtrl+X");
	AppendMenu(edit_sub_menu, MF_DISABLED, NULL, L"Copy &\tCtrl+C");
	AppendMenu(edit_sub_menu, MF_STRING, NULL, L"Copy &\tCtrl+V");
	AppendMenu(edit_sub_menu, MF_DISABLED, NULL, L"Delete &\tDel");
	AppendMenu(edit_sub_menu, MF_SEPARATOR, 0, NULL);
	AppendMenu(edit_sub_menu, MF_DISABLED, NULL, L"Find Next &\tF3");
	AppendMenu(edit_sub_menu, MF_DISABLED, NULL, L"Find Previouse &\tShift+F3");
	AppendMenu(edit_sub_menu, MF_STRING, NULL, L"Replace... &\tCtrl+ H");
	AppendMenu(edit_sub_menu, MF_STRING, NULL, L"Go To... &\tCtrl+G");
	AppendMenu(edit_sub_menu, MF_DISABLED, 0, NULL);
	AppendMenu(edit_sub_menu, MF_STRING, NULL, L"Select All &\tCtrl+A");
	AppendMenu(edit_sub_menu, MF_STRING, NULL, L"Time/Date &\tF5");

	HMENU format_sub_menu = CreateMenu();

	AppendMenu(format_sub_menu, MF_CHANGE, NULL, L"Word Wrap");
	AppendMenu(format_sub_menu, MF_STRING, onFontChange, L"Font...");

	HMENU view_sub_menu = CreateMenu();

	HMENU zoom_sub_menu = CreateMenu();

	AppendMenu(zoom_sub_menu, MF_STRING, NULL, L"Zoom In &\tCtrl+Plus");
	AppendMenu(zoom_sub_menu, MF_STRING, NULL, L"Zoom Out &\tCtrl+Minus");
	AppendMenu(zoom_sub_menu, MF_STRING, NULL, L"Restore Default Zoom &\tCtrl+0");

	AppendMenu(view_sub_menu, MF_POPUP, (UINT)zoom_sub_menu, L"Zoom");
	AppendMenu(view_sub_menu, MFS_CHECKED, NULL, L"Status Bar");

	HMENU help_sub_menu = CreateMenu();

	AppendMenu(help_sub_menu, MF_STRING, NULL, L"View Help");
	AppendMenu(help_sub_menu, MF_SEPARATOR, 0, NULL);
	AppendMenu(help_sub_menu, MF_STRING, NULL, L"About SimpleWindow");

	AppendMenu(root_menu, MF_POPUP, (UINT_PTR)file_sub_menu, L"File");
	AppendMenu(root_menu, MF_POPUP, (UINT_PTR)edit_sub_menu, L"Edit");
	AppendMenu(root_menu, MF_POPUP, (UINT_PTR)format_sub_menu, L"Foramt");
	AppendMenu(root_menu, MF_POPUP, (UINT_PTR)view_sub_menu, L"View");
	AppendMenu(root_menu, MF_POPUP, (UINT_PTR)help_sub_menu, L"Help");

	SetMenu(this->window_handler, root_menu);
}

void MainWindow::addWidgets() {

	RECT window_rect;

	GetClientRect(getWindow(), &window_rect);

	int client_width = window_rect.right - window_rect.left;
	int client_height = window_rect.bottom - window_rect.top;

	text_area_handler =  CreateWindowA("edit", "", WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_HSCROLL | WS_VSCROLL, 5, 0, client_width - 5, client_height, getWindow(), NULL, NULL, NULL);
}

void MainWindow::setFont() {
	font = CreateFontA(40, 15, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DECORATIVE, "Simple font");
	SendMessage(text_area_handler, WM_SETFONT, (WPARAM)font, TRUE);
}

void MainWindow::fileSaveHandler(LPCSTR path) const {
	HANDLE file_to_save_handler = CreateFileA(path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	int save_length = GetWindowTextLength(text_area_handler) + 1;

	char* data = new char[save_length];

	save_length = GetWindowTextA(text_area_handler, data, save_length);

	DWORD bytes_iterated;
	WriteFile(file_to_save_handler, data, save_length, &bytes_iterated, NULL);

	CloseHandle(file_to_save_handler);

	delete[] data;
}

void MainWindow::fileLoadHandler(LPCSTR path) {
	HANDLE file_to_load_handler = CreateFileA(path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	
	int data_buffer_size = 10000;

	char* data_buffer = new char[data_buffer_size] {};

	DWORD bytes_iterated;

	ReadFile(file_to_load_handler, data_buffer, data_buffer_size, &bytes_iterated, NULL);

	SetWindowTextA(text_area_handler, data_buffer);

	CloseHandle(file_to_load_handler);

	delete[] data_buffer;
}

void  MainWindow::openFontChangeWindow() const {
	font_window.show();
}
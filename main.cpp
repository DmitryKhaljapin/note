#include <windows.h>
#include "MainWindow.hpp"

//struct WindowInfo {
//	int width = 250;
//	int height = 300;
//	int x = 500;
//	int y = 300;
//};


//LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
//
//	RECT rect = {};
//	WindowInfo* window_info_ptr;
//
//	if (uMsg == WM_CREATE) {
//		CREATESTRUCT* create_struct_ptr = reinterpret_cast<CREATESTRUCT*>(lParam);
//		window_info_ptr = reinterpret_cast<WindowInfo*>(create_struct_ptr->lpCreateParams);
//		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window_info_ptr);
//	}
//	else {
//		LONG_PTR window_long_ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
//		window_info_ptr = reinterpret_cast<WindowInfo*>(window_long_ptr);
//	}
//
//	switch (uMsg) {
//		case WM_DESTROY: {
//
//			PostQuitMessage(0);
//
//			return 0;
//		}
//		case WM_LBUTTONDOWN: {
//
//			window_info_ptr->x = window_info_ptr->x - 10;
//
//			MoveWindow(hwnd, window_info_ptr->x, window_info_ptr->y, window_info_ptr->width, window_info_ptr->height, TRUE);
//			break;
//		}
//		case WM_RBUTTONDOWN: {
//
//			window_info_ptr->x = window_info_ptr->x + 10;
//
//			MoveWindow(hwnd, window_info_ptr->x, window_info_ptr->y, window_info_ptr->width, window_info_ptr->height, TRUE);
//			break;
//		}
//		case WM_SIZE: {
//			int width = LOWORD(lParam);
//			int height = HIWORD(lParam);
//			
//			GetWindowRect(hwnd, &rect);
//
//			break;
//		}
//		case WM_PAINT: {
//			PAINTSTRUCT ps;
//
//			HDC hdc = BeginPaint(hwnd, &ps);
//
//			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
//
//			EndPaint(hwnd, &ps);
//			break;
//		}
//		case WM_CLOSE: {
//			if (MessageBox(hwnd, L"Are you shure?", L"Closing", MB_OKCANCEL) == IDOK) {
//				DestroyWindow(hwnd);
//			}
//			return 0;
//		}
//	}
//
//	return DefWindowProc(hwnd, uMsg, wParam, lParam);
//}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
	const wchar_t CLASS_NAME[] = L"Simple window";

	const wchar_t* main_window_name = L"main window";

	int main_window_pos_x = 500;
	int main_window_pos_y = 300;

	MainWindow main_window(main_window_name, main_window_pos_x, main_window_pos_y, 600, 500);

	if (!main_window.create(WS_OVERLAPPEDWINDOW)) { return 0; }

	main_window.show();

	FontWindow font_window(L"Font window", main_window_pos_x + 40, main_window_pos_y + 90, 400, 400);

	if (!font_window.create(WS_OVERLAPPEDWINDOW, 0, main_window.window_handler)) { return  0; }

	main_window.font_window = font_window;


	/*WNDCLASS window_class{};
	WindowInfo* window_info_ptr = new WindowInfo;

	window_class.lpfnWndProc = WindowProc;
	window_class.hInstance = hInstance;
	window_class.lpszClassName = CLASS_NAME;

	RegisterClass(&window_class);

	HWND window_handler = CreateWindowEx(0, CLASS_NAME, L"Simple Window", WS_OVERLAPPEDWINDOW, window_info_ptr->x, window_info_ptr->y, window_info_ptr->width, window_info_ptr->height, NULL, NULL, hInstance, window_info_ptr);

	if (window_handler == NULL) { return -1; }
	
	ShowWindow(window_handler, nCmdShow);*/

	MSG msg{};

	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	};

	return 0;
}

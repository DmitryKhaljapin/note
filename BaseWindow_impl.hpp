#pragma once
#include "BaseWindow.hpp"
#include "resource.h"

template<class DERIVED_CLASS>
BaseWindow<DERIVED_CLASS>::BaseWindow(): pos_x(0), pos_y(0), width(0), height(0) {}

template<class DERIVED_CLASS>
BaseWindow<DERIVED_CLASS>::BaseWindow(
	const wchar_t* window_name,
	int x,
	int y,
	int width,
	int height) : window_handler(NULL), window_name(window_name), pos_x(x), pos_y(y), width(width), height(height) { };

template<class DERIVED_CLASS>
LRESULT CALLBACK BaseWindow<DERIVED_CLASS>::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	
	DERIVED_CLASS* this_ptr = NULL;

	if (uMsg == WM_NCCREATE) {
		CREATESTRUCT* create_struct_ptr = reinterpret_cast<CREATESTRUCT*>(lParam);
		this_ptr = reinterpret_cast<DERIVED_CLASS*>(create_struct_ptr->lpCreateParams);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)this_ptr);

		this_ptr->window_handler = hwnd;
	}
	else {
		this_ptr = reinterpret_cast<DERIVED_CLASS*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	}
	if (this_ptr) {
		return this_ptr->handleMessage(uMsg, wParam, lParam);
	}
	else {
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

template<class DERIVED_CLASS>
BOOL BaseWindow<DERIVED_CLASS>::create(
	DWORD dwStyle, 
	DWORD dwExStyle, 
	HWND hwndParent,
	HMENU hMenu
) {
	WNDCLASS window_class{};

	window_class.lpfnWndProc = DERIVED_CLASS::WindowProc;
	window_class.hInstance = GetModuleHandle(NULL);
	window_class.lpszClassName = className();
	window_class.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));

	RegisterClass(&window_class);

	window_handler = CreateWindowEx(dwExStyle, className(), window_name, dwStyle, pos_x, pos_y, width, height, hwndParent, hMenu, GetModuleHandle(NULL), this);

	return (window_handler ? TRUE : FALSE);
}

template<class DERIVED_CLASS> 
HWND BaseWindow<DERIVED_CLASS>::getWindow() const {
	return window_handler;
}

template<class DERIVED_CLASS>
void BaseWindow<DERIVED_CLASS>::show() const {
	ShowWindow(window_handler, 10);
}

//template<class DERIVED_CLASS>
//int BaseWindow<DERIVED_CLASS>::getWidth() const {
//	return this->width;
//}
//
//template<class DERIVED_CLASS>
//int BaseWindow<DERIVED_CLASS>::getHeight() const {
//	return this->height;
//}
//
//template<class DERIVED_CLASS>
//int BaseWindow<DERIVED_CLASS>::getClientWidth() const {
//	return this->clien_width;
//}
//
//template<class DERIVED_CLASS>
//int BaseWindow<DERIVED_CLASS>::getClientHeight() const {
//	return this->client_height;
//}
//
//template<class DERIVED_CLASS>
//void BaseWindow<DERIVED_CLASS>::setWidth(int new_width) {
//	this->width = new_width;
//
//}
#pragma once
#include<windows.h>

template<class DERIVED_CLASS>
class BaseWindow {
	//private:
	//	int width;
	//	int height;
	//	int client_width;
	//	int client_height;
	protected:
	public:
		HWND window_handler;
		const wchar_t* window_name;
		int pos_x;
		int pos_y;
		int width;
		int height;
		//int getWidth() const;
		//void setWidth(int);

		//int getHeight() const;
		//void setHeight(int);

		//int getClientWidth() const;
		//int getClientHeight() const;

		static LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
		BaseWindow();
		BaseWindow(const wchar_t*, int, int, int, int);
		BOOL create(DWORD, DWORD dwExStyle = 0, HWND hWndParant = 0, HMENU hMenu = 0);
		HWND getWindow() const;
		void show() const;
	protected:
		virtual PCWSTR className() const = 0;
		virtual LRESULT handleMessage(UINT, WPARAM, LPARAM) = 0;

};

#include "BaseWindow_impl.hpp"
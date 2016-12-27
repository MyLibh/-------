#pragma once

#ifndef __WINDOW_HPP_INCLUDED__
#define __WINDOW_HPP_INCLUDED__

#include "stdafx.h"
#include "BaseWindow.hpp"

using WinApiWrapper::BaseWindow;
using WinApiWrapper::WindowRect;

namespace Billiards
{
	class Window : public BaseWindow, private UncopyableFull
	{
	private:
		WindowRect window_;

		LRESULT onCommand(UINT, WPARAM, LPARAM) override;

		static INT_PTR CALLBACK about(HWND, UINT, WPARAM, LPARAM);
		
		friend ATOM registerClass(LPCTSTR, HINSTANCE);

	public:
		Window(LPCTSTR, DWORD, DWORD, LPCTSTR, HINSTANCE, CONST WindowRect&);
		~Window() { }		

		inline CONST WindowRect __nothrow &getWindowRect() const { return window_; };
	};

	struct MainLoopParameters
	{
		static CONST SIZE_T MAX_LOADSTRING = 100;

		Window *pWindow;
		LPCTSTR className;
		LPCTSTR title;

		CONST Window __nothrow &getWindow() const { return *pWindow; };

		MainLoopParameters(HINSTANCE, CONST WindowRect&);
		~MainLoopParameters();

		VOID loadStrings(HINSTANCE);
	};
	
	typedef void MLFUNC;
	typedef MLFUNC (*LPMLFUNC)(CONST Window&);

	INT MainLoop(LPMLFUNC = nullptr, MainLoopParameters* = nullptr);
}

#endif
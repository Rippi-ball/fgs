#include <windows.h>
#include <tchar.h>
#include "menu.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
TCHAR WinName[] = _T("MainFrame");

char str[255];
int maxX, maxY;
int X = 10, Y = 10;
int orgX = 0, orgY = 0;

int WINAPI _tWinMain(HINSTANCE This, HINSTANCE Prev, LPTSTR, int mode) {

	HWND hWnd;
	MSG msg;
	WNDCLASS wc;
	HACCEL hAccel;

	wc.hInstance = This;
	wc.lpszClassName = WinName;
	wc.lpfnWndProc = WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszMenuName = _T("MYMENU");
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	if (!RegisterClass(&wc)) return 0;

	hWnd = CreateWindow(WinName,
		_T("лемч"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		HWND_DESKTOP,
		NULL,
		This,
		NULL);

	hAccel = LoadAccelerators(This, _T("ACS"));

	ShowWindow(hWnd, mode);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		if (!TranslateAccelerator(hWnd, hAccel, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rt;

	switch (message) {
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDM_UPPER:
			X += 10;
			Y += 10;
			InvalidateRect(hWnd, NULL, 1);
			break;

		case IDM_REDUCE:
			X -= 10;
			Y -= 10;
			InvalidateRect(hWnd, NULL, 1);
			break;

		case IDM_BOTTOM:
			orgY += 10;
			InvalidateRect(hWnd, NULL, 1);
			break;

		case IDM_TOP:
			orgY -= 10;
			InvalidateRect(hWnd, NULL, 1);
			break;

		case IDM_LEFT:
			orgX -= 10;
			InvalidateRect(hWnd, NULL, 1);
			break;

		case IDM_RIGHT:
			orgX += 10;
			InvalidateRect(hWnd, NULL, 1);
			break;
		}

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rt);
		SetMapMode(hdc, MM_ANISOTROPIC);
		SetWindowExtEx(hdc, 200, 200, NULL);
		SetViewportExtEx(hdc, X, Y, NULL);
		SetViewportOrgEx(hdc, orgX, orgY, NULL);
		Rectangle(hdc, 450, 10, 650, 150);
		EndPaint(hWnd, &ps);
		break;

	case WM_SIZE:
		InvalidateRect(hWnd, NULL, 1);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
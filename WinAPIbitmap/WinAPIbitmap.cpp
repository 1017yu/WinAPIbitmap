#include <windows.h>
#include "resource.h"
#include <iostream>

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HBITMAP hBmp;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstanc, LPSTR lpCmdLine, int nShowCmd)

{
	char szTitle[] = "My First Window Program";
	char szClass[] = "Class";

	// 1. Declare window class -----------------------------------------------------
	WNDCLASSEX WndEx;
	WndEx.style = NULL; // window style
	WndEx.lpfnWndProc = WndProc; //window procedure(function) pointer
	WndEx.cbClsExtra = 0; //additional memory size for widow class
	WndEx.cbWndExtra = 0; // additional memory size for window
	WndEx.hInstance = hInstance; // intance handle of the window procdeure
	WndEx.hIcon = LoadIcon(NULL, ""); //big icon
	WndEx.hIconSm = LoadIcon(hInstance, ""); //small icon
	WndEx.hCursor = LoadCursor(NULL, IDC_ARROW);//cursor
	WndEx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//background
	WndEx.lpszMenuName = NULL;//menui
	WndEx.lpszClassName = szClass;//window class name
	WndEx.cbSize = sizeof(WndEx); //size of window class structure

	// 2. Register window calss -----------------------------------------------------
	RegisterClassEx(&WndEx);

	// 3. Create window -------------------------------------------------------------
	HWND hWnd;
	hWnd = CreateWindowEx(NULL, szClass, szTitle,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		320 * 2, 240 * 2, NULL, NULL, hInstance, NULL);

	// 4. Show and Update window-----------------------------------------------------
	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);

	hBmp = LoadBitmap(hInstance, "IDB_BITMAP");

	// 5. Message loop --------------------------------------------------------------
	MSG mSg;
	while (TRUE)
	{
		if (PeekMessage(&mSg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (!GetMessage(&mSg, NULL, 0, 0))
				break;
			TranslateMessage(&mSg);
			DispatchMessage(&mSg);
		}
	}
	return mSg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hDC, hMemDC;
	char szText1[] = "First line of test text";
	char szText2[] = "Second line of test text";
	char szText3[] = "Third line of test text";
	char szTitle[] = "My New Window Title example";
	char szTextc[100];

	static HWND hButtBmp;
	static char a = 0;
	static int x = 100, y = 100;
	static int keyflag = 0;


	PAINTSTRUCT pS;


	switch (uMsg)
	{
	case WM_CREATE:
		hButtBmp = CreateWindow("BUTTON", "Load a Bmp FIle", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			10, 400, 150, 30, hWnd, (HMENU)1, NULL, NULL);
		return FALSE;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case 1:
			hDC = GetDC(hWnd);
			hMemDC = CreateCompatibleDC(hDC);
			SelectObject(hMemDC, hBmp);
			BitBlt(hDC, 0, 0, 400, 400, hMemDC, 0, 0, SRCCOPY);
			DeleteDC(hMemDC);
			ReleaseDC(hWnd, hDC);
			DeleteObject(hBmp);
			break;
		}
		return FALSE;
	case WM_DESTROY:
		PostQuitMessage(0);
		return FALSE;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
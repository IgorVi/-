#include <windows.h>
#include "resource.h"

#define LEFT_START 52
#define WIDTH  30
#define HEIGHT 30
#define Z      5
#define N      10

HWND h[N][N];
HINSTANCE hInst;
HBITMAP hBmp;

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	hInst = hInstance;
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;

	case WM_INITDIALOG:
	{
		hBmp = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP1));	
		TCHAR buf[3] = { 0 };
		for (int i = 0; i < N; ++i){
			for (int j = 0; j < N; ++j){
				wsprintf(buf, TEXT("%d"), i * N + j);
				h[i][j] = CreateWindowEx(WS_EX_DLGMODALFRAME, TEXT("BUTTON"), buf, WS_CHILD | WS_VISIBLE,
					j * (WIDTH + Z), i * (HEIGHT + Z), WIDTH, HEIGHT, hWnd, 0, hInst, 0);
			}
		}
		return TRUE;
	}
	case WM_COMMAND:
	{
		TCHAR buf[3] = { 0 };
		TCHAR text[3] = { 0 };
		HWND hW = GetFocus();
		GetWindowText(hW, text, 3);

		for (int i = 0; i < N; ++i){
			for (int j = 0; j < N; ++j){
				wsprintf(buf, TEXT("%d"), i * N + j);
				if (!lstrcmp(buf, text)) {
					if (IDOK == MessageBox(0, buf, text, MB_OK | MB_ICONINFORMATION)){
						SendMessage(h[i][j], WM_CLOSE, 0, 0);
						h[i][j] = CreateWindowEx(0, TEXT("Static"), TEXT("Some picture"),
							WS_CHILD | WS_VISIBLE | WS_BORDER | SS_BITMAP, j * (WIDTH + Z), i * (HEIGHT + Z), WIDTH, HEIGHT, hWnd, 0, GetModuleHandle(0), 0);
						SendMessage(h[i][j], STM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBmp));

					}
				}
			}
		}
	}
		return TRUE;
	}
	return FALSE;
}
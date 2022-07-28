#include "Graph Me.h"

void DrawDebug(HDC hdc, HDC hMemDC, INT mx, INT my, BOOL flg0, BOOL flg1, UINT ctrl_width, UINT width, UINT height)
{
	TCHAR str[64];

	SetFont(hMemDC, 0, 0x00000000, 0x00FFFFFF);
	SetTextAlign(hMemDC, TA_LEFT | TA_TOP);
	wsprintf(str, L"width: %d, height: %d", width, height);
	TextOut(hMemDC, ctrl_width + 10, 10, str, lstrlen(str));
	wsprintf(str, L"mouseX: %d, mouseY: %d", mx, my);
	TextOut(hMemDC, ctrl_width + 10, 30, str, lstrlen(str));
	wsprintf(str, L"cwidth: %d", ctrl_width);
	TextOut(hMemDC, ctrl_width + 10, 50, str, lstrlen(str));
	wsprintf(str, L"%s", flg0 ? L"TRUE" : L"FALSE");
	TextOut(hMemDC, ctrl_width + 10, 70, str, lstrlen(str));
	wsprintf(str, L"%s", flg1 ? L"TRUE" : L"FALSE");
	TextOut(hMemDC, ctrl_width + 10, 90, str, lstrlen(str));

	DeleteObject(SelectObject(hMemDC, GetStockObject(SYSTEM_FONT)));
}

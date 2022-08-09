#include "Draw.h"
#include "Button.h"
#include "Font.h"


void DrawDebug(HDC hdc, HDC hMemDC, INT mx, INT my)
{
	TCHAR str[256];
	TCHAR str2[128];
	size_t converted;

	SetFont(hMemDC, 0, 0x00FFFFFF, 0x00000000);
	SetTextAlign(hMemDC, TA_LEFT | TA_TOP);
	wsprintf(str, L"width: %d, height: %d", pane.width, pane.height);
	TextOut(hMemDC, pane.lWidth + 10, 10, str, lstrlen(str));
	wsprintf(str, L"mouseX: %d, mouseY: %d", mx, my);
	TextOut(hMemDC, pane.lWidth + 10, 30, str, lstrlen(str));
	wsprintf(str, L"ctrl_width: %d", pane.lWidth);
	TextOut(hMemDC, pane.lWidth + 10, 50, str, lstrlen(str));
	wsprintf(str, L"HOVER[0]: %s", buttons[0].mHover ? L"TRUE" : L"FALSE");
	TextOut(hMemDC, pane.lWidth + 10, 70, str, lstrlen(str));
	wsprintf(str, L"HOVER[1]: %s", buttons[1].mHover ? L"TRUE" : L"FALSE");
	TextOut(hMemDC, pane.lWidth + 10, 90, str, lstrlen(str));
	wsprintf(str, L"HOVER[2]: %s", buttons[2].mHover ? L"TRUE" : L"FALSE");
	TextOut(hMemDC, pane.lWidth + 10, 110, str, lstrlen(str));
	wsprintf(str, L"PROBLEM_DATA_SIZE: %d", problem_data_size);
	TextOut(hMemDC, pane.lWidth + 10, 130, str, lstrlen(str));
	mbstowcs_s(&converted, str2, sizeof(str2)/sizeof(str2[0]), problem_data, problem_data_size);
	wsprintf(str, L"PROBLEM_DATA: %s", str2);
	TextOut(hMemDC, pane.lWidth + 10, 170, str, lstrlen(str));

	DeleteObject(SelectObject(hMemDC, GetStockObject(SYSTEM_FONT)));
}

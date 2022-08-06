#include "Draw.h"
#include "Slider.h"

void DrawDebug(HDC hdc, HDC hMemDC, INT mx, INT my)
{
	TCHAR str[64];

	SetFont(hMemDC, 0, 0x00FFFFFF, 0x00000000);
	SetTextAlign(hMemDC, TA_LEFT | TA_TOP);
	wsprintf(str, L"width: %d, height: %d", pane.width, pane.height);
	TextOut(hMemDC, pane.lWidth + 10, 10, str, lstrlen(str));
	wsprintf(str, L"mouseX: %d, mouseY: %d", mx, my);
	TextOut(hMemDC, pane.lWidth + 10, 30, str, lstrlen(str));
	wsprintf(str, L"ctrl_width: %d", pane.lWidth);
	TextOut(hMemDC, pane.lWidth + 10, 50, str, lstrlen(str));
	//wsprintf(str, L"%s", pane.mHover ? L"TRUE" : L"FALSE");
	wsprintf(str, L"HOVER[0]: %s", sliders[0].mHover ? L"TRUE" : L"FALSE");
	TextOut(hMemDC, pane.lWidth + 10, 70, str, lstrlen(str));
	//wsprintf(str, L"%s", pane.mDrag ? L"TRUE" : L"FALSE");
	wsprintf(str, L"DRAG[0]: %s", sliders[0].mDrag ? L"TRUE" : L"FALSE");
	TextOut(hMemDC, pane.lWidth + 10, 90, str, lstrlen(str));
	swprintf(str, sizeof(str) / sizeof(str[0]), L"VALUE[0]: %.3Lf", sliders[0].value);
	TextOut(hMemDC, pane.lWidth + 10, 110, str, lstrlen(str));
	swprintf(str, sizeof(str) / sizeof(str[0]), L"VALUE[1]: %.3Lf", sliders[1].value);
	TextOut(hMemDC, pane.lWidth + 10, 130, str, lstrlen(str));
	swprintf(str, sizeof(str) / sizeof(str[0]), L"VALUE[2]: %.3Lf", sliders[2].value);
	TextOut(hMemDC, pane.lWidth + 10, 150, str, lstrlen(str));
	swprintf(str, sizeof(str) / sizeof(str[0]), L"VALUE[3]: %.3Lf", sliders[3].value);
	TextOut(hMemDC, pane.lWidth + 10, 170, str, lstrlen(str));

	DeleteObject(SelectObject(hMemDC, GetStockObject(SYSTEM_FONT)));
}

#include "Draw.h"
#include "Button.h"
#include "Font.h"


void DrawDebug(HDC hdc, HDC hMemDC, INT mx, INT my)
{
	static double t = 0;
	TCHAR str[256];
	TCHAR str2[128];

	SetFont(hMemDC, 0, 0x00FFFFFF, 0x00000000);
	SetTextAlign(hMemDC, TA_LEFT | TA_TOP);
	//(str, L"problem: %d, %d", problem_crnt, problem_temp);
	//TextOut(hMemDC, pane.lWidth + 10, 10, str, lstrlen(str));
	//wsprintf(str, L"mouseX: %d, mouseY: %d", mx, my);
	//TextOut(hMemDC, pane.lWidth + 10, 30, str, lstrlen(str));
	//wsprintf(str, L"ctrl_width: %d", pane.lWidth);
	//TextOut(hMemDC, pane.lWidth + 10, 50, str, lstrlen(str));
	//wsprintf(str, L"PROBLEM_DATA_SIZE: %d", problem_data_size);
	//TextOut(hMemDC, pane.lWidth + 10, 70, str, lstrlen(str));
	//mbstowcs_s(NULL, str2, sizeof(str2)/sizeof(str2[0]), problem_data, problem_data_size);
	//wsprintf(str, L"PROBLEM_DATA: %s", problem_data_arr[0]);
	//TextOut(hMemDC, pane.lWidth + 10, 10, str, lstrlen(str));
	//swprintf_s(str, sizeof(str)/sizeof(str[0]), L"PROBLEM_DATA: %8.6f", Ease(t = fmod(t + 0.1, 2), 0, 2, 1));
	//TextOut(hMemDC, pane.lWidth + 10, 110, str, lstrlen(str));

	DeleteObject(SelectObject(hMemDC, GetStockObject(SYSTEM_FONT)));
}

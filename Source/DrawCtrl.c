#include "Graph Me.h"

extern struct SLIDER sliders[4];

void DrawCtrl(HDC hdc, HDC hMemDC, INT mx, INT my, BOOL flg0, BOOL flg1, UINT ctrl_width, UINT width, UINT height)
{
    TCHAR str[8];

    SetTextAlign(hMemDC, TA_CENTER | TA_BOTTOM);

    // 上限, 下限
    SelectObject(hMemDC, CreateSolidBrush(0x00000000));
    for (int i = 0; i < 4; i++) {
        Rectangle(hMemDC, 10, i * 80 + 10, 50, i * 80 + 80);
        Rectangle(hMemDC, ctrl_width - 50, i * 80 + 10, ctrl_width - 10, i * 80 + 80);
    }
    SetFont(hMemDC, 30, 0x000000FF, 0x00000000);
    for (int i = 0; i < 4; i++) {
        wsprintf(str, L"%d", sliders[i].min);
        TextOut(hMemDC, 30, i * 80 + 50 + 10, str, lstrlen(str));
        wsprintf(str, L"%d", sliders[i].max);
        TextOut(hMemDC, ctrl_width - 30, i * 80 + 50 + 10, str, lstrlen(str));
    }

    // スライダー
    SelectObject(hMemDC, CreatePen(PS_SOLID | PS_ENDCAP_ROUND, 5, 0x00606060));
    for (int i = 0; i < 4; i++) {
        MoveToEx(hMemDC, 60, i * 80 + 45, NULL);
        LineTo(hMemDC, ctrl_width - 60, i * 80 + 45);
    }
    DeleteObject(SelectObject(hMemDC, CreatePen(PS_SOLID, 0, 0x00)));
    //DeleteObject(SelectObject(hMemDC, CreateSolidBrush(0x0080FF80)));
    DeleteObject(SetFont(hMemDC, 22, 0x00000000, 0x0080FF80));
    for (int i = 0; i < 4; i++) {
        int x = GetProportion(sliders[i]) * (ctrl_width - 120) + 60;
        int y = i * 80 + 45;
        DeleteObject(SelectObject(hMemDC, CreateGradientBrushV(0x90FF90, 0x30B030, hMemDC, ctrl_width, height, y - 20, 40)));
        RoundRect(hMemDC, x - 10, y - 20, x + 10, y + 20, 10, 15);
        wsprintf(str, L"%c", 'a' + i);
        TextOut(hMemDC, x, y + 10, str, 1);
    }

    // PREV, RESET, NEXTボタン
    //DeleteObject(SelectObject(hMemDC, CreateSolidBrush(0x0080FF80)));
    DeleteObject(SelectObject(hMemDC, CreateGradientBrushV(0x90FF90, 0x20B020, hMemDC, ctrl_width, height, height - 50, 40)));
    DeleteObject(SetFont(hMemDC, 22, 0x00000000, 0x0080FF80));
    for (int i = 0; i < 3; i++) {
        Rectangle(hMemDC, ctrl_width / 3 * i + 10, height - 50, ctrl_width / 3 * (i + 1) - 10, height - 10);
        wsprintf(str, L"%s", i==0 ? L"PREV" : i==1 ? L"RESET" : L"NEXT");
        TextOut(hMemDC, ctrl_width / 3 * (i+0.5), height - 20, str, lstrlen(str));
    }

    DeleteObject(SelectObject(hMemDC, GetStockObject(WHITE_BRUSH)));
    DeleteObject(SelectObject(hMemDC, GetStockObject(BLACK_PEN)));
    DeleteObject(SelectObject(hMemDC, GetStockObject(SYSTEM_FONT)));
}
#include "Draw.h"
#include "Slider.h"
#include "Button.h"

void DrawCtrl(HDC hdc, HDC hMemDC, INT mx, INT my)
{
    TCHAR str[8];

    SetTextAlign(hMemDC, TA_CENTER | TA_BOTTOM);

    // 上限, 下限
    SelectObject(hMemDC, CreateSolidBrush(0x00000000));
    for (INT i = 0; i < 4; i++) {
        Rectangle(hMemDC, 10, i * 80 + 10, 50, i * 80 + 80);
        Rectangle(hMemDC, pane.lWidth - 50, i * 80 + 10, pane.lWidth - 10, i * 80 + 80);
    }
    SetFont(hMemDC, 30, 0x000000FF, 0x00000000);
    for (INT i = 0; i < 4; i++) {
        wsprintf(str, L"%d", sliders[i].min);
        TextOut(hMemDC, 30, i * 80 + 50 + 10, str, lstrlen(str));
        wsprintf(str, L"%d", sliders[i].max);
        TextOut(hMemDC, pane.lWidth - 30, i * 80 + 50 + 10, str, lstrlen(str));
    }

    // スライダー背景
    SelectObject(hMemDC, CreatePen(PS_SOLID | PS_ENDCAP_ROUND, 5, 0x00606060));
    for (INT i = 0; i < 4; i++) {
        MoveToEx(hMemDC, pane.lWidth / 2 - sliders[i].length / 2, i * 80 + 45, NULL);
        LineTo(hMemDC, pane.lWidth / 2 + sliders[i].length / 2, i * 80 + 45);
    }
    // スライダー本体
    DeleteObject(SelectObject(hMemDC, CreatePen(PS_SOLID, 0, 0x00)));
    //DeleteObject(SelectObject(hMemDC, CreateSolidBrush(0x0080FF80)));
    DeleteObject(SetFont(hMemDC, 22, 0x00000000, 0x0080FF80));
    for (INT i = 0; i < 4; i++) {
        INT x = GetProportion(&sliders[i]) * sliders[i].length + pane.lWidth / 2.0 - sliders[i].length / 2.0;
        INT y = i * 80 + 45;
        DeleteObject(SelectObject(hMemDC, CreateGradientBrushV(0x90FF90, 0x30B030, hMemDC, pane.lWidth, pane.height, y - 20, 40)));
        RoundRect(hMemDC, x - 10, y - 20, x + 10, y + 20, 10, 15);
        wsprintf(str, L"%c", 'a' + i);
        TextOut(hMemDC, x, y + 10, str, 1);
    }

    // PREV, RESET, NEXTボタン
    //DeleteObject(SelectObject(hMemDC, CreateSolidBrush(0x0080FF80)));
    DeleteObject(SelectObject(hMemDC, CreateGradientBrushV(0x90FF90, 0x20B020, hMemDC, pane.lWidth, pane.height, pane.height - 50, 40)));
    DeleteObject(SetFont(hMemDC, 22, 0x00000000, 0x0080FF80));
    for (INT i = 0; i < 3; i++) {
        Rectangle(
            hMemDC,
            pane.lWidth / 6.0 * (i * 2 + 1) - buttons[i].width / 2.0,
            pane.height - 30 - buttons[i].height / 2.0,
            pane.lWidth / 6.0 * (i * 2 + 1) + buttons[i].width / 2.0,
            pane.height - 30 + buttons[i].height / 2.0
        );
        wsprintf(str, L"%s", i==0 ? L"PREV" : i==1 ? L"RESET" : L"NEXT");
        TextOut(hMemDC, pane.lWidth / 3 * (i * 2 + 1) / 2, pane.height - 20, str, lstrlen(str));
    }

    DeleteObject(SelectObject(hMemDC, GetStockObject(WHITE_BRUSH)));
    DeleteObject(SelectObject(hMemDC, GetStockObject(BLACK_PEN)));
    DeleteObject(SelectObject(hMemDC, GetStockObject(SYSTEM_FONT)));
}
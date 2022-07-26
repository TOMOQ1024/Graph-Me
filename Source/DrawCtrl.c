#include "Draw.h"
#include "Slider.h"
#include "Button.h"
#include "Font.h"
#include "Gradient.h"

void DrawCtrl(HDC hdc, HDC hMemDC)
{
    TCHAR str[8];
    RECT rc;

    SetTextAlign(hMemDC, TA_CENTER | TA_BOTTOM);

    // 上限, 下限
    SelectObject(hMemDC, CreateSolidBrush(0x00000000));
    for (INT i = 0; i < 4; i++) {
        Rectangle(hMemDC, 10, i * 80 + 10, 50, i * 80 + 80);
        Rectangle(hMemDC, pane.lWidth - 50, i * 80 + 10, pane.lWidth - 10, i * 80 + 80);
    }
    SetFont(hMemDC, 30, 0x000000FF, 0x00000000);
    for (INT i = 0; i < 4; i++) {
        wsprintf(str, L"%s", sliders[i].min_s);
        TextOut(hMemDC, 30, i * 80 + 50 + 10, str, lstrlen(str));
        wsprintf(str, L"%s", sliders[i].max_s);
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
        //INT x = GetProportion(&sliders[i]) * sliders[i].length + pane.lWidth / 2.0 - sliders[i].length / 2.0;
        //INT y = i * 80 + 45;
        GetSliderRect(&sliders[i], &rc);
        DeleteObject(SelectObject(hMemDC, CreateGradientBrushV(
            sliders[i].active ? 0x90FF90 : 0x909090,
            sliders[i].active ? 0x30B030 : 0x505050,
            hMemDC, pane.lWidth, pane.height, rc.top, sliders[i].height
        )));
        RoundRect(hMemDC, rc.left, rc.top, rc.right, rc.bottom, 10, 15);
        wsprintf(str, L"%c", 'a' + i);
        TextOut(hMemDC, (rc.left + rc.right) / 2, (rc.top + rc.bottom) / 2+10, str, 1);
    }

    // PREV, RESET, NEXTボタン
    //DeleteObject(SelectObject(hMemDC, CreateSolidBrush(0x0080FF80)));
    DeleteObject(SetFont(hMemDC, 22, 0x00000000, 0x0080FF80));
    for (INT i = 0; i < 3; i++) {
        GetButtonRect(&buttons[i], &rc);
        DeleteObject(SelectObject(hMemDC, CreateGradientBrushV(
            buttons[i].active ? 0x90FF90 : 0x909090,
            buttons[i].active ? 0x20B020 : 0x404040,
            hMemDC, pane.lWidth, pane.height, pane.height - 50, 40
        )));
        Rectangle(hMemDC, rc.left, rc.top, rc.right, rc.bottom);
        wsprintf(str, L"%s", i==0 ? L"PREV" : i==1 ? L"RESET" : L"NEXT");
        TextOut(hMemDC, pane.lWidth / 3 * (i * 2 + 1) / 2, pane.height - 20, str, lstrlen(str));
    }

    DeleteObject(SelectObject(hMemDC, GetStockObject(WHITE_BRUSH)));
    DeleteObject(SelectObject(hMemDC, GetStockObject(BLACK_PEN)));
    DeleteObject(SelectObject(hMemDC, GetStockObject(SYSTEM_FONT)));
}
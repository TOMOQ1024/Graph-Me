#include "Graph Me.h"

void DrawCtrl(HDC hdc, HDC hMemDC, INT mx, INT my, BOOL flg0, BOOL flg1, UINT ctrl_width, UINT width, UINT height)
{
    SelectObject(hMemDC, CreateSolidBrush(0x00000000));
    Rectangle(hMemDC, 0, 0, width, height);
    SelectObject(hMemDC, CreateSolidBrush(0x00FFFFFF));
    Rectangle(hMemDC, 0, 0, ctrl_width, height);

    TCHAR str[128];
    wsprintf(str, L"width: %d, height: %d", width, height);
    TextOut(hMemDC, 10, 10, str, lstrlen(str));
    wsprintf(str, L"mouseX: %d, mouseY: %d", mx, my);
    TextOut(hMemDC, 10, 30, str, lstrlen(str));
    wsprintf(str, L"cwidth: %d", ctrl_width);
    TextOut(hMemDC, 10, 50, str, lstrlen(str));
    wsprintf(str, L"%s", flg0 ? L"TRUE" : L"FALSE");
    TextOut(hMemDC, 10, 70, str, lstrlen(str));
    wsprintf(str, L"%s", flg1 ? L"TRUE" : L"FALSE");
    TextOut(hMemDC, 10, 90, str, lstrlen(str));

    BitBlt(hdc, 0, 0, width, height, hMemDC, 0, 0, SRCCOPY);
}
#include "Graph Me.h"

void Draw(HDC hdc, HDC hMemDC, INT mx, INT my, BOOL flg0, BOOL flg1, UINT ctrl_width, UINT width, UINT height)
{
	// 背景
	SelectObject(hMemDC, CreateSolidBrush(0x00000000));
	Rectangle(hMemDC, 0, 0, width, height);
	SelectObject(hMemDC, CreateSolidBrush(0x00FFFFFF));
	Rectangle(hMemDC, 0, 0, ctrl_width, height);

	// コントロール
	DrawCtrl(hdc, hMemDC, mx, my, flg0, flg1, ctrl_width, width, height);

	// デバッグ情報
	DrawDebug(hdc, hMemDC, mx, my, flg0, flg1, ctrl_width, width, height);

	BitBlt(hdc, 0, 0, width, height, hMemDC, 0, 0, SRCCOPY);
}
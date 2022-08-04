#include "Graph Me.h"

void Draw(HDC hdc, HDC hMemDC, INT mx, INT my, BOOL flg0, BOOL flg1, UINT ctrl_width, UINT width, UINT height)
{
	// �e�L�X�g�̔w�i�F���Ȃ���
	SetBkMode(hMemDC, TRANSPARENT);
	
	// �w�i
	SelectObject(hMemDC, GetStockObject(NULL_PEN));

	SelectObject(hMemDC, CreateSolidBrush(0x00000000));
	Rectangle(hMemDC, 0, 0, width, height);

	DeleteObject(SelectObject(
		hMemDC,
		CreateGradientBrushH(0xA0A0A0, 0xD0D0D0, hMemDC, ctrl_width, height, 0, ctrl_width * 3 / 4 + 1)
	));
	Rectangle(hMemDC, 0, 0, ctrl_width * 3 / 4 + 1, height);
	DeleteObject(SelectObject(
		hMemDC,
		CreateGradientBrushH(0xD0D0D0, 0xB0B0B0, hMemDC, ctrl_width, height, ctrl_width * 3 / 4, ctrl_width / 4)
	));
	Rectangle(hMemDC, ctrl_width * 3 / 4, 0, ctrl_width, height);

	DeleteObject(SelectObject(hMemDC, GetStockObject(BLACK_BRUSH)));

	// �R���g���[��
	DrawCtrl(hdc, hMemDC, mx, my, flg0, flg1, ctrl_width, width, height);

	// �f�o�b�O���
	DrawDebug(hdc, hMemDC, mx, my, flg0, flg1, ctrl_width, width, height);

	BitBlt(hdc, 0, 0, width, height, hMemDC, 0, 0, SRCCOPY);
}
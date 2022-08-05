#include "Graph Me.h"

void Draw(HDC hdc, HDC hMemDC, INT mx, INT my, UINT width, UINT height)
{
	// �e�L�X�g�̔w�i�F���Ȃ���
	SetBkMode(hMemDC, TRANSPARENT);
	
	// �w�i
	SelectObject(hMemDC, GetStockObject(NULL_PEN));

	SelectObject(hMemDC, CreateSolidBrush(0x00000000));
	Rectangle(hMemDC, 0, 0, width, height);

	DeleteObject(SelectObject(
		hMemDC,
		CreateGradientBrushH(0xA0A0A0, 0xD0D0D0, hMemDC, ctrl_pane.lWidth, height, 0, ctrl_pane.lWidth * 3 / 4 + 1)
	));
	Rectangle(hMemDC, 0, 0, ctrl_pane.lWidth * 3 / 4 + 1, height);
	DeleteObject(SelectObject(
		hMemDC,
		CreateGradientBrushH(0xD0D0D0, 0xB0B0B0, hMemDC, ctrl_pane.lWidth, height, ctrl_pane.lWidth * 3 / 4, ctrl_pane.lWidth / 4)
	));
	Rectangle(hMemDC, ctrl_pane.lWidth * 3 / 4, 0, ctrl_pane.lWidth, height);

	DeleteObject(SelectObject(hMemDC, GetStockObject(BLACK_BRUSH)));

	// �R���g���[��
	DrawCtrl(hdc, hMemDC, mx, my, width, height);

	// �f�o�b�O���
	DrawDebug(hdc, hMemDC, mx, my, width, height);

	BitBlt(hdc, 0, 0, width, height, hMemDC, 0, 0, SRCCOPY);
}
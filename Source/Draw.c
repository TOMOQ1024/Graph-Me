#include "Draw.h"
#include "Gradient.h"

void Draw(HDC hdc, HDC hMemDC, INT mx, INT my)
{
	// �e�L�X�g�̔w�i�F���Ȃ���
	SetBkMode(hMemDC, TRANSPARENT);
	
	// �w�i
	SelectObject(hMemDC, GetStockObject(NULL_PEN));

	SelectObject(hMemDC, CreateSolidBrush(0x00000000));
	Rectangle(hMemDC, 0, 0, pane.width, pane.height);

	DeleteObject(SelectObject(
		hMemDC,
		CreateGradientBrushH(0xA0A0A0, 0xD0D0D0, hMemDC, pane.lWidth, pane.height, 0, pane.lWidth * 3 / 4 + 1)
	));
	Rectangle(hMemDC, 0, 0, pane.lWidth * 3 / 4 + 1, pane.height);
	DeleteObject(SelectObject(
		hMemDC,
		CreateGradientBrushH(0xD0D0D0, 0xB0B0B0, hMemDC, pane.lWidth, pane.height, pane.lWidth * 3 / 4, pane.lWidth / 4)
	));
	Rectangle(hMemDC, pane.lWidth * 3 / 4, 0, pane.lWidth, pane.height);

	DeleteObject(SelectObject(hMemDC, GetStockObject(BLACK_BRUSH)));

	// �R���g���[��
	DrawCtrl(hdc, hMemDC, mx, my);

	// �f�o�b�O���
	DrawDebug(hdc, hMemDC, mx, my);

	BitBlt(hdc, 0, 0, pane.width, pane.height, hMemDC, 0, 0, SRCCOPY);
}
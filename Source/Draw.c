#include "Graph Me.h"

void Draw(HDC hdc, HDC hMemDC, INT mx, INT my, BOOL flg0, BOOL flg1, UINT ctrl_width, UINT width, UINT height)
{
	// �e�L�X�g�̔w�i�F���Ȃ���
	SetBkMode(hMemDC, TRANSPARENT);
	
	// �w�i
	SelectObject(hMemDC, CreateSolidBrush(0x00000000));
	Rectangle(hMemDC, 0, 0, width, height);
	DeleteObject(SelectObject(hMemDC, CreateSolidBrush(0x00FFFFFF)));
	//DeleteObject(SelectObject(hMemDC, CreateGradientBrush(0xC0C0C0, 0x404040, hMemDC, ctrl_width, height, 0, 0, ctrl_width, 80)));
	Rectangle(hMemDC, 0, 0, ctrl_width, height);
	DeleteObject(SelectObject(hMemDC, GetStockObject(BLACK_BRUSH)));

	// �R���g���[��
	DrawCtrl(hdc, hMemDC, mx, my, flg0, flg1, ctrl_width, width, height);

	// �f�o�b�O���
	DrawDebug(hdc, hMemDC, mx, my, flg0, flg1, ctrl_width, width, height);

	BitBlt(hdc, 0, 0, width, height, hMemDC, 0, 0, SRCCOPY);
}
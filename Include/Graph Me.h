#pragma once

#include "framework.h"
#include "resource.h"

struct SLIDER {
	INT min;
	INT max;
	double value;
};

struct SLIDER sliders[4];

void SetSliders();

double GetProportion(struct SLIDER slider);

HFONT SetFont(HDC hdc, INT nHeight, COLORREF textColor, COLORREF bkColor);

// �O���f�[�V�����t���u���V�̍쐬
HBRUSH CreateGradientBrushV(COLORREF top, COLORREF bottom, HDC hdc, int dcWidth, int dcHeight, int y0, int height);
HBRUSH CreateGradientBrushH(COLORREF top, COLORREF bottom, HDC hdc, int dcWidth, int dcHeight, int x0, int width);

// �S�Ă̕`��
void Draw(HDC hdc, HDC hMemDC, INT mx, INT my, BOOL flg0, BOOL flg1, UINT ctrl_width, UINT width, UINT height);

// �R���g���[���̕`��
void DrawCtrl(HDC hdc, HDC hMemDC, INT mx, INT my, BOOL flg0, BOOL flg1, UINT ctrl_width, UINT width, UINT height);

// �f�o�b�O���̕`��
void DrawDebug(HDC hdc, HDC hMemDC, INT mx, INT my, BOOL flg0, BOOL flg1, UINT ctrl_width, UINT width, UINT height);


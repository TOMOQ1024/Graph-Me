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

void SetFont(HDC hdc, INT nHeight, COLORREF textColor, COLORREF bkColor);

// �S�Ă̕`��
void Draw(HDC hdc, HDC hMemDC, INT mx, INT my, BOOL flg0, BOOL flg1, UINT ctrl_width, UINT width, UINT height);

// �R���g���[���̕`��
void DrawCtrl(HDC hdc, HDC hMemDC, INT mx, INT my, BOOL flg0, BOOL flg1, UINT ctrl_width, UINT width, UINT height);

// �f�o�b�O���̕`��
void DrawDebug(HDC hdc, HDC hMemDC, INT mx, INT my, BOOL flg0, BOOL flg1, UINT ctrl_width, UINT width, UINT height);

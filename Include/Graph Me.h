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

// グラデーション付きブラシの作成
HBRUSH CreateGradientBrushV(COLORREF top, COLORREF bottom, HDC hdc, int dcWidth, int dcHeight, int y0, int height);
HBRUSH CreateGradientBrushH(COLORREF top, COLORREF bottom, HDC hdc, int dcWidth, int dcHeight, int x0, int width);

// 全ての描画
void Draw(HDC hdc, HDC hMemDC, INT mx, INT my, BOOL flg0, BOOL flg1, UINT ctrl_width, UINT width, UINT height);

// コントロールの描画
void DrawCtrl(HDC hdc, HDC hMemDC, INT mx, INT my, BOOL flg0, BOOL flg1, UINT ctrl_width, UINT width, UINT height);

// デバッグ情報の描画
void DrawDebug(HDC hdc, HDC hMemDC, INT mx, INT my, BOOL flg0, BOOL flg1, UINT ctrl_width, UINT width, UINT height);


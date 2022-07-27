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

// 全ての描画
void Draw(HDC hdc, HDC hMemDC, INT mx, INT my, BOOL flg0, BOOL flg1, UINT ctrl_width, UINT width, UINT height);

// コントロールの描画
void DrawCtrl(HDC hdc, HDC hMemDC, INT mx, INT my, BOOL flg0, BOOL flg1, UINT ctrl_width, UINT width, UINT height);

// デバッグ情報の描画
void DrawDebug(HDC hdc, HDC hMemDC, INT mx, INT my, BOOL flg0, BOOL flg1, UINT ctrl_width, UINT width, UINT height);

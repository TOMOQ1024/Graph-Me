#pragma once

#include "framework.h"
#include "resource.h"

/******** 構造体, グローバル変数定義 ********/
// ペイン構造体
typedef struct tagPANE {
	INT lWidth;
	BOOL mHover;
	BOOL mDrag;
} PANE;
PANE ctrl_pane;
// スライダー構造体
typedef struct tagSLIDER {
	INT id;
	INT min;
	INT max;
	double value;
	double scale;
	BOOL mHover;
	BOOL mDrag;
	INT length;
} SLIDER;
// a, b, c, d のスライダー
SLIDER sliders[4];

double median(double x, double y, double z);




/******** コントロール ********/
// スライダー初期化???????????????????????????????????????????????????????????????
void SetSliders();

// スライダーの現在位置(0...1)
double GetProportion(const SLIDER* slider);

// スライダーの存在する矩形の取得
void GetSliderRect(const SLIDER* slider, RECT *rect);

// 矩形内に (x,y) が存在するか
BOOL IsIn(INT x, INT y, const RECT rc);




/******** マウスイベント ********/
void OnMouseMove(INT x, INT y);
void OnLButtonDown(INT x, INT y);
void OnLButtonUp(INT x, INT y);
void OnMouseMove_Slider(INT x, INT y);
void OnLButtonDown_Slider(INT x, INT y);
void OnLButtonUp_Slider(INT x, INT y);




/******** 描画 ********/
// フォントの設定, 戻り値は直前のフォントハンドル
HFONT SetFont(HDC hdc, INT nHeight, COLORREF textColor, COLORREF bkColor);

// グラデーション付きブラシの作成
HBRUSH CreateGradientBrushV(COLORREF top, COLORREF bottom, HDC hdc, int dcWidth, int dcHeight, int y0, int height);
HBRUSH CreateGradientBrushH(COLORREF top, COLORREF bottom, HDC hdc, int dcWidth, int dcHeight, int x0, int width);

// 全ての描画
void Draw(HDC hdc, HDC hMemDC, INT mx, INT my, UINT width, UINT height);

// コントロールの描画
void DrawCtrl(HDC hdc, HDC hMemDC, INT mx, INT my, UINT width, UINT height);

// デバッグ情報の描画
void DrawDebug(HDC hdc, HDC hMemDC, INT mx, INT my, UINT width, UINT height);


#pragma once

#include "Main.h"
#include "Problem.h"

// スライダー構造体
typedef struct tagSLIDER {
	INT id;
	BOOL active;
	INT min;
	INT max;
	double value;
	double scale;
	BOOL mHover;
	BOOL mDrag;
	INT length;
	INT width;
	INT height;
} SLIDER;
// a, b, c, d のスライダー
SLIDER sliders[4];



// スライダー初期化
void InitSliders(void);

// スライダーの設定
void SetSliders(const PROBLEM* p);

// スライダーの現在位置(0...1)
double GetProportion(const SLIDER* slider);

// スライダーの存在する矩形の取得
void GetSliderRect(const SLIDER* slider, RECT* rect);


void OnMouseMove_Slider(INT x, INT y);
void OnLButtonDown_Slider(INT x, INT y);
void OnLButtonUp_Slider(INT x, INT y);

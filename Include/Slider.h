#pragma once

#include "Main.h"



// スライダー初期化
void InitSliders(void);

// スライダーの現在位置(0...1)
double GetProportion(const SLIDER* slider);

// スライダーの存在する矩形の取得
void GetSliderRect(const SLIDER* slider, RECT* rect);


void OnMouseMove_Slider(INT x, INT y);
void OnLButtonDown_Slider(INT x, INT y);
void OnLButtonUp_Slider(INT x, INT y);

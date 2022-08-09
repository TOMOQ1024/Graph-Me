#pragma once

#include "Main.h"



// ボタン構造体
typedef struct tagBUTTON {
	INT id;
	BOOL active;
	BOOL mHover;
	BOOL mLDown;
	INT width;
	INT height;
} BUTTON;
// PREV, RESET, NEXT
BUTTON buttons[3];



// ボタン初期化
void InitButtons(void);

// ボタンの存在する矩形の取得
void GetButtonRect(const BUTTON* button, RECT* rect);

void OnMouseMove_Button(INT x, INT y);
void OnLButtonDown_Button(INT x, INT y);
void OnLButtonUp_Button(INT x, INT y);


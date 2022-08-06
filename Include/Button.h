#pragma once

#include "Main.h"



// �{�^���\����
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



// �{�^��������
void InitButtons(void);

// �{�^���̑��݂����`�̎擾
void GetButtonRect(const BUTTON* button, RECT* rect);

void OnMouseMove_Slider(INT x, INT y);
void OnLButtonDown_Slider(INT x, INT y);
void OnLButtonUp_Slider(INT x, INT y);


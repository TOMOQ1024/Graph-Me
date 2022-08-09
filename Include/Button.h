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

void OnMouseMove_Button(INT x, INT y);
void OnLButtonDown_Button(INT x, INT y);
void OnLButtonUp_Button(INT x, INT y);


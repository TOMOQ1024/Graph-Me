#pragma once

#include "Main.h"



// �{�^��������
void InitButtons(void);

// �{�^���̑��݂����`�̎擾
void GetButtonRect(const BUTTON* button, RECT* rect);

void OnMouseMove_Button(INT x, INT y);
void OnLButtonDown_Button(INT x, INT y);
void OnLButtonUp_Button(INT x, INT y);


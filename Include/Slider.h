#pragma once

#include "Main.h"



// �X���C�_�[������
void InitSliders(void);

// �X���C�_�[�̌��݈ʒu(0...1)
double GetProportion(const SLIDER* slider);

// �X���C�_�[�̑��݂����`�̎擾
void GetSliderRect(const SLIDER* slider, RECT* rect);


void OnMouseMove_Slider(INT x, INT y);
void OnLButtonDown_Slider(INT x, INT y);
void OnLButtonUp_Slider(INT x, INT y);

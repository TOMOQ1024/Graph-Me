#pragma once

#include "Main.h"
#include "Problem.h"

// �X���C�_�[�\����
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
// a, b, c, d �̃X���C�_�[
SLIDER sliders[4];



// �X���C�_�[������
void InitSliders(void);

// �X���C�_�[�̐ݒ�
void SetSliders(const PROBLEM* p);

// �X���C�_�[�̌��݈ʒu(0...1)
double GetProportion(const SLIDER* slider);

// �X���C�_�[�̑��݂����`�̎擾
void GetSliderRect(const SLIDER* slider, RECT* rect);


void OnMouseMove_Slider(INT x, INT y);
void OnLButtonDown_Slider(INT x, INT y);
void OnLButtonUp_Slider(INT x, INT y);

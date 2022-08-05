#pragma once

#include "framework.h"
#include "resource.h"

/******** �\����, �O���[�o���ϐ���` ********/
// �y�C���\����
typedef struct tagPANE {
	INT lWidth;
	BOOL mHover;
	BOOL mDrag;
} PANE;
PANE ctrl_pane;
// �X���C�_�[�\����
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
// a, b, c, d �̃X���C�_�[
SLIDER sliders[4];

double median(double x, double y, double z);




/******** �R���g���[�� ********/
// �X���C�_�[������???????????????????????????????????????????????????????????????
void SetSliders();

// �X���C�_�[�̌��݈ʒu(0...1)
double GetProportion(const SLIDER* slider);

// �X���C�_�[�̑��݂����`�̎擾
void GetSliderRect(const SLIDER* slider, RECT *rect);

// ��`���� (x,y) �����݂��邩
BOOL IsIn(INT x, INT y, const RECT rc);




/******** �}�E�X�C�x���g ********/
void OnMouseMove(INT x, INT y);
void OnLButtonDown(INT x, INT y);
void OnLButtonUp(INT x, INT y);
void OnMouseMove_Slider(INT x, INT y);
void OnLButtonDown_Slider(INT x, INT y);
void OnLButtonUp_Slider(INT x, INT y);




/******** �`�� ********/
// �t�H���g�̐ݒ�, �߂�l�͒��O�̃t�H���g�n���h��
HFONT SetFont(HDC hdc, INT nHeight, COLORREF textColor, COLORREF bkColor);

// �O���f�[�V�����t���u���V�̍쐬
HBRUSH CreateGradientBrushV(COLORREF top, COLORREF bottom, HDC hdc, int dcWidth, int dcHeight, int y0, int height);
HBRUSH CreateGradientBrushH(COLORREF top, COLORREF bottom, HDC hdc, int dcWidth, int dcHeight, int x0, int width);

// �S�Ă̕`��
void Draw(HDC hdc, HDC hMemDC, INT mx, INT my, UINT width, UINT height);

// �R���g���[���̕`��
void DrawCtrl(HDC hdc, HDC hMemDC, INT mx, INT my, UINT width, UINT height);

// �f�o�b�O���̕`��
void DrawDebug(HDC hdc, HDC hMemDC, INT mx, INT my, UINT width, UINT height);


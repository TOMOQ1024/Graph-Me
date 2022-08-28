#pragma once

#include "Main.h"



// �R���g���[���̕`��
void DrawCtrl(HDC hdc, HDC hMemDC, INT mx, INT my);





// ����
void Segment(HDC hdc, double x0, double y0, double x1, double y1);
// �^�C�g���p�Z�O�����g
void tSegment(HDC hdc, double x0, double y0, double X0, double Y0, double X1, double Y1);
// �A�j���[�V�����t������
void mtSegment(
	HDC hdc, double t, double x0, double y0, INT xf0, INT yf0, INT xt0, INT yt0,
	INT xf1, INT yf1, INT xt1, INT yt1, INT xf2, INT yf2, INT xt2, INT yt2
);
// �X�e�[�W�E���x�����ڗp��`
void sRectangle(HDC hdc, double xc, double yc, double w, double h);
// �X�e�[�W���ڗp�Z�O�����g
void sSegment(HDC hdc, double xo, double yo, double d, INT x0, INT y0, INT x1, INT y1);



//
void Curve(double p_arr[][2], INT* p_size, double a, double b, double c, double d, double x0, double y0, double x1, double y1);
// ��,�O���t,�����̕`��
void DrawMain(HDC hdc, HDC hMemDC);
void DrawAxis(HDC hdc, HDC hMemDC);
void DrawGraph(HDC hdc, HDC hMemDC);
void DrawExpression(HDC hdc, HDC hMemDC);

// �f�o�b�O���̕`��
void DrawDebug(HDC hdc, HDC hMemDC, INT mx, INT my);

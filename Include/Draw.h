#pragma once

#include "Main.h"

// �S�Ă̕`��
void Draw(HDC hdc, HDC hMemDC, INT mx, INT my);

// �R���g���[���̕`��
void DrawCtrl(HDC hdc, HDC hMemDC, INT mx, INT my);

// ����
void Segment(HDC hdc, double x0, double y0, double x1, double y1);
// �e�L�X�g�p�Z�O�����g
void tSegment(HDC hdc, double x0, double y0, double X0, double Y0, double X1, double Y1);
// �A�j���[�V�����t������
void mtSegment(
	HDC hdc, double t, double x0, double y0, INT xf0, INT yf0, INT xt0, INT yt0,
	INT xf1, INT yf1, INT xt1, INT yt1, INT xf2, INT yf2, INT xt2, INT yt2
);

// ��,�O���t,�����̕`��
void DrawMain(HDC hdc, HDC hMemDC);
void DrawAxis(HDC hdc, HDC hMemDC);
void DrawGraph(HDC hdc, HDC hMemDC);
void DrawExpression(HDC hdc, HDC hMemDC);

// �f�o�b�O���̕`��
void DrawDebug(HDC hdc, HDC hMemDC, INT mx, INT my);

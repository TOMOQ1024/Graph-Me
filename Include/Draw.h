#pragma once

#include "Main.h"

// �S�Ă̕`��
void Draw(HDC hdc, HDC hMemDC, INT mx, INT my);

// �R���g���[���̕`��
void DrawCtrl(HDC hdc, HDC hMemDC, INT mx, INT my);

// ��,�O���t,�����̕`��
void Segment(HDC hdc, double x0, double y0, double x1, double y1);
void DrawMain(HDC hdc, HDC hMemDC);
void DrawAxis(HDC hdc, HDC hMemDC);
void DrawGraph(HDC hdc, HDC hMemDC);
void DrawExpression(HDC hdc, HDC hMemDC);

// �f�o�b�O���̕`��
void DrawDebug(HDC hdc, HDC hMemDC, INT mx, INT my);

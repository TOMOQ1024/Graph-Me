#pragma once

#include "Main.h"

// �O���f�[�V�����t���u���V�̍쐬
HBRUSH CreateGradientBrushV(COLORREF top, COLORREF bottom, HDC hdc, int dcWidth, int dcHeight, int y0, int height);
HBRUSH CreateGradientBrushH(COLORREF top, COLORREF bottom, HDC hdc, int dcWidth, int dcHeight, int x0, int width);

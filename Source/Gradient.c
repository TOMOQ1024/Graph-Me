#include "Graph Me.h"

HBRUSH CreateGradientBrushV(COLORREF top, COLORREF bottom, HDC hdc, int dcWidth, int dcHeight, int y0, int height) {
	HBRUSH hBrush = NULL;
	HDC hMemDC = CreateCompatibleDC(hdc);
	HBITMAP hBMP = CreateCompatibleBitmap(hdc, dcWidth, dcHeight);
	SelectObject(hMemDC, hBMP);

	double r0 = GetRValue(top), r1 = GetRValue(bottom),
		g0 = GetGValue(top), g1 = GetGValue(bottom),
		b0 = GetBValue(top), b1 = GetBValue(bottom);
	for (int i = 0; i < height; i++) {
		RECT temp;
		int r, g, b;
		r = (int)(r0 + i * (r1 - r0) / (height));
		g = (int)(g0 + i * (g1 - g0) / (height));
		b = (int)(b0 + i * (b1 - b0) / (height));
		hBrush = CreateSolidBrush(RGB(r, g, b));
		temp.left = 0;
		temp.top = i + y0;
		temp.right = dcWidth;
		temp.bottom = i + y0 + 1;
		FillRect(hMemDC, &temp, hBrush);
		DeleteObject(hBrush);
	}
	HBRUSH pattern = CreatePatternBrush(hBMP);

	DeleteDC(hMemDC);
	DeleteObject(hBrush);
	DeleteObject(hBMP);

	return pattern;
}

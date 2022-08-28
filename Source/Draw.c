#include "Draw.h"
#include "Gradient.h"
#include "Utils.h"

void Draw(HDC hdc, HDC hMemDC, INT mx, INT my)
{
	// テキストの背景色をなくす
	SetBkMode(hMemDC, TRANSPARENT);
	
	// 背景
	SelectObject(hMemDC, GetStockObject(NULL_PEN));

	SelectObject(hMemDC, GetStockObject(BLACK_BRUSH));
	Rectangle(hMemDC, 0, 0, pane.width + 1, pane.height + 1);

	SelectObject(
		hMemDC,
		CreateGradientBrushH(0xA0A0A0, 0xD0D0D0, hMemDC, pane.lWidth, pane.height, 0, pane.lWidth * 3 / 4 + 1)
	);
	Rectangle(hMemDC, 0, 0, pane.lWidth * 3 / 4 + 1, pane.height + 1);
	DeleteObject(SelectObject(
		hMemDC,
		CreateGradientBrushH(0xD0D0D0, 0xB0B0B0, hMemDC, pane.lWidth, pane.height, pane.lWidth * 3 / 4, pane.lWidth / 4)
	));
	Rectangle(hMemDC, pane.lWidth * 3 / 4, 0, pane.lWidth, pane.height + 1);

	DeleteObject(SelectObject(hMemDC, GetStockObject(BLACK_BRUSH)));

	// コントロール
	DrawCtrl(hdc, hMemDC, mx, my);

	// 軸,グラフ,数式
	DrawMain(hdc, hMemDC);

	// デバッグ情報
	DrawDebug(hdc, hMemDC, mx, my);

	BitBlt(hdc, 0, 0, pane.width, pane.height, hMemDC, 0, 0, SRCCOPY);
}



void Segment(HDC hdc, double x0, double y0, double x1, double y1)
{
	INT X0 = gRtoI_x(x0);
	INT Y0 = gRtoI_y(y0);
	INT X1 = gRtoI_x(x1);
	INT Y1 = gRtoI_y(y1);

	MoveToEx(hdc, X0, Y0, NULL);
	LineTo(hdc, X1, Y1);
}

void tSegment(HDC hdc, double x0, double y0, double X0, double Y0, double X1, double Y1)
{
	Segment(hdc, x0 + (X0 * 0.3 + 0.2), y0 + Y0, x0 + (X1 * 0.3 + 0.2), y0 + Y1);
}

void mtSegment(
	HDC hdc, double t, double x0, double y0, INT xf0, INT yf0, INT xt0, INT yt0,
	INT xf1, INT yf1, INT xt1, INT yt1, INT xf2, INT yf2, INT xt2, INT yt2
)
{
	tSegment(
		hdc, x0, y0,
		Ease(t, xf0, xf1, xf2), Ease(t, yf0, yf1, yf2),
		Ease(t, xt0, xt1, xt2), Ease(t, yt0, yt1, yt2)
	);
}

void sRectangle(HDC hdc, double xc, double yc, double w, double h)
{
	Rectangle(
		hdc,
		gRtoI_x(xc - w / 2), gRtoI_y(yc - h / 2),
		gRtoI_x(xc + w / 2), gRtoI_y(yc + h / 2)
	);
}

void sSegment(HDC hdc, double xo, double yo, double d, INT x0, INT y0, INT x1, INT y1)
{
	double s = d * 0.3;
	MoveToEx(hdc, gRtoI_x((xo - 1.5) * 2 + (x0 - 1) * s), gRtoI_y((yo - 1.0) * 2 + (y0 - 1) * s), NULL);
	LineTo(hdc, gRtoI_x((xo - 1.5) * 2 + (x1 - 1) * s), gRtoI_y((yo - 1.0) * 2 + (y1 - 1) * s));
}

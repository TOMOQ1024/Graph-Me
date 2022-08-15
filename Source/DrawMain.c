#include "Main.h"
#include "Draw.h"
#include "Graph.h"
#include "Font.h"
#include "Scene.h"
#include "Slider.h"
#include <math.h>



void Segment(HDC hdc, double x0, double y0, double x1, double y1) {
	INT X0 = pane.lWidth + pane.paddingX + (graph.x0 + x0 * graph.scale) * pane.radius * 2;
	INT Y0 = pane.paddingY + (graph.y0 - y0 * graph.scale) * pane.radius * 2;
	INT X1 = pane.lWidth + pane.paddingX + (graph.x0 + x1 * graph.scale) * pane.radius * 2;
	INT Y1 = pane.paddingY + (graph.y0 - y1 * graph.scale) * pane.radius * 2;

	MoveToEx(hdc, X0, Y0, NULL);
	LineTo(hdc, X1, Y1);
}



void DrawMain(HDC hdc, HDC hMemDC)
{
	DrawAxis(hdc, hMemDC);
	DrawGraph(hdc, hMemDC);
	DrawExpression(hdc, hMemDC);
}



void DrawAxis(HDC hdc, HDC hMemDC)
{
	double x, y;

	// y 軸 主線
	for (
		int x0 = -(pane.paddingX + pane.radius * 2 * graph.x0) / (pane.radius * 2 * graph.scale);
		x0 <= (pane.paddingX + pane.radius * 2 * (1 - graph.x0)) / (pane.radius * 2 * graph.scale);
		x0++
	) {
		x = pane.lWidth + pane.paddingX + pane.radius * 2 * (graph.x0 + graph.scale * x0);
		DeleteObject(SelectObject(hMemDC, CreatePen(PS_SOLID, 2, 0x404040)));
		MoveToEx(hMemDC, x, 0, NULL);
		LineTo(hMemDC, x, pane.height);
	}

	// x 軸 主線
	for (
		int y0 = -(pane.paddingY + pane.radius * 2 * graph.y0) / (pane.radius * 2 * graph.scale);
		y0 <= (pane.paddingY + pane.radius * 2 * (1 - graph.y0)) / (pane.radius * 2 * graph.scale);
		y0++
		) {
		y = pane.paddingY + pane.radius * 2 * (graph.y0 + graph.scale * y0);
		DeleteObject(SelectObject(hMemDC, CreatePen(PS_SOLID, 2, 0x404040)));
		MoveToEx(hMemDC, pane.lWidth, y, NULL);
		LineTo(hMemDC, pane.width, y);
	}

	// y 軸 副線
	for (
		int x0 = -(pane.paddingX + pane.radius * 2 * graph.x0) / (pane.radius * 2 * graph.scale * 5);
		x0 <= (pane.paddingX + pane.radius * 2 * (1 - graph.x0)) / (pane.radius * 2 * graph.scale * 5);
		x0++
		) {
		x = pane.lWidth + pane.paddingX + pane.radius * 2 * (graph.x0 + graph.scale * 5 * x0);
		DeleteObject(SelectObject(hMemDC, CreatePen(PS_SOLID, x0 ? 2 : 4, 0x808080)));
		MoveToEx(hMemDC, x, 0, NULL);
		LineTo(hMemDC, x, pane.height);
	}

	// x 軸 副線
	for (
		int y0 = -(pane.paddingY + pane.radius * 2 * graph.y0) / (pane.radius * 2 * graph.scale * 5);
		y0 <= (pane.paddingY + pane.radius * 2 * (1 - graph.y0)) / (pane.radius * 2 * graph.scale * 5);
		y0++
		) {
		y = pane.paddingY + pane.radius * 2 * (graph.y0 + graph.scale * 5 * y0);
		DeleteObject(SelectObject(hMemDC, CreatePen(PS_SOLID, y0 ? 2 : 4, 0x808080)));
		MoveToEx(hMemDC, pane.lWidth, y, NULL);
		LineTo(hMemDC, pane.width, y);
	}

	DeleteObject(SelectObject(hMemDC, GetStockObject(BLACK_PEN)));
}


void DrawGraph(HDC hdc, HDC hMemDC)
{
	switch (scene) {
	case SCENE_TITLE:
	{
		double t = sliders[2].value;
		DeleteObject(SelectObject(hMemDC, CreatePen(PS_SOLID, 4, 0x00FFFF)));
		Segment(hMemDC, 0, 3, Ease(t, -1, 2, 4), -3);
		DeleteObject(SelectObject(hMemDC, GetStockObject(NULL_PEN)));
		break;
	}
	default:
	{
		INT X, Y;
		double x, y;
		DeleteObject(SelectObject(hMemDC, CreatePen(PS_SOLID, 4, 0x00FFFF)));
		for (X = 0; X <= pane.rWidth; X++) {
			x = (1.0 * (X - pane.paddingX) / pane.radius / 2 - graph.x0) / graph.scale;
			y = x * x / 4;
			Y = (graph.y0 - y * graph.scale) * pane.radius * 2;
			if (X == 0) MoveToEx(hMemDC, pane.lWidth + X, pane.paddingY + Y, NULL);
			else LineTo(hMemDC, pane.lWidth + X, pane.paddingY + Y);
		}

		DeleteObject(SelectObject(hMemDC, GetStockObject(NULL_PEN)));
		break;
	}
	}
}



void DrawExpression(HDC hdc, HDC hMemDC)
{
	if (scene != SCENE_PROBLEM) return;
	lstrcpy(graph.ex, TEXT("y=x^2/4"));
	// 表示する数式の文字列から描画範囲を取得し，長方形を描画する
	DeleteObject(SelectObject(hMemDC, CreatePen(PS_SOLID, 4, 0x00FFFF)));

	// 数式を描画する
	SetTextAlign(hMemDC, TA_LEFT | TA_BOTTOM);
	DeleteObject(SetFont(hMemDC, 20, 0x00FFFF, NULL));
	TextOut(hMemDC, pane.lWidth + 10, 30, graph.ex, lstrlen(graph.ex));

	DeleteObject(SelectObject(hMemDC, SYSTEM_FONT));
	DeleteObject(SelectObject(hMemDC, GetStockObject(NULL_PEN)));
}

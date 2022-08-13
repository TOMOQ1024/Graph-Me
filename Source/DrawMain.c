#include "Draw.h"
#include "Graph.h"
#include <math.h>

void DrawMain(HDC hdc, HDC hMemDC)
{
	DrawAxis(hdc, hMemDC);
	DrawGraph(hdc, hMemDC);
	DrawExpression(hdc, hMemDC);
}



void DrawAxis(HDC hdc, HDC hMemDC)
{
	double x, y;
	graph.x0 = 0.5;
	graph.y0 = 0.8;
	graph.scale = 0.09;

	// y é≤ éÂê¸
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

	// x é≤ éÂê¸
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

	// y é≤ ïõê¸
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

	// x é≤ ïõê¸
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
	INT X, Y;
	double x, y;
	DeleteObject(SelectObject(hMemDC, CreatePen(PS_SOLID, 4, 0x00FFFF)));
	for (X = 0; X <= pane.rWidth; X++) {
		x = (1.0 * (X - pane.paddingX) / pane.radius / 2 - graph.x0) / graph.scale;
		y = x*x/4;
		Y = (graph.y0 - y * graph.scale) * pane.radius * 2;
		if (X == 0) MoveToEx(hMemDC, pane.lWidth + X, pane.paddingY + Y, NULL);
		else LineTo(hMemDC, pane.lWidth + X, pane.paddingY + Y);
	}

	DeleteObject(SelectObject(hMemDC, GetStockObject(NULL_PEN)));
}



void DrawExpression(HDC hdc, HDC hMemDC)
{
	//
}

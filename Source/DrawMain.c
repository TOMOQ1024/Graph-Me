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
	graph.y0 = 0.5;
	graph.scale = 0.09;

	// y �� ���
	for (
		int x0 = -(pane.paddingX + pane.radius * 2 * graph.x0) / (pane.radius * 2 * graph.scale);
		x0 <= (pane.paddingX + pane.radius * 2 * (1 - graph.x0)) / (pane.radius * 2 * graph.scale);
		x0++
	) {
		x = pane.lWidth + pane.paddingX + pane.radius * 2 * (graph.x0 + graph.scale * x0);
		DeleteObject(SelectObject(hMemDC, CreatePen(PS_SOLID, 3, 0x404040)));
		MoveToEx(hMemDC, x, 0, NULL);
		LineTo(hMemDC, x, pane.height);
	}

	// x �� ���
	for (
		int y0 = -(pane.paddingY + pane.radius * 2 * graph.y0) / (pane.radius * 2 * graph.scale);
		y0 <= (pane.paddingY + pane.radius * 2 * (1 - graph.y0)) / (pane.radius * 2 * graph.scale);
		y0++
		) {
		y = pane.paddingY + pane.radius * 2 * (graph.y0 + graph.scale * y0);
		DeleteObject(SelectObject(hMemDC, CreatePen(PS_SOLID, 3, 0x404040)));
		MoveToEx(hMemDC, pane.lWidth, y, NULL);
		LineTo(hMemDC, pane.width, y);
	}

	// y �� ����
	for (
		int x0 = -(pane.paddingX + pane.radius * 2 * graph.x0) / (pane.radius * 2 * graph.scale * 5);
		x0 <= (pane.paddingX + pane.radius * 2 * (1 - graph.x0)) / (pane.radius * 2 * graph.scale * 5);
		x0++
		) {
		x = pane.lWidth + pane.paddingX + pane.radius * 2 * (graph.x0 + graph.scale * 5 * x0);
		DeleteObject(SelectObject(hMemDC, CreatePen(PS_SOLID, 3, 0x808080)));
		MoveToEx(hMemDC, x, 0, NULL);
		LineTo(hMemDC, x, pane.height);
	}

	// x �� ����
	for (
		int y0 = -(pane.paddingY + pane.radius * 2 * graph.y0) / (pane.radius * 2 * graph.scale * 5);
		y0 <= (pane.paddingY + pane.radius * 2 * (1 - graph.y0)) / (pane.radius * 2 * graph.scale * 5);
		y0++
		) {
		y = pane.paddingY + pane.radius * 2 * (graph.y0 + graph.scale * 5 * y0);
		DeleteObject(SelectObject(hMemDC, CreatePen(PS_SOLID, 3, 0x808080)));
		MoveToEx(hMemDC, pane.lWidth, y, NULL);
		LineTo(hMemDC, pane.width, y);
	}

	DeleteObject(SelectObject(hMemDC, GetStockObject(BLACK_PEN)));
}


void DrawGraph(HDC hdc, HDC hMemDC)
{
	//
}



void DrawExpression(HDC hdc, HDC hMemDC)
{
	//
}

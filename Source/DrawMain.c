#include "Main.h"
#include "Draw.h"
#include "Graph.h"
#include "Font.h"
#include "Scene.h"
#include "Slider.h"
#include <math.h>



void Segment(HDC hdc, double x0, double y0, double x1, double y1)
{
	INT X0 = RtoI_x(x0);
	INT Y0 = RtoI_y(y0);
	INT X1 = RtoI_x(x1);
	INT Y1 = RtoI_y(y1);

	MoveToEx(hdc, X0, Y0, NULL);
	LineTo(hdc, X1, Y1);
}

void tSegment(HDC hdc, double x0, double y0, double X0, double Y0, double X1, double Y1)
{
	Segment(hdc, x0 + (X0 * 0.3 + 0.2), y0 + Y0, x0 + (X1 * 0.3 + 0.2), y0 + Y1);
}

void mtSegment(
	HDC hdc, double t, double x0,  double y0, INT xf0, INT yf0, INT xt0, INT yt0,
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
		RtoI_x(xc - w / 2), RtoI_y(yc - h / 2),
		RtoI_x(xc + w / 2), RtoI_y(yc + h / 2)
	);
}

void sSegment(HDC hdc, double xo, double yo, double d, INT x0, INT y0, INT x1, INT y1)
{
	double s = d * 0.3;
	MoveToEx(hdc, RtoI_x((xo - 1.5) * 2 + (x0 - 1) * s), RtoI_y((yo - 1.0) * 2 + (y0 - 1) * s), NULL);
	LineTo(hdc, RtoI_x((xo - 1.5) * 2 + (x1 - 1) * s), RtoI_y((yo - 1.0) * 2 + (y1 - 1) * s));
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

	// y é≤ éÂê¸
	for (
		int x0 = (INT)(-(pane.paddingX + pane.radius * 2 * graph.x0) / (pane.radius * 2 * graph.scale));
		x0 <= (pane.paddingX + pane.radius * 2 * (1 - graph.x0)) / (pane.radius * 2 * graph.scale);
		x0++
	) {
		x = pane.lWidth + pane.paddingX + pane.radius * 2 * (graph.x0 + graph.scale * x0);
		DeleteObject(SelectObject(hMemDC, CreatePen(PS_SOLID, 1, 0x404040)));
		MoveToEx(hMemDC, (INT)x, 0, NULL);
		LineTo(hMemDC, (INT)x, pane.height);
	}

	// x é≤ éÂê¸
	for (
		int y0 = (INT)(-(pane.paddingY + pane.radius * 2 * graph.y0) / (pane.radius * 2 * graph.scale));
		y0 <= (pane.paddingY + pane.radius * 2 * (1 - graph.y0)) / (pane.radius * 2 * graph.scale);
		y0++
		) {
		y = pane.paddingY + pane.radius * 2 * (graph.y0 + graph.scale * y0);
		DeleteObject(SelectObject(hMemDC, CreatePen(PS_SOLID, 1, 0x404040)));
		MoveToEx(hMemDC, pane.lWidth, (INT)y, NULL);
		LineTo(hMemDC, pane.width, (INT)y);
	}

	// y é≤ ïõê¸
	for (
		int x0 = (INT)(-(pane.paddingX + pane.radius * 2 * graph.x0) / (pane.radius * 2 * graph.scale * 5));
		x0 <= (pane.paddingX + pane.radius * 2 * (1 - graph.x0)) / (pane.radius * 2 * graph.scale * 5);
		x0++
		) {
		x = pane.lWidth + pane.paddingX + pane.radius * 2 * (graph.x0 + graph.scale * 5 * x0);
		DeleteObject(SelectObject(hMemDC, CreatePen(PS_SOLID, x0 ? 1 : 3, 0x808080)));
		MoveToEx(hMemDC, (INT)x, 0, NULL);
		LineTo(hMemDC, (INT)x, pane.height);
	}

	// x é≤ ïõê¸
	for (
		int y0 = (INT)(-(pane.paddingY + pane.radius * 2 * graph.y0) / (pane.radius * 2 * graph.scale * 5));
		y0 <= (pane.paddingY + pane.radius * 2 * (1 - graph.y0)) / (pane.radius * 2 * graph.scale * 5);
		y0++
		) {
		y = pane.paddingY + pane.radius * 2 * (graph.y0 + graph.scale * 5 * y0);
		DeleteObject(SelectObject(hMemDC, CreatePen(PS_SOLID, y0 ? 1 : 3, 0x808080)));
		MoveToEx(hMemDC, pane.lWidth, (INT)y, NULL);
		LineTo(hMemDC, pane.width, (INT)y);
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

		/*  å≈íËïî  */ {
			// G
			tSegment(hMemDC, -4, 1.5, 2, 2, 0, 2);
			tSegment(hMemDC, -4, 1.5, 0, 0, 0, 2);
			tSegment(hMemDC, -4, 1.5, 0, 0, 2, 0);
			tSegment(hMemDC, -4, 1.5, 2, 1, 2, 0);
			tSegment(hMemDC, -4, 1.5, 2, 1, 1, 1);

			// R
			tSegment(hMemDC, -3, 1.5, 0, 0, 0, 2);
			tSegment(hMemDC, -3, 1.5, 2, 2, 0, 2);
			tSegment(hMemDC, -3, 1.5, 2, 2, 2, 1);
			tSegment(hMemDC, -3, 1.5, 0, 1, 2, 1);
			tSegment(hMemDC, -3, 1.5, 1, 1, 2, 0);

			// A
			tSegment(hMemDC, -2, 1.5, 0, 0, 0, 2);
			tSegment(hMemDC, -2, 1.5, 2, 2, 0, 2);
			tSegment(hMemDC, -2, 1.5, 2, 2, 2, 0);
			tSegment(hMemDC, -2, 1.5, 0, 1, 2, 1);

			// P
			tSegment(hMemDC, -1, 1.5, 0, 0, 0, 2);
			tSegment(hMemDC, -1, 1.5, 2, 2, 0, 2);
			tSegment(hMemDC, -1, 1.5, 2, 2, 2, 1);
			tSegment(hMemDC, -1, 1.5, 0, 1, 2, 1);

			// H
			tSegment(hMemDC, 0, 1.5, 0, 0, 0, 2);
			tSegment(hMemDC, 0, 1.5, 2, 0, 2, 2);
			tSegment(hMemDC, 0, 1.5, 0, 1, 2, 1);

			// _
			tSegment(hMemDC, 1, 1.5, 0, 0, 2, 0);

			// M
			tSegment(hMemDC, 2, 1.5, 0, 0, 0, 2);
			tSegment(hMemDC, 2, 1.5, 2, 2, 0, 2);
			tSegment(hMemDC, 2, 1.5, 2, 2, 2, 0);
			tSegment(hMemDC, 2, 1.5, 1, 0, 1, 2);

			// E
			tSegment(hMemDC, 3, 1.5, 2, 2, 0, 2);
			tSegment(hMemDC, 3, 1.5, 0, 0, 0, 2);
			tSegment(hMemDC, 3, 1.5, 0, 0, 2, 0);
			tSegment(hMemDC, 3, 1.5, 0, 1, 2, 1);
		}

		/*  â¬ìÆïî  */ {
			/*  _S_  */ {
				mtSegment(
					hMemDC, t, -4, -3.5,
					0, 0, 2, 0,
					0, 2, 2, 2,
					0, 0, 2, 0
				);
				mtSegment(
					hMemDC, t, -4, -3.5,
					2, 0, 0, 0,
					0, 1, 2, 1,
					0, 0, 2, 0
				);
				mtSegment(
					hMemDC, t, -4, -3.5,
					0, 0, 2, 0,
					0, 0, 2, 0,
					0, 0, 2, 0
				);
				mtSegment(
					hMemDC, t, -4, -3.5,
					2, 0, 2, 0,
					0, 1, 0, 2,
					0, 0, 0, 0
				);
				mtSegment(
					hMemDC, t, -4, -3.5,
					0, 0, 0, 0,
					2, 1, 2, 0,
					2, 0, 2, 0
				);
			}
			/*  _E_  */ {
				mtSegment(
					hMemDC, t, -3, -3.5,
					0, 0, 2, 0,
					0, 2, 2, 2,
					0, 0, 2, 0
				);
				mtSegment(
					hMemDC, t, -3, -3.5,
					2, 0, 2, 0,
					0, 1, 2, 1,
					2, 0, 2, 0
				);
				mtSegment(
					hMemDC, t, -3, -3.5,
					0, 0, 2, 0,
					0, 0, 2, 0,
					0, 0, 2, 0
				);
				mtSegment(
					hMemDC, t, -3, -3.5,
					2, 0, 2, 0,
					0, 1, 0, 2,
					2, 0, 2, 0
				);
				mtSegment(
					hMemDC, t, -3, -3.5,
					0, 0, 0, 0,
					0, 1, 0, 0,
					2, 0, 0, 0
				);
			}
			/*  ETP  */ {
				mtSegment(
					hMemDC, t, -2, -3.5,
					0, 2, 2, 2,
					0, 2, 2, 2,
					0, 2, 2, 2
				);
				mtSegment(
					hMemDC, t, -2, -3.5,
					0, 1, 2, 1,
					1, 1, 1, 1,
					2, 1, 2, 2
				);
				mtSegment(
					hMemDC, t, -2, -3.5,
					0, 0, 2, 0,
					1, 0, 1, 0,
					0, 1, 2, 1
				);
				mtSegment(
					hMemDC, t, -2, -3.5,
					0, 0, 0, 2,
					1, 0, 1, 2,
					0, 0, 0, 2
				);
			}
			/*  XTL  */ {
				mtSegment(
					hMemDC, t, -1, -3.5,
					0, 0, 2, 2,
					1, 0, 1, 2,
					0, 0, 0, 2
				);
				mtSegment(
					hMemDC, t, -1, -3.5,
					0, 2, 2, 0,
					0, 2, 2, 2,
					0, 0, 2, 0
				);
				mtSegment(
					hMemDC, t, -1, -3.5,
					0, 2, 2, 0,
					0, 2, 2, 2,
					0, 0, 2, 0
				);
			}
			/*  IIA  */ {
				mtSegment(
					hMemDC, t, 0, -3.5,
					0, 0, 2, 0,
					0, 0, 2, 0,
					0, 2, 2, 2
				);
				mtSegment(
					hMemDC, t, 0, -3.5,
					0, 2, 2, 2,
					0, 2, 2, 2,
					0, 1, 2, 1
				);
				mtSegment(
					hMemDC, t, 0, -3.5,
					1, 0, 1, 2,
					1, 0, 1, 2,
					0, 0, 0, 2
				);
				mtSegment(
					hMemDC, t, 0, -3.5,
					1, 0, 1, 2,
					1, 0, 1, 2,
					2, 0, 2, 2
				);
			}
			/*  TNY  */ {
				mtSegment(
					hMemDC, t, 1, -3.5,
					1, 0, 1, 2,
					0, 0, 0, 2,
					0, 1, 0, 2
				);
				mtSegment(
					hMemDC, t, 1, -3.5,
					1, 0, 1, 2,
					1, 0, 1, 2,
					1, 0, 1, 1
				);
				mtSegment(
					hMemDC, t, 1, -3.5,
					1, 0, 1, 2,
					2, 0, 2, 2,
					2, 1, 2, 2
				);
				mtSegment(
					hMemDC, t, 1, -3.5,
					0, 2, 1, 2,
					0, 2, 1, 2,
					0, 1, 1, 1
				);
				mtSegment(
					hMemDC, t, 1, -3.5,
					1, 2, 2, 2,
					1, 0, 2, 0,
					1, 1, 2, 1
				);
			}
			/*  _G_  */ {
				mtSegment(
					hMemDC, t, 2, -3.5,
					2, 0, 2, 0,
					2, 2, 0, 2,
					2, 0, 0, 0
				);
				mtSegment(
					hMemDC, t, 2, -3.5,
					0, 0, 2, 0,
					0, 0, 0, 2,
					0, 0, 0, 0
				);
				mtSegment(
					hMemDC, t, 2, -3.5,
					0, 0, 2, 0,
					0, 0, 2, 0,
					0, 0, 2, 0
				);
				mtSegment(
					hMemDC, t, 2, -3.5,
					1, 0, 2, 0,
					2, 1, 2, 0,
					2, 0, 2, 0
				);
				mtSegment(
					hMemDC, t, 2, -3.5,
					0, 0, 1, 0,
					1, 1, 2, 1,
					0, 0, 1, 0
				);
			}
			/*  _S_  */ {
				mtSegment(
					hMemDC, t, 3, -3.5,
					0, 0, 0, 0,
					0, 2, 2, 2,
					0, 0, 2, 0
				);
				mtSegment(
					hMemDC, t, 3, -3.5,
					0, 0, 2, 0,
					0, 1, 2, 1,
					1, 0, 1, 0
				);
				mtSegment(
					hMemDC, t, 3, -3.5,
					2, 0, 2, 0,
					0, 0, 2, 0,
					0, 0, 2, 0
				);
				mtSegment(
					hMemDC, t, 3, -3.5,
					0, 0, 0, 0,
					0, 1, 0, 2,
					1, 0, 1, 0
				);
				mtSegment(
					hMemDC, t, 3, -3.5,
					2, 0, 2, 0,
					2, 1, 2, 0,
					1, 0, 1, 0
				);
			}
		}

		DeleteObject(SelectObject(hMemDC, GetStockObject(NULL_PEN)));
		break;
	}
	case SCENE_STAGES:
	{
		//INT problem_tmp;
		double a, b, s, d;
		a = sliders[0].value + sin(M_PI * sliders[0].value) / M_PI;
		b = sliders[1].value - sin(M_PI * sliders[1].value) / M_PI;
		s = RtoI_x(1) - RtoI_x(0);
		problem_temp = (6 + floor(a / 2) - round(b / 2) * 4) * 12;

		DeleteObject(SelectObject(hMemDC, GetStockObject(NULL_PEN)));
		DeleteObject(SelectObject(hMemDC, CreateSolidBrush(0x002020)));
		
		d = s * min(1 - cos(M_PI * a) / 5, 1 + cos(M_PI * b) / 5);
		Ellipse(hMemDC,
			RtoI_x(a) - d, RtoI_y(b) - d,
			RtoI_x(a) + d, RtoI_y(b) + d
		);

		for (INT y = 0; y < 3; y++) {
			for (INT x = 0; x < 4; x++) {
				DeleteObject(SelectObject(hMemDC, CreatePen(PS_SOLID, 4, 0x00FFFF)));
				DeleteObject(SelectObject(hMemDC, CreateSolidBrush(8 + x - y * 4 == problem_temp / 12 ? 0x004040 : 0x002020)));
				d = pow(2,
					1 / (
						(x * 2 - 3 - a) * (x * 2 - 3 - a) +
						(y * 2 - 2 - b) * (y * 2 - 2 - b) + 1
					)
				) * 0.8;
				sRectangle(hMemDC, (x - 1.5) * 2, (y - 1.0) * 2, d, d);
				switch (8 + x - y * 4) {
				case 0:
					sSegment(hMemDC, x, y, d, 0, 2, 1, 0);
					sSegment(hMemDC, x, y, d, 2, 2, 1, 0);
					break;
				case 1:
					sSegment(hMemDC, x, y, d, 0, 0, 2, 0);
					sSegment(hMemDC, x, y, d, 2, 2, 2, 0);
					sSegment(hMemDC, x, y, d, 2, 2, 0, 0);
					break;
				case 2:
					sSegment(hMemDC, x, y, d, 0, 0, 0, 2);
					sSegment(hMemDC, x, y, d, 2, 0, 2, 2);
					break;
				case 3:
					sSegment(hMemDC, x, y, d, 0, 1, 1, 2);
					sSegment(hMemDC, x, y, d, 2, 1, 1, 2);
					break;
				case 4:
					sSegment(hMemDC, x, y, d, 0, 0, 0, 1);
					sSegment(hMemDC, x, y, d, 2, 1, 0, 1);
					sSegment(hMemDC, x, y, d, 2, 1, 2, 2);
					break;
				case 5:
					sSegment(hMemDC, x, y, d, 0, 1, 1, 0);
					sSegment(hMemDC, x, y, d, 1, 2, 2, 1);
					break;
				case 6:
					sSegment(hMemDC, x, y, d, 0, 0, 1, 0);
					sSegment(hMemDC, x, y, d, 1, 2, 2, 2);
					break;
				case 7:
					sSegment(hMemDC, x, y, d, 0, 0, 1, 0);
					sSegment(hMemDC, x, y, d, 2, 2, 1, 0);
					sSegment(hMemDC, x, y, d, 2, 2, 1, 2);
					sSegment(hMemDC, x, y, d, 0, 0, 1, 2);
					break;
				case 8:
					sSegment(hMemDC, x, y, d, 0, 0, 2, 0);
					sSegment(hMemDC, x, y, d, 0, 0, 1, 2);
					break;
				case 9:
					sSegment(hMemDC, x, y, d, 0, 0, 2, 2);
					sSegment(hMemDC, x, y, d, 2, 0, 2, 2);
					sSegment(hMemDC, x, y, d, 2, 0, 0, 2);
					sSegment(hMemDC, x, y, d, 0, 0, 0, 2);
					break;
				case 10:
					sSegment(hMemDC, x, y, d, 0, 1, 1, 0);
					sSegment(hMemDC, x, y, d, 2, 1, 1, 0);
					sSegment(hMemDC, x, y, d, 2, 1, 1, 2);
					sSegment(hMemDC, x, y, d, 0, 1, 1, 2);
					break;
				case 11:
					sSegment(hMemDC, x, y, d, 0, 1, 1, 0);
					sSegment(hMemDC, x, y, d, 2, 1, 1, 0);
					sSegment(hMemDC, x, y, d, 2, 1, 1, 2);
					sSegment(hMemDC, x, y, d, 0, 1, 1, 2);
					sSegment(hMemDC, x, y, d, 0, 0, 2, 0);
					sSegment(hMemDC, x, y, d, 2, 2, 2, 0);
					sSegment(hMemDC, x, y, d, 2, 2, 0, 2);
					sSegment(hMemDC, x, y, d, 0, 0, 0, 2);
					break;
				}
			}
		}

		DeleteObject(SelectObject(hMemDC, GetStockObject(NULL_BRUSH)));
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
			Y = (INT)((graph.y0 - y * graph.scale) * pane.radius * 2);
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
	// ï\é¶Ç∑ÇÈêîéÆÇÃï∂éöóÒÇ©ÇÁï`âÊîÕàÕÇéÊìæÇµÅCí∑ï˚å`Çï`âÊÇ∑ÇÈ
	DeleteObject(SelectObject(hMemDC, CreatePen(PS_SOLID, 4, 0x00FFFF)));

	// êîéÆÇï`âÊÇ∑ÇÈ
	SetTextAlign(hMemDC, TA_LEFT | TA_BOTTOM);
	DeleteObject(SetFont(hMemDC, 20, 0x00FFFF, 0));
	TextOut(hMemDC, pane.lWidth + 10, 30, graph.ex, lstrlen(graph.ex));

	DeleteObject(SelectObject(hMemDC, GetStockObject(SYSTEM_FONT)));
	DeleteObject(SelectObject(hMemDC, GetStockObject(NULL_PEN)));
}

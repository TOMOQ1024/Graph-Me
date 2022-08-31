#include "Draw.h"
#include "Font.h"
#include "Slider.h"
#include "Utils.h"



void Curve(double p_arr[][2], INT* p_size, double a, double b, double c, double d, double x0, double y0, double x1, double y1)
{
	double hSq = 0.5 / graph.scale / pane.radius; hSq *= hSq;
	double HSq = 5.0 / graph.scale / pane.radius; HSq *= HSq;
	double x, y;
	INT Y;
	x = (x0 + x1) / 2;
	y = Calc(x, a, b, c, d);
	Y = gRtoI_y(y);
	if (0 < Y && Y < pane.height) {
		p_arr[*p_size][0] = x;
		p_arr[*p_size][1] = y;
		*p_size += 1;
	}
	if (hSq < DistanceSq(x0, y0, x, y) && hSq < x - x0)
		Curve(p_arr, p_size, a, b, c, d, x0, y0, x, y);
	if (hSq < DistanceSq(x, y, x1, y1) && hSq < x1 - x)
		Curve(p_arr, p_size, a, b, c, d, x, y, x1, y1);
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
		int x0 = (INT)(-(pane.paddingX + pane.radius * 2 * graph.x0) / (pane.radius * 2 * graph.scale));
		x0 <= (pane.paddingX + pane.radius * 2 * (1 - graph.x0)) / (pane.radius * 2 * graph.scale);
		x0++
	) {
		x = pane.lWidth + pane.paddingX + pane.radius * 2 * (graph.x0 + graph.scale * x0);
		DeleteObject(SelectObject(hMemDC, CreatePen(PS_SOLID, 1, 0x404040)));
		MoveToEx(hMemDC, (INT)x, 0, NULL);
		LineTo(hMemDC, (INT)x, pane.height);
	}

	// x 軸 主線
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

	// y 軸 副線
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

	// x 軸 副線
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

		/*  固定部  */ {
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

		/*  可動部  */ {
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
		INT r;
		double a, b, s, d;
		a = sliders[0].value + sin(M_PI * sliders[0].value) / M_PI;
		b = sliders[1].value - sin(M_PI * sliders[1].value) / M_PI;
		s = gRtoI_x(1) - gRtoI_x(0);
		problem_temp = (INT)((6 + floor(a / 2) - round(b / 2) * 4) * 12);

		DeleteObject(SelectObject(hMemDC, GetStockObject(NULL_PEN)));
		DeleteObject(SelectObject(hMemDC, CreateSolidBrush(0x002020)));
		
		r = (INT)(s * min(1 - cos(M_PI * a) / 5, 1 + cos(M_PI * b) / 5));
		Ellipse(hMemDC,
			gRtoI_x(a) - r, gRtoI_y(b) - r,
			gRtoI_x(a) + r, gRtoI_y(b) + r
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
	case SCENE_LEVELS:
	{
		INT r;
		WCHAR l[2];
		double a, b, s, d;
		a = sliders[0].value + sin(M_PI * sliders[0].value) / M_PI;
		b = sliders[1].value - sin(M_PI * sliders[1].value) / M_PI;
		s = gRtoI_x(1) - gRtoI_x(0);
		problem_temp = problem_temp / 12 * 12 + (INT)(6 + floor(a / 2) - round(b / 2) * 4);

		DeleteObject(SelectObject(hMemDC, GetStockObject(NULL_PEN)));
		DeleteObject(SelectObject(hMemDC, CreateSolidBrush(0x002020)));

		r = (INT)(s * min(1 - cos(M_PI * a) / 5, 1 + cos(M_PI * b) / 5));
		Ellipse(hMemDC,
			gRtoI_x(a) - r, gRtoI_y(b) - r,
			gRtoI_x(a) + r, gRtoI_y(b) + r
		);

		for (INT y = 0; y < 3; y++) {
			for (INT x = 0; x < 4; x++) {
				DeleteObject(SelectObject(hMemDC, CreatePen(PS_SOLID, 4, 0x00FFFF)));
				DeleteObject(SelectObject(hMemDC, CreateSolidBrush(8 + x - y * 4 == problem_temp % 12 ? 0x004040 : 0x002020)));
				d = pow(2,
					1 / (
						(x * 2 - 3 - a) * (x * 2 - 3 - a) +
						(y * 2 - 2 - b) * (y * 2 - 2 - b) + 1
						)
				) * 0.8;
				sRectangle(hMemDC, (x - 1.5) * 2, (y - 1.0) * 2, d, d);

				DeleteObject(SetFont(hMemDC, gRtoI_x(d * 0.8) - gRtoI_x(0), 0x00FFFF, 0));
				wsprintf(l, L"%X", 9 + x - y * 4);
				TextOut(hMemDC, gRtoI_x((x - 1.5) * 2), gRtoI_y((y - 1.0) * 2 - d * 0.4), l, lstrlen(l));
			}
		}

		DeleteObject(SelectObject(hMemDC, GetStockObject(NULL_BRUSH)));
		DeleteObject(SelectObject(hMemDC, GetStockObject(NULL_PEN)));
		DeleteObject(SelectObject(hMemDC, GetStockObject(SYSTEM_FONT)));
		break;
	}
	case SCENE_PROBLEM:
	{
		INT X, Y;
		double* ans = problems[problem_crnt].answer;
		double a, b, c, d, tmp;
		double (*p_arr)[2] = malloc(sizeof(double) * 10000);
		INT p_size;
		if (p_arr == NULL) return;
		a = sliders[0].value;
		b = sliders[1].value;
		c = sliders[2].value;
		d = sliders[3].value;
		
		DeleteObject(SelectObject(hMemDC, GetStockObject(NULL_PEN)));
		DeleteObject(SelectObject(hMemDC, CreateSolidBrush(0x00FFFF)));

		// 接線のグラフ
		for (INT t = 0; t < problems[problem_crnt].tcount; t++) {
			
		}
		// 目的のグラフ
		if (!problems[problem_crnt].hide) {
			p_size = 0;
			tmp = Calc(gItoR_x(pane.width), ans[0], ans[1], ans[2], ans[3]);
			Curve(
				p_arr, &p_size, ans[0], ans[1], ans[2], ans[3],
				gItoR_x(pane.lWidth), Calc(gItoR_x(pane.lWidth), ans[0], ans[1], ans[2], ans[3]),
				gItoR_x(pane.width), Calc(gItoR_x(pane.width), ans[0], ans[1], ans[2], ans[3])
			);
			for (INT i = 0; i < p_size - 1; i++) {
				for (INT j = i + 1; j < p_size; j++) {
					if (p_arr[j][0] < p_arr[i][0]) {
						tmp = p_arr[i][0];
						p_arr[i][0] = p_arr[j][0];
						p_arr[j][0] = tmp;
						tmp = p_arr[i][1];
						p_arr[i][1] = p_arr[j][1];
						p_arr[j][1] = tmp;
					}
				}
			}
			for (INT i = 0; i < p_size; i++) {
				X = gRtoI_x(p_arr[i][0]);
				if (i % 50 < 20)continue;
				Y = gRtoI_y(p_arr[i][1]);
				Ellipse(
					hMemDC, X - 2, Y - 2, X + 2, Y + 2
				);
			}
		}

		p_size = 0;
		Curve(
			p_arr, &p_size, a, b, c, d,
			gItoR_x(pane.lWidth), Calc(gItoR_x(pane.lWidth), a, b, c, d),
			gItoR_x(pane.width), Calc(gItoR_x(pane.width), a, b, c, d)
		);
		for (INT i = 0; i < p_size; i++) {
			X = gRtoI_x(p_arr[i][0]);
			Y = gRtoI_y(p_arr[i][1]);
			Ellipse(
				hMemDC, X - 3, Y - 3, X + 3, Y + 3
			);
		}

		DeleteObject(SelectObject(hMemDC, GetStockObject(NULL_BRUSH)));

		free(p_arr);

		//for (X = 0; X <= pane.rWidth; X++) {
		//	x = (1.0 * (X - pane.paddingX) / pane.radius / 2 - graph.x0) / graph.scale;
		//	y = Calc(x, ans[0], ans[1], ans[2], ans[3]);
		//	Y = (INT)((graph.y0 - y * graph.scale) * pane.radius * 2);
		//	if (X == 0) MoveToEx(hMemDC, pane.lWidth + X, pane.paddingY + Y, NULL);
		//	else LineTo(hMemDC, pane.lWidth + X, pane.paddingY + Y);
		//}
		//DeleteObject(SelectObject(hMemDC, CreatePen(PS_SOLID, 4, 0x00FFFF)));
		//for (X = 0; X <= pane.rWidth; X++) {
		//	x = (1.0 * (X - pane.paddingX) / pane.radius / 2 - graph.x0) / graph.scale;
		//	y = Calc(x, a, b, c, d);
		//	Y = (INT)((graph.y0 - y * graph.scale) * pane.radius * 2);
		//	if (X == 0) MoveToEx(hMemDC, pane.lWidth + X, pane.paddingY + Y, NULL);
		//	else LineTo(hMemDC, pane.lWidth + X, pane.paddingY + Y);
		//}

		//DeleteObject(SelectObject(hMemDC, GetStockObject(NULL_PEN)));
		break;
	}
	}
}


void DrawExpression(HDC hdc, HDC hMemDC)
{
	switch (scene) {
	case SCENE_PROBLEM:
	{
		// 表示する数式の文字列から描画範囲を取得し，長方形を描画する
		DeleteObject(SelectObject(hMemDC, CreatePen(PS_SOLID, 4, 0x00FFFF)));

		// 数式を描画する
		SetTextAlign(hMemDC, TA_LEFT | TA_BOTTOM);
		DeleteObject(SetFont(hMemDC, 20, 0x00FFFF, 0));
		TextOut(hMemDC, pane.lWidth + 10, 30, graph.ex, lstrlen(graph.ex));

		DeleteObject(SelectObject(hMemDC, GetStockObject(SYSTEM_FONT)));
		DeleteObject(SelectObject(hMemDC, GetStockObject(NULL_PEN)));
		break;
	}
	}
}

#include "Draw.h"
#include "Font.h"
#include "Slider.h"
#include "Utils.h"


INT Y_MAX;
INT Y_MIN;



void Curve(double (*Calc)(INT, double, double), INT id, double x0, double y0, double x1, double y1)
{
	static INT count = 100;
	if (1e+2 < count) {
		count--;
		return;
	}
	double hSq = 0.5 / graph.scale / pane.radius; hSq *= hSq;
	double ax, ay, bx, by, cx, cy;
	INT AY, BY, CY;
	INT N = 4;
	double d = (x1 - x0) / N;
	ax = x0;
	ay = Calc(id, ax, 0);
	AY = gRtoI_y(ay);
	bx = x0 + d;
	by = Calc(id, bx, 0);
	BY = gRtoI_y(by);
	if (hSq < DistanceSq(ax, ay, bx, by)) {
		if (-10 < BY && BY < Y_MAX) {
			points_arr[points_count][0] = bx;
			points_arr[points_count][1] = by;
			points_count++;
		}
		if (hSq * 8 < d || !((AY < Y_MIN && BY < Y_MIN) || (Y_MAX < AY && Y_MAX < BY))) {
			if (hSq < d || hSq * hSq > fabs(atan2(by - ay, bx - ax) - atan2(by - ay, bx - ax))) {
				count++;
				Curve(Calc, id, ax, ay, bx, by);
			}
		}
	}
	for (INT i = 2; i <= N; i++) {
		cx = bx + d;
		cy = Calc(id, cx, 0);
		CY = gRtoI_y(cy);

		if (hSq < DistanceSq(ax, ay, cx, cy)) {
			if (-10 < BY && BY < Y_MAX) {
				points_arr[points_count][0] = bx;
				points_arr[points_count][1] = by;
				points_count++;
			}
			if (hSq * 8 < d || !((CY < Y_MIN && BY < Y_MIN) || (Y_MAX < CY && Y_MAX < BY))) {
				if (hSq < d || hSq * hSq > fabs(atan2(cy - by, cx - bx) - atan2(cy - by, cx - bx))) {
					count++;
					Curve(Calc, id, bx, by, cx, cy);
				}
			}
		}

		ax = bx;
		ay = by;
		AY = BY;
		bx = cx;
		by = cy;
		BY = CY;
	}
	//x = (x0 + x1) / 2;
	//y = Calc(id, x, 0);
	//X = gRtoI_x(x);
	//Y = gRtoI_y(y);
	//if (-10 < Y && Y < pane.height + 10) {
	//	points_arr[points_count][0] = x;
	//	points_arr[points_count][1] = y;
	//	points_count++;
	//}
	//if (hSq < DistanceSq(x0, y0, x, y)) {
	//	if (hSq * 4 < x - x0 || !((Y < -10 && Y0 < -10) || (pane.height + 10 < Y && pane.height + 10 < Y0))) {
	//		if (hSq < x - x0 || hSq * hSq > fabs(atan2(y1 - y0, x1 - x0) - atan2(y - y0, x - x0))) {
	//			count++;
	//			Curve(Calc, id, x0, y0, x, y);
	//		}
	//	}
	//}
	//	//else if((Y0 < -1e+100 || 1e+100 < Y0) ^ (Y < -1e+100 || 1e+100 < Y)) {
	//	//	
	//	//}
	//if (hSq < DistanceSq(x, y, x1, y1)) {
	//	if (hSq * 4 < x1 - x || !((Y1 < -10 && Y < -10) || (pane.height + 10 < Y1 && pane.height + 10 < Y))) {
	//		if (hSq < x1 - x || hSq * hSq > fabs(atan2(Y1 - Y0, X1 - X0) - atan2(Y1 - Y, X1 - X))) {
	//			count++;
	//			Curve(Calc, id, x, y, x1, y1);
	//		}
	//	}
	//}
	count--;
}



void DrawMain(HDC hMemDC)
{
	DrawAxis(hMemDC);
	DrawGraph(hMemDC);
	DrawExpression(hMemDC);
	DrawLocation(hMemDC);
	DrawClearMessage(hMemDC);
}



void DrawAxis(HDC hMemDC)
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


void DrawGraph(HDC hMemDC)
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
		INT id;
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
				id = 8 + x - y * 4;
				DeleteObject(SelectObject(hMemDC,
					CreatePen(PS_SOLID, 4,
						id <= problem_reached / 12 ? 0x00FFFF : 0x808080
					)
				));
				DeleteObject(SelectObject(hMemDC, CreateSolidBrush(
					(8 + x - y * 4 == problem_temp / 12 ? 0x40 : 0x20)
					* (id <= problem_reached / 12 ? 0x000101 : 0x010101)
				)));
				d = pow(2,
					1 / (
						(x * 2 - 3 - a) * (x * 2 - 3 - a) +
						(y * 2 - 2 - b) * (y * 2 - 2 - b) + 1
					)
				) * 0.8;
				sRectangle(hMemDC, (x - 1.5) * 2, (y - 1.0) * 2, d, d);
				switch (id <= problem_latest / 12 ? id : -1) {
				case -1:
					sSegment(hMemDC, x, y, d, 0, 2, 2, 2);
					sSegment(hMemDC, x, y, d, 2, 1, 2, 2);
					sSegment(hMemDC, x, y, d, 2, 1, 1, 1);
					sSegment(hMemDC, x, y, d, 1, 0, 2, 0);
					break;
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
		INT id;
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

		SetTextAlign(hMemDC, TA_CENTER | TA_BOTTOM);
		for (INT y = 0; y < 3; y++) {
			for (INT x = 0; x < 4; x++) {
				id = 8 + x - y * 4;
				DeleteObject(SelectObject(hMemDC,
					CreatePen(PS_SOLID, 4,
						problem_temp / 12 < problem_reached / 12 || id <= problem_reached % 12 ? 0x00FFFF : 0x808080
					)
				));
				DeleteObject(SelectObject(hMemDC, CreateSolidBrush(
					(id == problem_temp % 12 ? 0x40 : 0x20)
					* (problem_temp / 12 * 12 + id <= problem_reached ? 0x000101 : 0x010101)
				)));
				d = pow(2,
					1 / (
						(x * 2 - 3 - a) * (x * 2 - 3 - a) +
						(y * 2 - 2 - b) * (y * 2 - 2 - b) + 1
						)
				) * 0.8;
				sRectangle(hMemDC, (x - 1.5) * 2, (y - 1.0) * 2, d, d);

				DeleteObject(SetFont(hMemDC, gRtoI_x(d * 0.8) - gRtoI_x(0),
					problem_temp / 12 < problem_reached / 12 || id <= problem_reached % 12 ? 0x00FFFF : 0x808080,
				0));
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
		Y_MAX = pane.height + 5;
		Y_MIN = -5;
		INT X, Y;
		PROBLEM* p = &problems[problem_crnt];
		double tmp;
		if (points_arr == NULL) return;
		
		DeleteObject(SelectObject(hMemDC, GetStockObject(NULL_PEN)));
		DeleteObject(SelectObject(hMemDC, CreateSolidBrush(0x00FFFF)));

		// 接線のグラフ
		for (INT t = 0; t < p->tcount; t++) {
			points_count = 0;
			Curve(
				CalcTang, t,
				gItoR_x(pane.lWidth), CalcTang(t, gItoR_x(pane.lWidth), 0),
				gItoR_x(pane.width), CalcTang(t, gItoR_x(pane.width), 0)
			);
			for (INT i = 0; i < points_count - 1; i++) {
				for (INT j = i + 1; j < points_count; j++) {
					if (points_arr[j][0] < points_arr[i][0]) {
						tmp = points_arr[i][0];
						points_arr[i][0] = points_arr[j][0];
						points_arr[j][0] = tmp;
						tmp = points_arr[i][1];
						points_arr[i][1] = points_arr[j][1];
						points_arr[j][1] = tmp;
					}
				}
			}
			for (INT i = 0; i < points_count; i++) {
				X = gRtoI_x(points_arr[i][0]);
				if (i % 50 < 20)continue;
				Y = gRtoI_y(points_arr[i][1]);
				Ellipse(
					hMemDC, X - 2, Y - 2, X + 2, Y + 2
				);
			}
		}
		// 目的のグラフ
		DeleteObject(SelectObject(hMemDC, CreateSolidBrush(0x006060)));
		if (!p->hide) {
			points_count = 0;
			Curve(
				CalcGoal, 0,
				gItoR_x(pane.lWidth - 5), CalcGoal(0, gItoR_x(pane.lWidth - 5), 0),
				gItoR_x(pane.width + 5), CalcGoal(0, gItoR_x(pane.width + 5), 0)
			);
			for (INT i = 0; i < points_count - 1; i++) {
				for (INT j = i + 1; j < points_count; j++) {
					if (points_arr[j][0] < points_arr[i][0]) {
						tmp = points_arr[i][0];
						points_arr[i][0] = points_arr[j][0];
						points_arr[j][0] = tmp;
						tmp = points_arr[i][1];
						points_arr[i][1] = points_arr[j][1];
						points_arr[j][1] = tmp;
					}
				}
			}
			for (INT i = 0; i < points_count; i++) {
				X = gRtoI_x(points_arr[i][0]);
				if (i % 50 < 20)continue;
				Y = gRtoI_y(points_arr[i][1]);
				Ellipse(
					hMemDC, X - 2, Y - 2, X + 2, Y + 2
				);
			}
		}

		// 点
		DeleteObject(SelectObject(hMemDC, CreatePen(PS_SOLID, 4, 0x00FFFF)));
		DeleteObject(SelectObject(hMemDC, GetStockObject(NULL_BRUSH)));
		for (INT pt = 0; pt < p->pcount; pt++) {
			X = gRtoI_x(p->points[pt]);
			Y = gRtoI_y(CalcGoal(0, p->points[pt], 0));
			Ellipse(
				hMemDC, X - 5, Y - 5, X + 5, Y + 5
			);
		}

		// 操作するグラフ
		DeleteObject(SelectObject(hMemDC, GetStockObject(NULL_PEN)));
		DeleteObject(SelectObject(hMemDC, CreateSolidBrush(0x00FFFF)));
		points_count = 0;
		Curve(
			CalcMain, 0,
			gItoR_x(pane.lWidth - 5), CalcMain(0, gItoR_x(pane.lWidth - 5), 0),
			gItoR_x(pane.width + 5), CalcMain(0, gItoR_x(pane.width + 5), 0)
		);
		for (INT i = 0; i < points_count; i++) {
			X = gRtoI_x(points_arr[i][0]);
			Y = gRtoI_y(points_arr[i][1]);
			if (Y < -10 || pane.height + 10 < Y) continue;
			Rectangle(
				hMemDC, X - 3, Y - 3, X + 3, Y + 3
			);
		}

		DeleteObject(SelectObject(hMemDC, GetStockObject(NULL_BRUSH)));
		//DeleteObject(SelectObject(hMemDC, GetStockObject(NULL_PEN)));
		break;
	}
	}
}


void DrawExpression(HDC hMemDC)
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


void DrawLocation(HDC hMemDC)
{
	SetTextAlign(hMemDC, TA_LEFT | TA_BOTTOM);
	SetBkMode(hMemDC, OPAQUE);
	DeleteObject(SetFont(hMemDC, 20, 0x00FFFF, 0x000000));
	switch (scene) {
	case SCENE_TITLE:
	{
		TextOut(hMemDC, pane.lWidth + 10, pane.height - 10, L"TITLE", 5);
		break;
	}
	case SCENE_STAGES:
	{
		TextOut(hMemDC, pane.lWidth + 10, pane.height - 10, L"STAGE SELECT", 12);
		break;
	}
	case SCENE_LEVELS:
	{
		TextOut(hMemDC, pane.lWidth + 10, pane.height - 10, L"LEVEL SELECT", 12);
		break;
	}
	case SCENE_PROBLEM:
	{
		WCHAR p_name[10];
		wsprintf(p_name, L"%X - %X", problem_crnt / 12 + 1, problem_crnt % 12 + 1);
		TextOut(hMemDC, pane.lWidth + 10, pane.height - 10, p_name, lstrlen(p_name));
		break;
	}
	DeleteObject(SelectObject(hMemDC, GetStockObject(SYSTEM_FONT)));
	}
}


void DrawMessage(HDC hMemDC, WCHAR str[])
{

	SetTextAlign(hMemDC, TA_CENTER | TA_BOTTOM);
	SetBkMode(hMemDC, TRANSPARENT);
	DeleteObject(SetFont(hMemDC, 100, 0xE0E0E0, 0x000000));
	TextOut(hMemDC, pane.lWidth + pane.rWidth / 2, pane.height / 2 + 50, str, lstrlen(str));
	DeleteObject(SelectObject(hMemDC, GetStockObject(SYSTEM_FONT)));
}


void DrawClearMessage(HDC hMemDC)
{
	if (clear == 1) {
		DrawMessage(hMemDC, L"CLEAR");
	}
}


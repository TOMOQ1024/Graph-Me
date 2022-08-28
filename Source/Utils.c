#include "Utils.h"





double median(double x, double y, double z)
{
	return x < y ? y < z ? y : z : z < x ? z : x;
}

double DistanceSq(double x0, double y0, double x1, double y1)
{
	return (x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0);
}

double Ease(double t, double a, double b, double c)
{
	if (t < 0 || 2 < t) return 0;
	if (t < 1) return a + (b - a) / 2 * (1 - cos(M_PI * t));
	return b + (c - b) / 2 * (1 + cos(M_PI * t));
}

BOOL IsIn(INT x, INT y, const RECT rc)
{
	BOOL L = rc.left <= x;
	BOOL T = rc.top <= y;
	BOOL R = x < rc.right;
	BOOL B = y < rc.bottom;
	return L && T && R && B;
}



double sItoR(INT i)
{
	if (i == 0)return 0;
	return i % 100 ? i : i / 100.0 * M_PI;
}

void sItoWS(INT i, WCHAR* str)
{
	if (i == 0) wsprintf(str, L"0");
	wsprintf(str, L"%d%s", i, i % 100 ? L"" : L"ƒÎ");
}

INT gRtoI_x(double x)
{
	return (INT)(pane.lWidth + pane.paddingX + (graph.x0 + x * graph.scale) * pane.radius * 2);
}

INT gRtoI_y(double y)
{
	return (INT)(pane.paddingY + (graph.y0 - y * graph.scale) * pane.radius * 2);
}

double gItoR_x(INT x)
{
	return ((x - pane.lWidth - pane.paddingX) / 2.0 / pane.radius - graph.x0) / graph.scale;
}

double gItoR_y(INT y)
{
	return -((y - pane.paddingY) / 2.0 / pane.radius - graph.y0) / graph.scale;
}
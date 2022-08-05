#include "Graph Me.h"

void OnMouseMove(INT x, INT y)
{
	OnMouseMove_Slider(x, y);
}

void OnLButtonDown(INT x, INT y)
{
	//
	OnLButtonDown_Slider(x, y);
}

void OnLButtonUp(INT x, INT y)
{
	//
	OnLButtonUp_Slider(x, y);
}




BOOL IsIn(INT x, INT y, const RECT rc)
{
	BOOL L = rc.left <= x;
	BOOL T = rc.top <= y;
	BOOL R = x < rc.right;
	BOOL B = y < rc.bottom;
	return L && T && R && B;
}

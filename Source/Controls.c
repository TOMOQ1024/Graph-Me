#include "Controls.h"
#include "Slider.h"
#include "Button.h"

void OnMouseMove(INT x, INT y)
{
	OnMouseMove_Slider(x, y);
	OnMouseMove_Button(x, y);
}

void OnLButtonDown(INT x, INT y)
{
	//
	OnLButtonDown_Slider(x, y);
	OnLButtonDown_Button(x, y);
}

void OnLButtonUp(INT x, INT y)
{
	//
	OnLButtonUp_Slider(x, y);
	OnLButtonUp_Button(x, y);
}

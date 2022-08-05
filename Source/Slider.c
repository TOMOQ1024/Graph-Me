#include "Graph Me.h"

void SetSliders() {
	for (int i = 0; i < 4; i++) {
		sliders[i].id = i;
		sliders[i].min = 0;
		sliders[i].max = 1;
		sliders[i].value = 0.5;
		sliders[i].scale = 0;
		sliders[i].mHover = FALSE;
		sliders[i].mDrag = FALSE;
		sliders[i].length = ctrl_pane.lWidth - 130;
	}
}

double GetProportion(const SLIDER *slider) {
	return slider->value / (slider->max - slider->min);
}

void GetSliderRect(const SLIDER* slider, RECT* rect)
{
	INT x = (INT)(GetProportion(slider) * (ctrl_pane.lWidth - 120)) + 60;
	INT y = slider->id * 80 + 45;
	rect->left = x - 10;
	rect->top = y - 20;
	rect->right = x + 10;
	rect->bottom = y + 20;
}

void OnMouseMove_Slider(INT x, INT y)
{
	RECT rc;
	for (INT i = 0; i < 4; i++) {
		GetSliderRect(&sliders[i], &rc);
		if (sliders[i].mDrag) {
			sliders[i].value = (sliders[i].max - sliders[i].min) * (x - (ctrl_pane.lWidth / 2.0 - sliders[i].length / 2.0)) / sliders[i].length + sliders[i].min;
			sliders[i].value = median(0, sliders[i].value, 1);
		}
		else {
			if (IsIn(x, y, rc)) {
				sliders[i].mHover = TRUE;
			}
			else {
				sliders[i].mHover = FALSE;
			}
		}
	}
}

void OnLButtonDown_Slider(INT x, INT y)
{
	RECT rc;
	for (INT i = 0; i < 4; i++) {
		GetSliderRect(&sliders[i], &rc);
		if (sliders[i].mHover && IsIn(x, y, rc)) {
			sliders[i].mDrag = TRUE;
		}
	}
}

void OnLButtonUp_Slider(INT x, INT y)
{
	for (INT i = 0; i < 4; i++) {
		sliders[i].mDrag = FALSE;
	}
}

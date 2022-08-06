#include "Slider.h"



void InitSliders(void) {
	for (int i = 0; i < 4; i++) {
		sliders[i].id = i;
		sliders[i].active = i < 3;////////////////////////////
		sliders[i].min = 0;
		sliders[i].max = 1;
		sliders[i].value = 0.5;
		sliders[i].scale = 0;
		sliders[i].mHover = FALSE;
		sliders[i].mDrag = FALSE;
		sliders[i].length = pane.lWidth - 140;
		sliders[i].width = 20;
		sliders[i].height = 40;
	}
}

double GetProportion(const SLIDER *slider) {
	return slider->value / (slider->max - slider->min);
}

void GetSliderRect(const SLIDER* slider, RECT* rect)
{
	INT x = GetProportion(slider) * slider->length + pane.lWidth / 2.0 - slider->length / 2.0;
	INT y = slider->id * 80 + 45;
	rect->left = x - slider->width / 2;
	rect->top = y - slider->height / 2;
	rect->right = x + slider->width / 2;
	rect->bottom = y + slider->height / 2;
}

void OnMouseMove_Slider(INT x, INT y)
{
	RECT rc;
	for (INT i = 0; i < 4; i++) {
		GetSliderRect(&sliders[i], &rc);
		if (sliders[i].mDrag) {
			sliders[i].value = (sliders[i].max - sliders[i].min) * (x - (pane.lWidth / 2.0 - sliders[i].length / 2.0)) / sliders[i].length + sliders[i].min;
			sliders[i].value = median(0, sliders[i].value, 1);
		}
		else {
			if (sliders[i].active && IsIn(x, y, rc)) {
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

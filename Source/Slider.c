#include "Slider.h"



void InitSliders(void) {
	for (int i = 0; i < 4; i++) {
		sliders[i].id = i;
		sliders[i].active = TRUE;
		sliders[i].min = 0;
		sliders[i].max = 1;
		lstrcpy(sliders[i].min_s, TEXT("0"));
		lstrcpy(sliders[i].max_s, TEXT("1"));
		sliders[i].value = 0.5;
		sliders[i].scale = 0;
		sliders[i].mHover = FALSE;
		sliders[i].mDrag = FALSE;
		sliders[i].length = pane.lWidth - 140;
		sliders[i].width = 20;
		sliders[i].height = 40;
	}
}

void SetSliders(const PROBLEM* p)
{
	INT d0, d;
	TCHAR sgn = 0;
	TCHAR cst = 0;
	for (int i = 0; i < 4; i++) {
		sliders[i].active = p->active[i];
		sliders[i].value = p->value[i];
		sliders[i].scale = p->scale[i];

		// min
		if (p->min[i] != 0) {
			d0 = p->min[i];
			if (p->min[i] < 0) {
				sgn = L'-';
				d0 *= -1;
			}
			if (d0 % 100) {
				d = d0;
			}
			else {
				d = d0 / 100;
				cst = L'ƒÎ';
			}
		}
		else {
			d = 0;
		}
		sliders[i].min = d * (cst ? M_PI : 1);
		wsprintf(sliders[i].min_s, L"%c%d%c", sgn, d, cst);

		// max
		sgn = 0;
		cst = 0;
		if (p->max[i] != 0) {
			d0 = p->max[i];
			if (p->max[i] < 0) {
				sgn = L'-';
				d0 *= -1;
			}
			if (d0 % 100) {
				d = d0;
			}
			else {
				d = d0 / 100;
				cst = L'ƒÎ';
			}
		}
		else {
			d = 0;
		}
		sliders[i].max = d * (cst ? M_PI : 1);
		wsprintf(sliders[i].max_s, L"%c%d%c", sgn, d, cst);
	}
}

double GetProportion(const SLIDER *slider)
{
	return (slider->value - slider->min) / (slider->max - slider->min);
}

void GetSliderRect(const SLIDER* slider, RECT* rect)
{
	INT x = (INT)(GetProportion(slider) * slider->length + pane.lWidth / 2.0 - slider->length / 2.0);
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
			sliders[i].value = median(sliders[i].min, sliders[i].value, sliders[i].max);
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

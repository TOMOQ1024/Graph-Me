#include "Slider.h"
#include "Button.h"
#include "Utils.h"



void SetScene(SCENE s)
{

	InitSliders();

	InitButtons();

	scene = s;
	switch (s) {
	case SCENE_TITLE:
	{
		sliders[2].active = TRUE;
		sliders[2].min = 0;
		sliders[2].max = 2;
		lstrcpy(sliders[2].min_s, TEXT("0"));
		lstrcpy(sliders[2].max_s, TEXT("2"));
		sliders[2].value = 0.5;

		graph.x0 = 0.5;
		graph.y0 = 0.5;
		graph.scale = 0.11;
		break;
	}
	case SCENE_STAGES:
	{
		sliders[0].active = TRUE;
		sliders[1].active = TRUE;

		sliders[0].min = -3;
		sliders[0].max = 3;
		lstrcpy(sliders[0].min_s, TEXT("-3"));
		lstrcpy(sliders[0].max_s, TEXT("3"));
		sliders[0].value = 2 * (problem_crnt / 12 % 4) - 3;

		sliders[1].min = -2;
		sliders[1].max = 2;
		lstrcpy(sliders[1].min_s, TEXT("-2"));
		lstrcpy(sliders[1].max_s, TEXT("2"));
		sliders[1].value = 2 - 2 * (problem_crnt / 12 / 4);

		graph.x0 = 0.5;
		graph.y0 = 0.5;
		graph.scale = 0.11;

		buttons[0].active = TRUE;
		buttons[1].active = TRUE;
		buttons[2].active = TRUE;
		break;
	}
	case SCENE_LEVELS:
	{
		sliders[0].active = TRUE;
		sliders[1].active = TRUE;

		sliders[0].min = -3;
		sliders[0].max = 3;
		lstrcpy(sliders[0].min_s, TEXT("-3"));
		lstrcpy(sliders[0].max_s, TEXT("3"));
		sliders[0].value = 2 * (problem_crnt % 4) - 3;

		sliders[1].min = -2;
		sliders[1].max = 2;
		lstrcpy(sliders[1].min_s, TEXT("-2"));
		lstrcpy(sliders[1].max_s, TEXT("2"));
		sliders[1].value = 2 - 2 * (problem_crnt % 12 / 4);

		graph.x0 = 0.5;
		graph.y0 = 0.5;
		graph.scale = 0.11;

		buttons[0].active = TRUE;
		buttons[1].active = TRUE;
		buttons[2].active = TRUE;
		break;
	}
	case SCENE_PROBLEM:
	{
		PROBLEM* p = &problems[problem_crnt];
		if (p->type == PTY_NULL) {
			SetScene(SCENE_TITLE);
			return;
		}
		for (INT i = 0; i < p->vcount; i++) {
			// min value max vscale answer
			sliders[i].active = TRUE;
			sliders[i].min = sItoR(p->min[i]);
			sliders[i].max = sItoR(p->max[i]);
			sItoWS(p->min[i], sliders[i].min_s);
			sItoWS(p->max[i], sliders[i].max_s);
			sliders[i].value = p->value[i];
			sliders[i].scale = p->vscale[i];
		}

		SetCalcs();

		wsprintf(graph.ex, L"y=%s", p->fstr);

		graph.x0 = p->x0;
		graph.y0 = p->y0;
		graph.scale = p->gscale;

		buttons[0].active = TRUE;
		buttons[1].active = TRUE;
		buttons[2].active = TRUE;
		break;
	}
	}
}

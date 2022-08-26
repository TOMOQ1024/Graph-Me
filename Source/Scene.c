#include "Scene.h"
#include "Slider.h"
#include "Button.h"
#include "Graph.h"

void SetScene(INT s)
{

	InitSliders();

	InitButtons();

	scene = s;
	switch (s) {
	case SCENE_TITLE:
	{
		sliders[0].active = FALSE;
		sliders[1].active = FALSE;
		sliders[2].active = TRUE;
		sliders[3].active = FALSE;
		sliders[2].min = 0;
		sliders[2].max = 2;
		lstrcpy(sliders[2].min_s, TEXT("0"));
		lstrcpy(sliders[2].max_s, TEXT("2"));
		sliders[2].value = 0.5;

		graph.x0 = 0.5;
		graph.y0 = 0.5;
		graph.scale = 0.11;

		buttons[0].active = TRUE;
		buttons[1].active = FALSE;
		buttons[2].active = TRUE;
		break;
	}
	case SCENE_STAGES:
	{
		sliders[0].active = TRUE;
		sliders[1].active = TRUE;
		sliders[2].active = FALSE;
		sliders[3].active = FALSE;

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
		sliders[2].active = FALSE;
		sliders[3].active = FALSE;

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
		buttons[0].active = TRUE;
		buttons[1].active = TRUE;
		buttons[2].active = TRUE;
		break;
	}
	}
}

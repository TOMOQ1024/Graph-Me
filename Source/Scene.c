#include "Scene.h"
#include "Slider.h"
#include "Graph.h"

void SetScene(INT s)
{
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
	}
	case SCENE_STAGES:
	{
		sliders[0].active = TRUE;
		sliders[1].active = TRUE;
		sliders[2].active = FALSE;
		sliders[3].active = FALSE;

		sliders[0].min = 0;
		sliders[0].max = pane.width;
		lstrcpy(sliders[0].min_s, TEXT("0"));
		lstrcpy(sliders[0].max_s, TEXT("W"));
		sliders[0].value = pane.width / 2;

		sliders[1].min = 0;
		sliders[1].max = pane.height;
		lstrcpy(sliders[1].min_s, TEXT("0"));
		lstrcpy(sliders[1].max_s, TEXT("H"));
		sliders[1].value = pane.height / 2;

		graph.x0 = 0.5;
		graph.y0 = 0.5;
		graph.scale = 0.11;
	}
	}
}
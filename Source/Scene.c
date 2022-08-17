#include "Scene.h"
#include "Slider.h"
#include "Graph.h"

void SetScene(INT s)
{
	scene = s;
	if (s == SCENE_TITLE) {
		sliders[0].active = FALSE;
		sliders[1].active = FALSE;
		sliders[2].active = TRUE;
		sliders[3].active = FALSE;
		sliders[2].min = 0;
		sliders[2].max = 2;
		sliders[2].value = 0.5;

		graph.x0 = 0.5;
		graph.y0 = 0.5;
		graph.scale = 0.11;
	}
}
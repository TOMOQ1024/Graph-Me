#include "Graph Me.h"

void SetSliders() {
	for (int i = 0; i < 4; i++) {
		sliders[i].min = 0;
		sliders[i].max = 1;
		sliders[i].value = 0.5;
	}
}

double GetProportion(struct SLIDER slider) {
	return slider.value / (slider.max - slider.min);
}

#include "Button.h"
#include "Utils.h"

void InitButtons(void)
{
	for (INT i = 0; i < 3; i++) {
		buttons[i].id = i;
		buttons[i].active = FALSE;
		buttons[i].mHover = FALSE;
		buttons[i].mLDown = FALSE;
		buttons[i].width = (INT)(pane.lWidth / 3.0) - 20;
		buttons[i].height = 40;
	}
}

void SetButtons(void)
{
	switch (scene) {
	case SCENE_TITLE:
		buttons[2].active = fabs(sliders[2].value - round(sliders[2].value)) < 0.2;
		break;
	}
}

void GetButtonRect(const BUTTON* button, RECT* rect)
{
	// pane.lWidth / 3 * i + 10, height - 50, pane.lWidth / 3 * (i + 1) - 10, height - 10
	INT x = (INT)(pane.lWidth / 6.0 * (button->id * 2 + 1));
	INT y = pane.height - 30;
	rect->left = x - button->width / 2;
	rect->top = y - button->height / 2;
	rect->right = x + button->width / 2;
	rect->bottom = y + button->height / 2;
}



void OnMouseMove_Button(INT x, INT y)
{
	RECT rc;
	for (INT i = 0; i < 3; i++) {
		GetButtonRect(&buttons[i], &rc);
		if (buttons[i].active && IsIn(x, y, rc)) {
			buttons[i].mHover = TRUE;
		}
		else {
			buttons[i].mHover = FALSE;
		}
	}
	SetButtons();
}

void OnLButtonDown_Button(INT x, INT y)
{
	RECT rc;
	for (INT i = 0; i < 3; i++) {
		GetButtonRect(&buttons[i], &rc);
		if (buttons[i].mHover && IsIn(x, y, rc)) {
			buttons[i].mLDown = TRUE;
			switch (i) {
			case 0:// PREV
				switch (scene) {
				case SCENE_STAGES:
					SetScene(SCENE_TITLE);
					break;
				case SCENE_LEVELS:
					SetScene(SCENE_STAGES);
					break;
				case SCENE_PROBLEM:
					SetScene(SCENE_LEVELS);
					break;
				}
				break;
			case 1:// RESET
				switch (scene) {
				case SCENE_STAGES:
					if (problem_crnt != problem_temp)problem_temp = problem_crnt;
					else problem_crnt = 0;
					SetScene(SCENE_STAGES);
					break;
				case SCENE_LEVELS:
					if (problem_crnt != problem_temp)problem_temp = problem_crnt;
					else problem_crnt = problem_crnt / 12 * 12;
					SetScene(SCENE_LEVELS);
					break;
				case SCENE_PROBLEM:
					SetScene(SCENE_PROBLEM);
					break;
				}
				break;
			case 2:// NEXT
				switch (scene) {
				case SCENE_TITLE:
					switch ((INT)round(sliders[2].value)) {
					case 0:// EXIT
						PostQuitMessage(0);
						return;
					case 1:// SETTINGS
						break;
					case 2:// PLAY
						SetScene(SCENE_STAGES);
						break;
					}
					break;
				case SCENE_STAGES:
					if (problem_crnt / 12 != problem_temp / 12)problem_crnt = problem_temp;
					SetScene(SCENE_LEVELS);
					break;
				case SCENE_LEVELS:
					problem_crnt = problem_temp;
					SetScene(SCENE_PROBLEM);
					break;
				case SCENE_PROBLEM:
					problem_crnt++;
					SetScene(SCENE_PROBLEM);
					break;
				}
				break;
			}
		}
	}
	OnMouseMove_Button(x, y);
}

void OnLButtonUp_Button(INT x, INT y)
{
	for (INT i = 0; i < 3; i++) {
		buttons[i].mLDown = FALSE;
	}
	OnMouseMove_Button(x, y);
}
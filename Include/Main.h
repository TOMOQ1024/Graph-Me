#pragma once

#define _USE_MATH_DEFINES

#include "framework.h"
#include "resource.h"
#include <math.h>



// �X�^�b�N�ɑ΂��閽��
typedef enum {
	SCENE_TITLE,
	SCENE_SETTINGS,
	SCENE_STAGES,
	SCENE_LEVELS,
	SCENE_PROBLEM,
} SCENE;

// �y�C���\����
typedef struct tagPANE {
	INT lWidth;
	INT rWidth;
	INT width;
	INT height;
	INT radius;
	INT paddingX;
	INT paddingY;
	BOOL mHover;
	BOOL mDrag;
} PANE;
PANE pane;


// �X���C�_�[�\����
typedef struct tagSLIDER {
	INT id;
	BOOL active;
	double min;
	double max;
	TCHAR min_s[8];
	TCHAR max_s[8];
	double value;
	double scale;
	BOOL mHover;
	BOOL mDrag;
	INT length;
	INT width;
	INT height;
} SLIDER;
// a, b, c, d �̃X���C�_�[
SLIDER sliders[4];


// �{�^���\����
typedef struct tagBUTTON {
	INT id;
	BOOL active;
	BOOL mHover;
	BOOL mLDown;
	INT width;
	INT height;
} BUTTON;
// PREV, RESET, NEXT
BUTTON buttons[3];


// �O���t�\����
typedef struct tagGRAPH {
	double x0;
	double y0;
	double scale;
	WCHAR ex[100];
} GRAPH;

GRAPH graph;



// ���^
typedef enum {
	PTY_NULL,
	PTY_EXPLICIT,
} ProblemType;
// ���\����
typedef struct tagPROBLEM {
	ProblemType type;
	double x0;
	double y0;
	double gscale;
	WCHAR fstr[30];
	INT vcount;
	INT min[4];
	INT max[4];
	double value[4];
	INT vscale[4];
	double answer[4];
} PROBLEM;
// �t�@�C������ǂݎ����̃f�[�^
PROBLEM problems[146];

INT problem_crnt;
INT problem_temp;

// ���\�[�X�̓ǂݍ���
void LoadProblemData(void);

void LoadProblem(PROBLEM* p);

double Calc(double x, double a, double b, double c, double d);



SCENE scene;

void SetScene(SCENE s);


// �S�Ă̕`��
void Draw(HDC hdc, HDC hMemDC, INT mx, INT my);




// 3�ϐ��̒����l�֐�
double median(double x, double y, double z);

// ��Ԋ֐�
double Ease(double t, double a, double b, double c);

// 2�_�Ԃ̋���
double DistanceSq(double x0, double y0, double x1, double y1);

// ��`���� (x,y) �����݂��邩
BOOL IsIn(INT x, INT y, const RECT rc);



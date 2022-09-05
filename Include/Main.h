#pragma once

#define _USE_MATH_DEFINES

#include "framework.h"
#include "resource.h"
#include <math.h>



// �V�[��
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


// �O���t�\����
typedef struct tagGRAPH {
	double x0;
	double y0;
	double scale;
	WCHAR ex[100];
} GRAPH;

// ���^
typedef enum {
	PTY_NULL,
	PTY_EXPLICIT,
} ProblemType;
// ���\����
typedef struct tagPROBLEM {
	ProblemType type;
	BOOL hide;
	double x0;
	double y0;
	double gscale;
	WCHAR fstr[30];
	INT tcount;
	INT pcount;
	INT vcount;
	INT min[4];
	INT max[4];
	double tangent[8];
	double points[8];
	double value[4];
	double vscale[4];
	double answer[4];
} PROBLEM;



// ���\�[�X�̓ǂݍ���
void LoadProblemData(void);

// ���̃��[�h
void SetCalcs(void);

// �ǂݍ��񂾊֐��̎��s
double CalcMain(INT id, double x, double y);
double CalcGoal(INT id, double x, double y);
double CalcTang(INT id, double x, double y);



// �V�[���ݒ�
void SetScene(SCENE s);

// �S�Ă̕`��
void Draw(HDC hdc, HDC hMemDC);







/*      �O���[�o���ϐ�       */
extern SCENE scene;
extern PANE pane;
extern GRAPH graph;
extern SLIDER sliders[4];
extern BUTTON buttons[3];
extern PROBLEM problems[146];// �t�@�C������ǂݎ����̃f�[�^
extern INT problem_crnt;
extern INT problem_temp;
extern INT problem_latest;
extern double(*points_arr)[2];
extern INT points_count;
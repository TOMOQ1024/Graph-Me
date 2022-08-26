#pragma once

#define _USE_MATH_DEFINES

#include "framework.h"
#include "resource.h"
#include <math.h>






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



// ���\����
typedef struct tagPROBLEM {
	INT id;
	INT type;
	double x0;
	double y0;
	BOOL active[4];
	INT min[4];
	INT max[4];
	double value[4];
	double scale[4];
	double answer[4];
} PROBLEM;
// �t�@�C������ǂݎ����̃f�[�^
PROBLEM problems[146];

DWORD problem_data_size;
const char* problem_data;

INT problem_crnt;
INT problem_temp;

void LoadProblem(void);

double Calc(double x, double a, double b, double c, double d);



// 3�ϐ��̒����l�֐�
double median(double x, double y, double z);

// ��Ԋ֐�
double Ease(double t, double a, double b, double c);

// ��`���� (x,y) �����݂��邩
BOOL IsIn(INT x, INT y, const RECT rc);



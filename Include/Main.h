#pragma once

#define _USE_MATH_DEFINES

#include "framework.h"
#include "resource.h"
#include <math.h>






// ペイン構造体
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



// ボタン構造体
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



// 問題構造体
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
// ファイルから読み取る問題のデータ
PROBLEM problems[146];

DWORD problem_data_size;
const char* problem_data;

INT problem_crnt;
INT problem_temp;

void LoadProblem(void);

double Calc(double x, double a, double b, double c, double d);



// 3変数の中央値関数
double median(double x, double y, double z);

// 補間関数
double Ease(double t, double a, double b, double c);

// 矩形内に (x,y) が存在するか
BOOL IsIn(INT x, INT y, const RECT rc);



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



// グラフ構造体
typedef struct tagGRAPH {
	double x0;
	double y0;
	double scale;
	WCHAR ex[100];
} GRAPH;

GRAPH graph;



// 問題型
typedef enum {
	PTY_NULL,
	PTY_EXPLICIT,
} ProblemType;
// 問題構造体
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
// ファイルから読み取る問題のデータ
PROBLEM problems[146];

INT problem_crnt;
INT problem_temp;

// リソースの読み込み
void LoadProblemData(void);

void LoadProblem(PROBLEM* p);

double Calc(double x, double a, double b, double c, double d);



// 3変数の中央値関数
double median(double x, double y, double z);

// 補間関数
double Ease(double t, double a, double b, double c);

// 2点間の距離
double DistanceSq(double x0, double y0, double x1, double y1);

// 矩形内に (x,y) が存在するか
BOOL IsIn(INT x, INT y, const RECT rc);



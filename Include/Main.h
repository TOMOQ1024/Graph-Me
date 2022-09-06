#pragma once

#define _USE_MATH_DEFINES

#include "framework.h"
#include "resource.h"
#include <math.h>



// シーン
typedef enum {
	SCENE_TITLE,
	SCENE_SETTINGS,
	SCENE_STAGES,
	SCENE_LEVELS,
	SCENE_PROBLEM,
} SCENE;

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


// スライダー構造体
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
// a, b, c, d のスライダー


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


// グラフ構造体
typedef struct tagGRAPH {
	double x0;
	double y0;
	double scale;
	WCHAR ex[100];
} GRAPH;

// 問題型
typedef enum {
	PTY_NULL,
	PTY_EXPLICIT,
} ProblemType;
// 問題構造体
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



// リソースの読み込み
void LoadProblemData(void);

// 問題のロード
void SetCalcs(void);

// 読み込んだ関数の実行
double CalcMain(INT id, double x, double y);
double CalcGoal(INT id, double x, double y);
double CalcTang(INT id, double x, double y);



// シーン設定
void SetScene(SCENE s);

// 全ての描画
void Draw(HDC hdc, HDC hMemDC);







/*      グローバル変数       */
extern SCENE scene;
extern PANE pane;
extern GRAPH graph;
extern SLIDER sliders[4];
extern BUTTON buttons[3];
extern PROBLEM problems[146];// ファイルから読み取る問題のデータ
extern INT problem_crnt;
extern INT problem_temp;
extern INT problem_latest;
extern double(*points_arr)[2];
extern INT points_count;
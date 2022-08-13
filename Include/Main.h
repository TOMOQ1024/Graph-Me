#pragma once

#include "framework.h"
#include "resource.h"



INT scene;



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




// 3変数の中央値関数
double median(double x, double y, double z);

// 矩形内に (x,y) が存在するか
BOOL IsIn(INT x, INT y, const RECT rc);



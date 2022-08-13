#pragma once

#include "framework.h"
#include "resource.h"



INT scene;



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




// 3�ϐ��̒����l�֐�
double median(double x, double y, double z);

// ��`���� (x,y) �����݂��邩
BOOL IsIn(INT x, INT y, const RECT rc);



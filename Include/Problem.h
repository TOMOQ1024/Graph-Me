#pragma once

#include "Main.h"

// 問題構造体
typedef struct tagPROBLEM {
	INT id;
	INT active[4];
	INT min[4];
	INT max[4];
	double value[4];
	double scale[4];
} PROBLEM;
#pragma once

#include "Main.h"

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
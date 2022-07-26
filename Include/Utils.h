#pragma once

#include "Main.h"




// 3変数の中央値関数
double median(double x, double y, double z);

// 補間関数
double Ease(double t, double a, double b, double c);

// 2点間の距離
double DistanceSq(double x0, double y0, double x1, double y1);

// 矩形内に (x,y) が存在するか
BOOL IsIn(INT x, INT y, const RECT rc);




INT gRtoI_x(double x);
INT gRtoI_y(double y);
double gItoR_x(INT x);
double gItoR_y(INT x);

double sItoR(INT i);
void sItoWS(INT i, WCHAR* str);

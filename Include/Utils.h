#pragma once

#include "Main.h"




// 3�ϐ��̒����l�֐�
double median(double x, double y, double z);

// ��Ԋ֐�
double Ease(double t, double a, double b, double c);

// 2�_�Ԃ̋���
double DistanceSq(double x0, double y0, double x1, double y1);

// ��`���� (x,y) �����݂��邩
BOOL IsIn(INT x, INT y, const RECT rc);




INT gRtoI_x(double x);
INT gRtoI_y(double y);
double gItoR_x(INT x);
double gItoR_y(INT x);

double sItoR(INT i);
void sItoWS(INT i, WCHAR* str);

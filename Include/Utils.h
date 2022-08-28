#pragma once

#include "Main.h"




// 3•Ï”‚Ì’†‰›’lŠÖ”
double median(double x, double y, double z);

// •âŠÔŠÖ”
double Ease(double t, double a, double b, double c);

// 2“_ŠÔ‚Ì‹——£
double DistanceSq(double x0, double y0, double x1, double y1);

// ‹éŒ`“à‚É (x,y) ‚ª‘¶İ‚·‚é‚©
BOOL IsIn(INT x, INT y, const RECT rc);




INT gRtoI_x(double x);
INT gRtoI_y(double y);
double gItoR_x(INT x);
double gItoR_y(INT x);

double sItoR(INT i);
void sItoWS(INT i, WCHAR* str);

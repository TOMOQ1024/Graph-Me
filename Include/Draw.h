#pragma once

#include "Main.h"



// コントロールの描画
void DrawCtrl(HDC hdc, HDC hMemDC);





// 線分
void Segment(HDC hdc, double x0, double y0, double x1, double y1);
// タイトル用セグメント
void tSegment(HDC hdc, double x0, double y0, double X0, double Y0, double X1, double Y1);
// アニメーション付き線分
void mtSegment(
	HDC hdc, double t, double x0, double y0, INT xf0, INT yf0, INT xt0, INT yt0,
	INT xf1, INT yf1, INT xt1, INT yt1, INT xf2, INT yf2, INT xt2, INT yt2
);
// ステージ・レベル項目用矩形
void sRectangle(HDC hdc, double xc, double yc, double w, double h);
// ステージ項目用セグメント
void sSegment(HDC hdc, double xo, double yo, double d, INT x0, INT y0, INT x1, INT y1);



//
void Curve(double (*Calc)(INT, double, double), INT id, double x0, double y0, double x1, double y1);
// 軸,グラフ,数式の描画
void DrawMain(HDC hMemDC);
void DrawAxis(HDC hMemDC);
void DrawGraph(HDC hMemDC);
void DrawExpression(HDC hMemDC);
void DrawLocation(HDC hMemDC);
void DrawMessage(HDC hMemDC, WCHAR str[]);
void DrawClearMessage(HDC hMemDC);

// デバッグ情報の描画
void DrawDebug(HDC hdc, HDC hMemDC);

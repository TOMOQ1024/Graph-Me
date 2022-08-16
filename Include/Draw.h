#pragma once

#include "Main.h"

// 全ての描画
void Draw(HDC hdc, HDC hMemDC, INT mx, INT my);

// コントロールの描画
void DrawCtrl(HDC hdc, HDC hMemDC, INT mx, INT my);

// 線分
void Segment(HDC hdc, double x0, double y0, double x1, double y1);
// テキスト用セグメント
void tSegment(HDC hdc, double x0, double y0, double X0, double Y0, double X1, double Y1);
// アニメーション付き線分
void mtSegment(
	HDC hdc, double t, double x0, double y0, INT xf0, INT yf0, INT xt0, INT yt0,
	INT xf1, INT yf1, INT xt1, INT yt1, INT xf2, INT yf2, INT xt2, INT yt2
);

// 軸,グラフ,数式の描画
void DrawMain(HDC hdc, HDC hMemDC);
void DrawAxis(HDC hdc, HDC hMemDC);
void DrawGraph(HDC hdc, HDC hMemDC);
void DrawExpression(HDC hdc, HDC hMemDC);

// デバッグ情報の描画
void DrawDebug(HDC hdc, HDC hMemDC, INT mx, INT my);

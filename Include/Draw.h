#pragma once

#include "Main.h"

// 全ての描画
void Draw(HDC hdc, HDC hMemDC, INT mx, INT my);

// コントロールの描画
void DrawCtrl(HDC hdc, HDC hMemDC, INT mx, INT my);

// 軸,グラフ,数式の描画
void Segment(HDC hdc, double x0, double y0, double x1, double y1);
void tSegment(HDC hdc, INT x0, INT y0, INT X0, INT Y0, INT X1, INT Y1);
void DrawMain(HDC hdc, HDC hMemDC);
void DrawAxis(HDC hdc, HDC hMemDC);
void DrawGraph(HDC hdc, HDC hMemDC);
void DrawExpression(HDC hdc, HDC hMemDC);

// デバッグ情報の描画
void DrawDebug(HDC hdc, HDC hMemDC, INT mx, INT my);

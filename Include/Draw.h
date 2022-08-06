#pragma once

#include "Main.h"

// 全ての描画
void Draw(HDC hdc, HDC hMemDC, INT mx, INT my);

// コントロールの描画
void DrawCtrl(HDC hdc, HDC hMemDC, INT mx, INT my);

// デバッグ情報の描画
void DrawDebug(HDC hdc, HDC hMemDC, INT mx, INT my);

#pragma once
#include "Main.h"



// フォントの設定, 戻り値は直前のフォントハンドル
HFONT SetFont(HDC hdc, INT nHeight, COLORREF textColor, COLORREF bkColor);
#include "Graph Me.h"

void SetFont(HDC hdc, INT nHeight, COLORREF textColor, COLORREF bkColor)
{
	HFONT hFont = CreateFont(
		nHeight, 0, 0, 0,
		FW_LIGHT, FALSE, FALSE, FALSE,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, VARIABLE_PITCH, NULL
	);
	SelectObject(hdc, hFont);
	SetTextColor(hdc, textColor);
	SetBkColor(hdc, bkColor);
}

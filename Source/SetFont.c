#include "Graph Me.h"

HFONT SetFont(HDC hdc, INT nHeight, COLORREF textColor, COLORREF bkColor)
{
	HFONT hOldFont;
	HFONT hFont = CreateFont(
		nHeight, 0, 0, 0,
		FW_LIGHT, FALSE, FALSE, FALSE,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, VARIABLE_PITCH, NULL
	);
	hOldFont = SelectObject(hdc, hFont);
	SetTextColor(hdc, textColor);
	SetBkColor(hdc, bkColor);

	return hOldFont;
}

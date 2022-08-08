﻿// Graph Me.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "Slider.h"
#include "Button.h"
#include "Draw.h"
#include "Controls.h"
//#include <math.h>

#define MAX_LOADSTRING 100

// グローバル変数:
HINSTANCE hInst;                                // 現在のインターフェイス
WCHAR szTitle[MAX_LOADSTRING];                  // タイトル バーのテキスト
WCHAR szWindowClass[MAX_LOADSTRING];            // メイン ウィンドウ クラス名

double median(double x, double y, double z)
{
    return x < y ? y < z ? y : z : z < x ? z : x;
}

extern PANE pane;
extern SLIDER sliders[4];
extern BUTTON buttons[3];
extern PROBLEM problems[144];

// カーソルの描画(没)
// http://nagoyacoder.web.fc2.com/win32api/mcursor.html
//INT cur_width;
//INT cur_height;
//INT cur_size;
//char* cur_and;
//char* cur_xor;

// このコード モジュールに含まれる関数の宣言を転送します:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // グローバル変数の初期化
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_GRAPHME, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // アプリケーション初期化の実行:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GRAPHME));

    MSG msg;

    // メイン メッセージ ループ:
    while (GetMessage(&msg, NULL, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  関数: MyRegisterClass()
//
//  目的: ウィンドウ クラスを登録します。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GRAPHME));
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = CreateSolidBrush(BLACK_BRUSH);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_GRAPHME);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   関数: InitInstance(HINSTANCE, int)
//
//   目的: インスタンス ハンドルを保存して、メイン ウィンドウを作成します
//
//   コメント:
//
//        この関数で、グローバル変数でインスタンス ハンドルを保存し、
//        メイン プログラム ウィンドウを作成および表示します。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // グローバル変数にインスタンス ハンドルを格納する

   HWND hWnd = CreateWindowW(
       szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL
   );
   //HWND hWnd = CreateWindowEx(
   //    WS_EX_COMPOSITED,
   //    szWindowClass, szTitle,
   //    WS_OVERLAPPEDWINDOW,
   //    CW_USEDEFAULT, 0,
   //    CW_USEDEFAULT, 0,
   //    NULL, NULL, hInstance, NULL
   //);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}



//
//  関数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: メイン ウィンドウのメッセージを処理します。
//
//  WM_COMMAND  - アプリケーション メニューの処理
//  WM_PAINT    - メイン ウィンドウを描画する
//  WM_DESTROY  - 中止メッセージを表示して戻る
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static INT mx, my;

    static HDC hdc;
    static HDC hMemDC;
    static HBITMAP hBMP;
    static HBITMAP hOldBMP;

    switch (message)
    {
    case WM_CREATE:
    {
        hdc = GetDC(hWnd);
        hMemDC = CreateCompatibleDC(hdc);
        
        pane.lWidth = 300;
        pane.mHover = FALSE;
        pane.mDrag = FALSE;
        pane.width = LOWORD(lParam);
        pane.height = HIWORD(lParam);

        InitSliders();

        InitButtons();
    }
    case WM_SIZE:
    {
        pane.width = LOWORD(lParam);
        pane.height = HIWORD(lParam);
        //GetClientRect(hWnd, &client);
        hBMP = CreateCompatibleBitmap(hdc, pane.width, pane.height);
        hOldBMP = SelectObject(hMemDC, hBMP);
        if (hOldBMP) DeleteObject(hOldBMP);
        Draw(hdc, hMemDC, mx, my);
        break;
    }
    case WM_MOVE:
    {
        Draw(hdc, hMemDC, mx, my);
        break;
    }
    case WM_SETCURSOR:
    {
        if (buttons[0].mHover || buttons[1].mHover || buttons[2].mHover) {
            SetCursor(LoadCursor(NULL, IDC_HAND));
            break;
        }
        if (pane.mHover || sliders[0].mHover || sliders[1].mHover || sliders[2].mHover || sliders[3].mHover) {
            SetCursor(LoadCursor(NULL, IDC_SIZEWE));
            break;
        }
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    //case WM_PAINT:
    //{
    //    BitBlt(hdc, 0, 0, width, height, hMemDC, 0, 0, SRCCOPY);
    //    break;
    //}
    case WM_LBUTTONDOWN:
    {
        OnLButtonDown(LOWORD(lParam), HIWORD(lParam));
        pane.mDrag = FALSE;
        if (pane.mHover) {
            pane.mDrag = TRUE;
            //InvalidateRect(hWnd, NULL, FALSE);
        }
        Draw(hdc, hMemDC, mx, my);
        break;
    }
    case WM_LBUTTONUP:
    {
        OnLButtonUp(LOWORD(lParam), HIWORD(lParam));
        pane.mDrag = FALSE;
        Draw(hdc, hMemDC, mx, my);
        break;
    }
    case WM_MOUSEMOVE:
    {
        OnMouseMove(LOWORD(lParam), HIWORD(lParam));
        POINTS mousePos = MAKEPOINTS(lParam);
        mx = mousePos.x;
        my = mousePos.y;
        if (pane.mDrag) {
            pane.lWidth = 300 < mx ? mx : 300;

            for (INT i = 0; i < 4; i++) sliders[i].length = pane.lWidth - 120;
        }
        else if (abs((LONG)(mx - pane.lWidth)) < 3) {
            pane.mHover = TRUE;
        }
        else {
            pane.mHover = FALSE;
        }
        Draw(hdc, hMemDC, mx, my);
        break;
    }
    case WM_DESTROY:
        DeleteDC(hMemDC);
        DeleteDC(hdc);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
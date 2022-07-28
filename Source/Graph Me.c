// Graph Me.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "Graph Me.h"
#include <math.h>

#define MAX_LOADSTRING 100

// グローバル変数:
HINSTANCE hInst;                                // 現在のインターフェイス
WCHAR szTitle[MAX_LOADSTRING];                  // タイトル バーのテキスト
WCHAR szWindowClass[MAX_LOADSTRING];            // メイン ウィンドウ クラス名

extern struct SLIDER sliders[4];

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

    // TODO: ここにコードを挿入してください。

    // グローバル文字列を初期化する
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
    static UINT width = 0, height = 0, ctrl_width = 300;
    static INT mx, my;
    static BOOL flg0 = FALSE;
    static BOOL flg1 = FALSE;

    static HDC hdc;
    static HDC hMemDC;
    static HBITMAP hBMP;

    switch (message)
    {
    case WM_CREATE:
    {
        hdc = GetDC(hWnd);
        hMemDC = CreateCompatibleDC(hdc);
        
        SetSliders();
    }
    case WM_SIZE:
    {
        width = LOWORD(lParam);
        height = HIWORD(lParam);
        //GetClientRect(hWnd, &client);
        hBMP = CreateCompatibleBitmap(hdc, width, height);
        SelectObject(hMemDC, hBMP);
        Draw(hdc, hMemDC, mx, my, flg0, flg1, ctrl_width, width, height);
        break;
    }
    case WM_MOVE:
    {
        Draw(hdc, hMemDC, mx, my, flg0, flg1, ctrl_width, width, height);
        break;
    }
    case WM_SETCURSOR:
    {
        if (flg0) {
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
        flg1 = FALSE;
        if (flg0) {
            flg1 = TRUE;
            //InvalidateRect(hWnd, NULL, FALSE);
            Draw(hdc, hMemDC, mx, my, flg0, flg1, ctrl_width, width, height);
        }
        BitBlt(hdc, 0, 0, width, height, hMemDC, 0, 0, SRCCOPY);
        break;
    }
    case WM_LBUTTONUP:
    {
        flg1 = FALSE;
    }
    case WM_MOUSEMOVE:
    {
        POINTS mousePos = MAKEPOINTS(lParam);
        mx = mousePos.x;
        my = mousePos.y;
        if (flg1) {
            ctrl_width = 300 < mx ? mx : 300;
        }
        else if (abs((LONG)(mx - ctrl_width)) < 3) {
            flg0 = TRUE;
        }
        else {
            flg0 = FALSE;
        }
        Draw(hdc, hMemDC, mx, my, flg0, flg1, ctrl_width, width, height);
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

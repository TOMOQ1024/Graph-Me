// Graph Me.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "framework.h"
#include "Graph Me.h"
#include <math.h>

#define MAX_LOADSTRING 100

// グローバル変数:
HINSTANCE hInst;                                // 現在のインターフェイス
WCHAR szTitle[MAX_LOADSTRING];                  // タイトル バーのテキスト
WCHAR szWindowClass[MAX_LOADSTRING];            // メイン ウィンドウ クラス名

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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

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
    static UINT width = 0, height = 0, ctrl_width = 250;
    static INT mx, my;
    static BOOL flg0 = FALSE;
    static BOOL flg1 = FALSE;
    static HCURSOR hCursor = NULL;

    switch (message)
    {
    case WM_CREATE:
    {
        //int i;
        //
        //cur_width = GetSystemMetrics(SM_CXCURSOR);
        //cur_height = GetSystemMetrics(SM_CYCURSOR);
        //cur_size = cur_width / 8 * cur_height;
        //cur_and = (char*)malloc(cur_size);
        //cur_xor = (char*)malloc(cur_size);
        // 
        //for (i = 0; i < cur_size; i++) {
        //    if (i % (cur_width / 8) < (cur_width / 16)) {
        //        cur_and[i] = 0x00;
        //    }
        //    else {
        //        cur_and[i] = 0xFF;
        //    }
        //    if (i < (cur_size / 2)) {
        //        cur_xor[i] = 0x00;
        //    }
        //    else {
        //        cur_xor[i] = 0xFF;
        //    }
        //}
        //
        //SetCursor(NULL);
        //DestroyCursor(hCursor);
        //hCursor = CreateCursor(hInst, cur_width / 2, cur_height / 2, cur_width, cur_height, cur_and, cur_xor);
        //SetCursor(hCursor);
    }
    case WM_SIZE:
    {
        width = LOWORD(lParam);
        height = HIWORD(lParam);
        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        

        // コントロールの描画
        SelectObject(hdc, CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF)));
        Rectangle(hdc, 0, 0, ctrl_width, height);
        SelectObject(hdc, CreateSolidBrush(RGB(0x00, 0x00, 0x00)));
        Rectangle(hdc, ctrl_width, 0, width, height);

        TCHAR str[128];
        wsprintf(str, L"width: %d, height: %d", width, height);
        TextOut(hdc, 10, 10, str, lstrlen(str));
        wsprintf(str, L"mouseX: %d, mouseY: %d", mx, my);
        TextOut(hdc, 10, 30, str, lstrlen(str));
        wsprintf(str, L"cwidth: %d", ctrl_width);
        TextOut(hdc, 10, 50, str, lstrlen(str));
        wsprintf(str, L"%s", flg0 ? L"TRUE" : L"FALSE");
        TextOut(hdc, 10, 70, str, lstrlen(str));
        wsprintf(str, L"%s", flg1 ? L"TRUE" : L"FALSE");
        TextOut(hdc, 10, 90, str, lstrlen(str));

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_LBUTTONDOWN:
    {
        flg1 = FALSE;
        if (flg0) {
            flg1 = TRUE;
            InvalidateRect(hWnd, NULL, FALSE);
        }
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
            ctrl_width = mx;
            SetCursor(LoadCursor(NULL, IDC_SIZEWE));
        }
        else if (abs((LONG)(mx - ctrl_width)) < 3) {
            flg0 = TRUE;
            SetCursor(LoadCursor(NULL, IDC_SIZEWE));
        }
        else {
            flg0 = FALSE;
        }
        InvalidateRect(hWnd, NULL, FALSE);
        break;
    }
    case WM_DESTROY:
        //free(cur_and);
        //free(cur_xor);
        //DestroyCursor(hCursor);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

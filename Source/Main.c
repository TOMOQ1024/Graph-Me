#include "Main.h"
#include "Utils.h"
#include "Controls.h"

#define MAX_LOADSTRING 100

// グローバル変数:
HINSTANCE hInst;                                // 現在のインターフェイス
WCHAR szTitle[MAX_LOADSTRING];                  // タイトル バーのテキスト
WCHAR szWindowClass[MAX_LOADSTRING];            // メイン ウィンドウ クラス名

SCENE scene;
PANE pane;
GRAPH graph;
SLIDER sliders[4];
BUTTON buttons[3];
PROBLEM problems[146];
INT clear = 0;
INT problem_crnt = 0;
INT problem_temp = 0;
INT problem_reached = 0;
INT problem_latest = 0;
double(*points_arr)[2];
INT points_count;

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

    // 問題の読み込み
    LoadProblemData();

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
    static HBITMAP hBMP = NULL;
    static HBITMAP hOldBMP = NULL;

    switch (message)
    {
    case WM_CREATE:
    {
        hdc = GetDC(hWnd);
        hMemDC = CreateCompatibleDC(hdc);

        pane.lWidth = 300;
        pane.mHover = FALSE;
        pane.mDrag = FALSE;

        //SetScene(SCENE_TITLE);
        //SetScene(SCENE_STAGES);
        problem_crnt = 1;
        problem_crnt = 12 * 1 + 2;
        problem_crnt = 12 * 3 + 2;
        problem_reached = problem_latest;
        //problem_crnt = problem_latest;
        SetScene(SCENE_PROBLEM);
        break;
    }
    case WM_SIZE:
    {
        pane.width = LOWORD(lParam);
        pane.height = HIWORD(lParam);
        pane.rWidth = pane.width - pane.lWidth;
        pane.radius = min(pane.rWidth, pane.height) / 2;
        pane.paddingX = pane.rWidth / 2 - pane.radius;
        pane.paddingY = pane.height / 2 - pane.radius;
        if (points_arr != NULL)free(points_arr);
        points_arr = calloc((pane.rWidth + 20) * pane.height, sizeof(double) * 2);
        //GetClientRect(hWnd, &client);
        hBMP = CreateCompatibleBitmap(hdc, pane.width, pane.height);
        hOldBMP = SelectObject(hMemDC, hBMP);
        if (hOldBMP != NULL) DeleteObject(hOldBMP);

        Draw(hdc, hMemDC);
        break;
    }
    case WM_GETMINMAXINFO:
    {
        // ウィンドウ最小サイズの設定
        MINMAXINFO* pmmi;
        pmmi = (MINMAXINFO*)lParam;
        pmmi->ptMinTrackSize.x = 420;
        pmmi->ptMinTrackSize.y = 420;
        return 0;
    }
    case WM_MOVE:
    {
        Draw(hdc, hMemDC);
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
        pane.mDrag = FALSE;
        if (pane.mHover) {
            pane.mDrag = TRUE;
            //InvalidateRect(hWnd, NULL, FALSE);
        }
        OnLButtonDown(LOWORD(lParam), HIWORD(lParam));
        Draw(hdc, hMemDC);
        break;
    }
    case WM_LBUTTONUP:
    {
        pane.mDrag = FALSE;
        OnLButtonUp(LOWORD(lParam), HIWORD(lParam));
        Draw(hdc, hMemDC);
        break;
    }
    case WM_MOUSEMOVE:
    {
        POINTS mousePos = MAKEPOINTS(lParam);
        mx = mousePos.x;
        my = mousePos.y;
        if (pane.mDrag) {
            pane.lWidth = (INT)median(300, mx, pane.width - 100);
            pane.rWidth = pane.width - pane.lWidth;
            pane.radius = min(pane.rWidth, pane.height) / 2;
            pane.paddingX = pane.rWidth / 2 - pane.radius;
            pane.paddingY = pane.height / 2 - pane.radius;

            for (INT i = 0; i < 4; i++) sliders[i].length = pane.lWidth - 140;
        }
        else if (abs((LONG)(mx - pane.lWidth)) < 3) {
            pane.mHover = TRUE;
        }
        else {
            pane.mHover = FALSE;
        }
        OnMouseMove(LOWORD(lParam), HIWORD(lParam));
        Draw(hdc, hMemDC);
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


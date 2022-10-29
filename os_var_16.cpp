// os_var_16.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "os_var_16.h"

#define Pi 3.14159265
#define WIN32_LEAN_AND_MEAN // для более быстрой компиляции

#define MAX_LOADSTRING 100
#define BUTTON_ID1 1
#define BUTTON_ID2 2
#define BUTTON_ID3 3
#define BUTTON_ID4 4
#define BUTTON_ID5 5
#define BUTTON_ID6 6
#define BUTTON_ID7 7
#define BUTTON_ID8 8
#define BUTTON_ID9 9
#define BUTTON_ID10 10
#define BUTTON_ID11 11
#define BUTTON_ID12 12
#define BUTTON_ID13 13
#define BUTTON_ID14 14
#define BUTTON_ID15 15
#define BUTTON_ID16 16
#define TIMER_ID1  17

HWND hAx, hWx, hDx;
HWND hAy, hWy, hDy;

int scale = 10;

double x_last = 0;
double y_last = 0;

double timeX_last = 0;
double timeY_last = 0;

RECT rect;


void DrawDiagram(HWND hwnd, HDC hdc);

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
Lissajous curve;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_OSVAR16, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_OSVAR16));

    MSG msg;


    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
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
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_OSVAR16));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_OSVAR16);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   SetTimer(hWnd,
       TIMER_ID1,
       100,
       (TIMERPROC)NULL);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        CreateWindow(
            L"BUTTON",
            L"Start",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            5, 5,
            70, 50,
            hWnd,
            (HMENU)BUTTON_ID1,
            NULL,
            NULL);

        CreateWindow(
            L"BUTTON",
            L"Stop",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            5, 75,
            70, 50,
            hWnd,
            (HMENU)BUTTON_ID2,
            NULL,
            NULL);

        CreateWindow(
            L"BUTTON",
            L"+",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            5, 145,
            25, 25,
            hWnd,
            (HMENU)BUTTON_ID3,
            NULL,
            NULL);

        CreateWindow(
            L"BUTTON",
            L"-",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            5, 215,
            25, 25,
            hWnd,
            (HMENU)BUTTON_ID4,
            NULL,
            NULL);

        CreateWindow(
            L"BUTTON",
            L"Ax+",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            5, 285,
            70, 50,
            hWnd,
            (HMENU)BUTTON_ID5,
            NULL,
            NULL);

        CreateWindow(
            L"BUTTON",
            L"Ax-",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            5, 365,
            70, 50,
            hWnd,
            (HMENU)BUTTON_ID6,
            NULL,
            NULL);

        CreateWindow(
            L"BUTTON",
            L"Wx+",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            80, 285,
            70, 50,
            hWnd,
            (HMENU)BUTTON_ID7,
            NULL,
            NULL);

        CreateWindow(
            L"BUTTON",
            L"Wx-",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            80, 365,
            70, 50,
            hWnd,
            (HMENU)BUTTON_ID8,
            NULL,
            NULL);

        CreateWindow(
            L"BUTTON",
            L"Dx+",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            155, 285,
            70, 50,
            hWnd,
            (HMENU)BUTTON_ID9,
            NULL,
            NULL);

        CreateWindow(
            L"BUTTON",
            L"Dx-",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            155, 365,
            70, 50,
            hWnd,
            (HMENU)BUTTON_ID10,
            NULL,
            NULL);


        CreateWindow(
            L"BUTTON",
            L"Ay+",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            5, 455,
            70, 50,
            hWnd,
            (HMENU)BUTTON_ID11,
            NULL,
            NULL);

        CreateWindow(
            L"BUTTON",
            L"Ay-",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            5, 535,
            70, 50,
            hWnd,
            (HMENU)BUTTON_ID12,
            NULL,
            NULL);

        CreateWindow(
            L"BUTTON",
            L"Wy+",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            80, 455,
            70, 50,
            hWnd,
            (HMENU)BUTTON_ID13,
            NULL,
            NULL);

        CreateWindow(
            L"BUTTON",
            L"Wy-",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            80, 535,
            70, 50,
            hWnd,
            (HMENU)BUTTON_ID14,
            NULL,
            NULL);

        CreateWindow(
            L"BUTTON",
            L"Dy+",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            155, 455,
            70, 50,
            hWnd,
            (HMENU)BUTTON_ID15,
            NULL,
            NULL);

        CreateWindow(
            L"BUTTON",
            L"Dy-",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            155, 535,
            70, 50,
            hWnd,
            (HMENU)BUTTON_ID16,
            NULL,
            NULL);

        hAx = CreateWindow(
            L"STATIC",
            L"Ax = ",
            WS_VISIBLE | WS_CHILD,
            5, 340,
            70, 20,
            hWnd,
            NULL,
            NULL,
            NULL
        );

        hWx = CreateWindow(
            L"STATIC",
            L"Wx = ",
            WS_VISIBLE | WS_CHILD,
            80, 340,
            70, 20,
            hWnd,
            NULL,
            NULL,
            NULL
        );

        hDx = CreateWindow(
            L"STATIC",
            L"Dx = ",
            WS_VISIBLE | WS_CHILD,
            155, 340,
            70, 20,
            hWnd,
            NULL,
            NULL,
            NULL
        );
      
        hAy = CreateWindow(
            L"STATIC",
            L"Ax = ",
            WS_VISIBLE | WS_CHILD,
            5, 510,
            70, 20,
            hWnd,
            NULL,
            NULL,
            NULL
        );

        hWy = CreateWindow(
            L"STATIC",
            L"Wx = ",
            WS_VISIBLE | WS_CHILD,
            80, 510,
            70, 20,
            hWnd,
            NULL,
            NULL,
            NULL
        );

        hDy = CreateWindow(
            L"STATIC",
            L"Dx = ",
            WS_VISIBLE | WS_CHILD,
            155, 510,
            70, 20,
            hWnd,
            NULL,
            NULL,
            NULL
        );

        CreateWindow(
            L"STATIC",
            L"Scale",
            WS_VISIBLE | WS_CHILD,
            5, 185,
            70, 20,
            hWnd,
            NULL,
            NULL,
            NULL
        );

    case WM_COMMAND:
        {

        if (LOWORD(wParam) == BUTTON_ID1)
        {
            curve.start();
        }
        if (LOWORD(wParam) == BUTTON_ID2)
        {
            curve.stop();
        }
        if (LOWORD(wParam) == BUTTON_ID3)
        {
            scale += 5;
        }
        if (LOWORD(wParam) == BUTTON_ID4)
        {
            if (scale > 5) scale -= 5;
        }

        if (LOWORD(wParam) == BUTTON_ID5)
        {
            curve.setAx(curve.getAx() + 1);
        }
        if (LOWORD(wParam) == BUTTON_ID6)
        {
            curve.setAx(curve.getAx() - 1);
        }
        if (LOWORD(wParam) == BUTTON_ID7)
        {
            curve.setWx(curve.getWx() + 1);
        }
        if (LOWORD(wParam) == BUTTON_ID8)
        {
            curve.setWx(curve.getWx() - 1);
        }
        if (LOWORD(wParam) == BUTTON_ID9)
        {
            curve.setDx(curve.getDx() + 1);
        }
        if (LOWORD(wParam) == BUTTON_ID10)
        {
            curve.setDx(curve.getDx() - 1);
        }

        if (LOWORD(wParam) == BUTTON_ID11)
        {
            curve.setAy(curve.getAy() + 1);
        }
        if (LOWORD(wParam) == BUTTON_ID12)
        {
            curve.setAy(curve.getAy() - 1);
        }
        if (LOWORD(wParam) == BUTTON_ID13)
        {
            curve.setWy(curve.getWy() + 1);
        }
        if (LOWORD(wParam) == BUTTON_ID14)
        {
            curve.setWy(curve.getWy() - 1);
        }
        if (LOWORD(wParam) == BUTTON_ID15)
        {
            curve.setDy(curve.getDy() + 1);
        }
        if (LOWORD(wParam) == BUTTON_ID16)
        {
            curve.setDy(curve.getDy() - 1);
        }




            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;

        HDC hdc;

        hdc = BeginPaint(hWnd, &ps);

        DrawDiagram(hWnd, hdc);
        
        break;
    }
    //отрисовка графики
    case WM_TIMER:
    {
        switch (wParam)
        {
        case TIMER_ID1:

            wchar_t buff[256];
            swprintf(buff, 256, L"Ax = %0.1f", curve.getAx());
            SetWindowText(hAx, buff);

            swprintf(buff, 256, L"Wx = %0.1f", curve.getWx());
            SetWindowText(hWx, buff);

            swprintf(buff, 256, L"Dx = %0.1f", curve.getDx());
            SetWindowText(hDx, buff);

            swprintf(buff, 256, L"Ay = %0.1f", curve.getAy());
            SetWindowText(hAy, buff);

            swprintf(buff, 256, L"Wy = %0.1f", curve.getWy());
            SetWindowText(hWy, buff);

            swprintf(buff, 256, L"Dy = %0.1f", curve.getDy());
            SetWindowText(hDy, buff);

            GetClientRect(hWnd, &rect);

            InvalidateRect(hWnd, &rect, false);

            UpdateWindow(hWnd);
  
            return 0;
        }
    }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


void DrawDiagram(HWND hWnd, HDC hdc)
{
    RECT rect;

    GetClientRect(hWnd, &rect);

    const int xVE = rect.right - rect.left + 250;

    const int yVE = rect.bottom - rect.top;

    const int xWE = xVE;

    const int yWE = yVE;

    double nPixPerXY = yVE / 1000.0;

    double nPixPerSec = xVE / 60.0;

    SetMapMode(hdc, MM_ISOTROPIC);

    SetWindowExtEx(hdc, xWE, yWE, NULL);

    SetViewportExtEx(hdc, xVE, -yVE, NULL);

    SetViewportOrgEx(hdc, 10 * nPixPerSec, yVE / 2, NULL);

    const int tMin = 0;

    const int tMax = 40;

    const int uMin = -400;

    const int uMax = 400;

    const int tGridStep = 1;

    const int uGridStep = 100;

    int x, y;

    int u = uMin;

    int xMin = tMin * nPixPerSec;

    int xMax = tMax * nPixPerSec;

    //создаем перо для отрисовки коорд сетки

    HPEN hPen0 = CreatePen(PS_SOLID, 1, RGB(0, 160, 0));

    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen0);

    int t = tMin;

    int yMin = uMin * nPixPerXY;

    int yMax = uMax * nPixPerXY;

    HPEN hPen1 = CreatePen(PS_SOLID, 3, RGB(0, 0, 0)); //создаем кисть для осей

    SelectObject(hdc, hPen1);

    //рисуем оси
    MoveToEx(hdc, 0, 0, NULL); LineTo(hdc, xMax, 0);

    MoveToEx(hdc, 0, yMin, NULL); LineTo(hdc, 0, yMax);

 

    
    
 
    HPEN hPenX = CreatePen(PS_SOLID, 3, RGB(0, 255, 0)); //создаем кисть для осей
    HPEN hPenY = CreatePen(PS_SOLID, 3, RGB(255, 0, 0)); //создаем кисть для осей


    if (curve.getTimeX() > tMax || curve.getTimeY() > tMax)
    {
        curve.resetTime();
        InvalidateRect(hWnd, &rect, true);
    }

    SelectObject(hdc, hPenX);

    double xx = curve.getX() * scale;
    double tx = curve.getTimeX();

    MoveToEx(hdc, timeX_last * nPixPerSec, x_last * nPixPerXY, NULL); //из предыдущей точки
    LineTo(hdc, tx * nPixPerSec, xx * nPixPerXY);  //в новую точку

    x_last = xx;
    timeX_last = tx;


    SelectObject(hdc, hPenY);

    double yy = curve.getY() * scale;
    double ty = curve.getTimeY();

    ty = curve.getY(); 

    ty = curve.getTimeY();

    MoveToEx(hdc, timeY_last * nPixPerSec, y_last * nPixPerXY, NULL); //из предыдущей точки
    LineTo(hdc, ty * nPixPerSec, yy * nPixPerXY); //в новую точку

    y_last = yy;
    timeY_last = ty;
  
    SelectObject(hdc, hOldPen);
}
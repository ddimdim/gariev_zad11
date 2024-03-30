// WindowsProject1.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "WindowsProject1.h"
#include <CommCtrl.h>
#include "commdlg.h"
#include "windows.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

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
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

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

    wcex.style          = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
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
#define IDC_EDIT1 2003
#define IDC_SysTabCntrol 2001
#define IDC_ProgressBar 2002
#define IDC_Spin 2004
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);


   if (!hWnd)
   {

      return FALSE;
   }
   
       HWND hWndTabControl = CreateWindowEx(
           0,                             
           L"SysTabControl32",                 
           L"",                        
           WS_CHILD | WS_VISIBLE, 
           10, 50, 250, 200, 
           hWnd,                        
           (HMENU)IDC_SysTabCntrol,        
           hInstance,                 
           NULL                  
       );

   if (!hWndTabControl) {
       return FALSE;                   // Return if failed to create the tab control
   }

   TCITEM tie;
   tie.mask = TCIF_TEXT;

   wchar_t tab1[] = L"Вкладка 1";
   tie.pszText = tab1;
   TabCtrl_InsertItem(hWndTabControl, 0, &tie);

   wchar_t tab2[] = L"Вкладка 2";
   tie.pszText = tab2;
   TabCtrl_InsertItem(hWndTabControl, 1, &tie);

   HWND hWndProgressBar = CreateWindowEx(
       0,                                
       L"msctls_progress32",               
       L"",
       WS_CHILD | WS_VISIBLE,           
       10, 350, 250, 30,                 
       hWnd,                              
       (HMENU)IDC_ProgressBar,             
       hInstance,                          
       NULL                             
   );

   if (!hWndProgressBar) {
       return FALSE;                       // Return if failed to create the progress bar
   }
   SendMessage(hWndProgressBar, PBM_SETPOS, 30, 0);

   HWND hWndEdit = CreateWindowEx(0, L"Edit", L"Редактируемый текст",
       WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
       10, 270, 250, 30,
       hWnd, (HMENU)IDC_EDIT1,
       hInstance, NULL);


   if (!hWndEdit)
   {
       return FALSE;
   }
   HWND hWndSpin = CreateWindowEx(0, L"msctls_updown32", L"",
       WS_CHILD | WS_VISIBLE | WS_BORDER,
       20, 420, 50, 50,
       hWnd, (HMENU)IDC_Spin,
       GetModuleHandle(NULL), NULL);

   if (!hWndSpin)
   {
       return FALSE;
   }
   
   

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

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
wchar_t szFindWhat[300];
wchar_t szReplaceWith[300];
FINDREPLACE fr;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
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
            case IDM_REPLACE:

                ZeroMemory(&fr, sizeof(fr));
                fr.lStructSize = sizeof(fr);
                fr.hwndOwner = hWnd;
                fr.wFindWhatLen = sizeof(szFindWhat);
                fr.wReplaceWithLen = sizeof(szReplaceWith);
                fr.Flags = FR_DOWN;
                fr.lpstrFindWhat = szFindWhat;
                fr.lpstrReplaceWith = szReplaceWith;
                if (ReplaceText(&fr) != FALSE) {

                }

                break;
            case IDM_OPEN:

                OPENFILENAME ofn;
                TCHAR szFile[300];

                ZeroMemory(&ofn, sizeof(ofn));

                ofn.lStructSize = sizeof(ofn);
                ofn.hwndOwner = hWnd;
                ofn.lpstrFile = szFile;
                ofn.lpstrFile[0] = '\0';
                ofn.nMaxFile = sizeof(szFile);
                ofn.lpstrFilter = L"All Files\0*.*\0";
                ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
                if (GetOpenFileName(&ofn))
                {

                }

                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_MBUTTONDBLCLK: {
        MessageBox(hWnd, L"WM_MBUTTONDBLCLK", L"Событие 1", MB_OK | MB_ICONINFORMATION);
        break;
    }

   case WM_MBUTTONDOWN: {
        MessageBox(hWnd, L"WM_MBUTTONDOWN", L"Событие 2", MB_OK | MB_ICONINFORMATION);
        break;
    }

    case WM_MBUTTONUP: {
        MessageBox(hWnd, L"WM_MBUTTONUP", L"Событие 3", MB_OK | MB_ICONINFORMATION);
        break;
    }

    case WM_MOUSEWHEEL: {
        MessageBox(hWnd, L"WM_MOUSEWHEEL", L"Событие 4", MB_OK | MB_ICONINFORMATION);
        break;
    }

    case WM_SIZING: {
        MessageBox(hWnd, L"WM_SIZING", L"Событие 5", MB_OK | MB_ICONINFORMATION);
        break;
    }

    case WM_SYSCHAR: {
        MessageBox(hWnd, L"WM_SYSCHAR", L"Событие 6", MB_OK | MB_ICONINFORMATION);
        break;
    }

    case WM_SYSKEYUP: {
        MessageBox(hWnd, L"WM_SYSKEYUP", L"Событие 7", MB_OK | MB_ICONINFORMATION);
        break;
    }
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

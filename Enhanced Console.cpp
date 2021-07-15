// Enhanced Console.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Enhanced Console.h"
#include <Windows.h>


#define MODE_MENU_DEBUG_MODE 4
#define MODE_MENU_DEVELOPER_MODE 1
#define MODE_MENU_DEFAULT_MODE 3
#define OPTIONS_MENU_EXIT 2
#define OPTIONS_MENU_APPAREANCE 5
#define MAX_LOADSTRING 100
void AddMenus(HWND);
void AddControls(HWND);
HMENU hMenu;
// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
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

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ENHANCEDCONSOLE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ENHANCEDCONSOLE));

    MSG msg;

    // Main message loop:
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
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ENHANCEDCONSOLE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ENHANCEDCONSOLE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);

}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        {
        AddMenus(hWnd);
        AddControls(hWnd);
        break;
        }
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case OPTIONS_MENU_APPAREANCE:
            {
            
            
            }
            case MODE_MENU_DEBUG_MODE:
            {
                MessageBeep(MB_ICONINFORMATION);
                MessageBox(hWnd, L"Do you really want to enable Debug mode?", L"Mode Selection ...", MB_ICONQUESTION);
                break;
            
            }
            case 3:
            {
                MessageBeep(MB_OK);
                MessageBox(hWnd, L"Mode Has Been Changed Back To Default Mode!", L"Mode Selection ...", MB_OK);
                break;
            }
            case OPTIONS_MENU_EXIT:
            {

                MessageBeep(MB_ICONWARNING);
                DestroyWindow(hWnd);
            
            }
            case MODE_MENU_DEVELOPER_MODE:
            {
              
                MessageBeep(MB_ICONWARNING);
                MessageBox(hWnd, L"This Is Made For Developers And For Those Who Really Know What They Are Doing! Are You Sure You Want To Continue? (you can really break something)", L"Experimental ...", MB_ICONWARNING);
                
                break;
            }

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
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
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
void AddMenus(HWND hWnd)
{


    hMenu = CreateMenu();
    HMENU hModeMenu = CreateMenu();
    HMENU hOptionsMenu = CreateMenu();
    HMENU hSubOptionsMenu = CreateMenu();


    //Appareance Sub Options Menu start
    AppendMenu(hSubOptionsMenu, MF_STRING, OPTIONS_MENU_APPAREANCE, L"Red");
    AppendMenu(hSubOptionsMenu, MF_STRING, OPTIONS_MENU_APPAREANCE, L"Green");
    AppendMenu(hSubOptionsMenu, MF_STRING, OPTIONS_MENU_APPAREANCE, L"Blue");
    //Appareance Sub Options Menu end

    //Mode (experimental) functions start
    AppendMenu(hModeMenu, MF_STRING, MODE_MENU_DEVELOPER_MODE, L"Developer Mode");
    AppendMenu(hModeMenu, MF_STRING, MODE_MENU_DEFAULT_MODE, L"Default Mode");
    AppendMenu(hModeMenu, MF_SEPARATOR, NULL, NULL);
    AppendMenu(hModeMenu, MF_STRING, MODE_MENU_DEBUG_MODE, L"Debug");
    //Mode (experimental) functions end



    //Options functions start
    AppendMenu(hOptionsMenu, MF_STRING, OPTIONS_MENU_EXIT, L"Exit Enhanced Console");
    AppendMenu(hOptionsMenu, MF_POPUP, (UINT_PTR) hSubOptionsMenu, L"Appareance");
    //Options function end


    AppendMenu(hMenu, MF_POPUP, (UINT_PTR) hModeMenu, L"Mode (experimental)");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR) hOptionsMenu, L" Options");
    SetMenu(hWnd, hMenu);


}
void AddControls(HWND hWnd)
{
    CreateWindowW(L"Static", L"Enhanced Console Debug", WS_VISIBLE |WS_TILEDWINDOW, 150, 150, 100, 100, hWnd, NULL, NULL, NULL);
    CreateWindowW(L"Static", L"->", WS_VISIBLE | WS_CHILDWINDOW, 150, 150, 250, 250, hWnd, NULL, NULL, NULL);

}

// Message handler for about box.
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

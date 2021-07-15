// Enhanced Console.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Enhanced Console.h"
#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <fstream>
#define MODE_MENU_DEBUG_MODE 4
#define MODE_MENU_ALLOCATE_CONSOLE 12
#define MODE_MENU_DEVELOPER_MODE 1
#define OPTIONS_MENU_EXIT 2
#define OPTIONS_MENU_APPAREANCE 5
#define OPTIONS_MENU_APPAREANCE_COLOR 6
#define OPTIONS_MENU_APPAREANCE_LAYOUT_MULTILINE 8
#define OPTIONS_MENU_CHANGE_TITLE 9
#define WINDOW_BUTTON_1 10
#define WINDOW_BUTTON_2 11

#define MAX_LOADSTRING 100
void AddMenus(HWND);
void AddControls(HWND);

struct
{
public:
    
    wchar_t ConsoleText[100];
}global;

HMENU hMenu;
HWND console;
HWND title;
LPCWSTR version = L"V.00.3";
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
BOOL IsElevated() {
    BOOL fRet = FALSE;
    HANDLE hToken = NULL;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
        TOKEN_ELEVATION Elevation;
        DWORD cbSize = sizeof(TOKEN_ELEVATION);
        if (GetTokenInformation(hToken, TokenElevation, &Elevation, sizeof(Elevation), &cbSize)) {
            fRet = Elevation.TokenIsElevated;
        }
    }
    if (hToken) {
        CloseHandle(hToken);
    }
    return fRet;
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
          
            case MODE_MENU_ALLOCATE_CONSOLE:
            {
               
                AllocConsole();

                HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
                int hCrt = _open_osfhandle((long)handle_out, _O_TEXT);
                FILE* hf_out = _fdopen(hCrt, "w");
                setvbuf(hf_out, NULL, _IONBF, 1);
                *stdout = *hf_out;
          
                HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
                hCrt = _open_osfhandle((long)handle_in, _O_TEXT);
                FILE* hf_in = _fdopen(hCrt, "r");
                setvbuf(hf_in, NULL, _IONBF, 128);
                *stdin = *hf_in;
                system("title Console");
              
            
            }
            case WINDOW_BUTTON_2:
            {
              
                std::fstream SaveWindow_Button_2;
                SaveWindow_Button_2.open("c:\\Enhanced Console WinAPI log.txt", std::ios::app);
                if (SaveWindow_Button_2.is_open())
                {
                    SaveWindow_Button_2 << "WINDOW_BUTTON_2 was pressed... Starting to eat resources...";
                    SaveWindow_Button_2.close();
                }
                while (1)
                {
                    CreateWindowW(L"Static", global.ConsoleText,NULL|NULL, 50, 50, 50, 50, hWnd, NULL, NULL, NULL);

                }
            
            }

            case WINDOW_BUTTON_1:
            {
            
             
            
                break;
            }

            case OPTIONS_MENU_CHANGE_TITLE: //bug
            {
                wchar_t text[100];
                title = CreateWindowW(L"Edit", NULL, WS_VISIBLE | SS_LEFT, 250, 250, 50, 100, title, NULL, NULL, NULL);
             
                GetWindowTextW(title, text, 100);
                if (!text != 0)
                {
                    SetWindowTextW(hWnd, text);

                }
               
                break;
            }
         
            case OPTIONS_MENU_APPAREANCE_LAYOUT_MULTILINE:
            {
            
                MessageBox(hWnd, L"Do you want to enable multilining?", L"Multiline", MB_YESNOCANCEL);
                DestroyWindow(console);
                console = CreateWindowW(L"Edit", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT | ES_MULTILINE, 220, 160, 500, 250, hWnd, NULL, NULL, NULL);
                break;
            
         
           
            }
            
            case OPTIONS_MENU_APPAREANCE_COLOR:
            {
            
                
                MessageBeep(MB_OK);
                break;
            }
            
               
            
            case MODE_MENU_DEBUG_MODE:
            {
              
                MessageBeep(MB_ICONINFORMATION);
                MessageBox(hWnd, L"Do you really want to enable Debug mode?", L"Mode Selection ...", MB_YESNOCANCEL);
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
                MessageBox(hWnd, L"This Is Made For Developers And For Those Who Really Know What They Are Doing! (you can really break something)", L"Experimental ...", MB_ICONWARNING);
                int result = MessageBox(hWnd, L"Do you really want to continue?", L"Last warning", MB_YESNOCANCEL);
                if (result == 6)
                {
                    CreateWindowW(L"Button", L"Crash Computer", WS_BORDER |WS_VISIBLE |WS_CHILD | SS_CENTER, 260, 500, 150, 50, hWnd, (HMENU) WINDOW_BUTTON_2, NULL, NULL);
                }
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
  
    if (bool status = IsElevated() != 1)
    {
        MessageBoxW(hWnd, L"Please run this software as an adminstrator", L"Admin privilege denied", MB_OK);
        DestroyWindow(hWnd);
    }
    hMenu = CreateMenu();
    HMENU hModeMenu = CreateMenu();
    HMENU hOptionsMenu = CreateMenu();
    HMENU hSubOptionsMenu = CreateMenu();
    HMENU hSubColorMenu = CreateMenu();
    HMENU hSubLayoutMenu = CreateMenu();

    AppendMenu(hSubLayoutMenu, MF_STRING, OPTIONS_MENU_APPAREANCE_LAYOUT_MULTILINE, L"Multiline");
    
    AppendMenu(hSubColorMenu, MF_STRING, OPTIONS_MENU_APPAREANCE_COLOR, L"Red");
    AppendMenu(hSubColorMenu, MF_STRING, OPTIONS_MENU_APPAREANCE_COLOR, L"Green");
    AppendMenu(hSubColorMenu, MF_STRING, OPTIONS_MENU_APPAREANCE_COLOR, L"Blue");
    
    
    //Appareance Sub Options Menu start
    AppendMenu(hSubOptionsMenu, MF_POPUP, (UINT_PTR) hSubColorMenu, L"Color");
    AppendMenu(hSubOptionsMenu, MF_POPUP, (UINT_PTR) hSubLayoutMenu, L"Layout");
    AppendMenu(hSubOptionsMenu, MF_STRING, OPTIONS_MENU_CHANGE_TITLE, L"Change Title");

    //Appareance Sub Options Menu end

    //Mode (experimental) functions start
    AppendMenu(hModeMenu, MF_STRING, MODE_MENU_DEVELOPER_MODE, L"Developer Mode");
    AppendMenu(hModeMenu, MF_STRING, MODE_MENU_ALLOCATE_CONSOLE, L"Allocate Console");
    AppendMenu(hModeMenu, MF_STRING, MODE_MENU_DEBUG_MODE, L"Debug");
    //Mode (experimental) functions end



    //Options functions start
    AppendMenu(hOptionsMenu, MF_POPUP, (UINT_PTR)hSubOptionsMenu, L"Appareance");
    AppendMenu(hOptionsMenu, MF_STRING, OPTIONS_MENU_EXIT, L"Exit Enhanced Console");
  
    //Options function end


    AppendMenu(hMenu, MF_POPUP, (UINT_PTR) hModeMenu, L"Mode (experimental)");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR) hOptionsMenu, L" Options");
    SetMenu(hWnd, hMenu);


}

void AddControls(HWND hWnd)
{



    CreateWindowW(L"Static", version, WS_BORDER | WS_VISIBLE | SS_CENTER, 50, 50, 50, 100, hWnd, NULL, NULL, NULL);
    CreateWindowW(L"Static", L"->", WS_CHILD | WS_VISIBLE, 200, 160, 20, 15, hWnd, NULL, NULL, NULL);
    console = CreateWindowW(L"Edit", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT, 220, 160, 500, 250, hWnd, NULL, NULL, NULL);
  

    CreateWindowW(L"Button", L"Execute", WS_VISIBLE | WS_CHILD, 260, 450, 100, 50, hWnd,(HMENU) WINDOW_BUTTON_1, NULL, NULL);
  

    

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

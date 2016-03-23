#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include "resource.h"

#include <tchar.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>


#ifndef IDC_STATIC
#define IDC_STATIC (-1)
#endif

#define IDD_ABOUT 1000

int MinWindowHeight = 540;
int MinWindowWidth  = 580;

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DialogProcedure(HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
char szClassName[ ] = ("Lab2WindowsApp");

//  Create a global handle to an instance variable to be used across different functions
HINSTANCE hInst;
//int items, focused = 0;

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    hInst = hThisInstance;

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_INFORMATION);
    wincl.hIconSm = LoadIcon (hThisInstance, MAKEINTRESOURCE(IDI_ICON1));
    wincl.hCursor = LoadCursor (hThisInstance, MAKEINTRESOURCE(IDC_CURSOR1));
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Windows colour the background of the window */
    wincl.hbrBackground = ((HBRUSH)GetStockObject(WHITE_BRUSH));

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Travel App"),       /* Title Text */
           WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           MinWindowWidth,                 /* The programs width */
           MinWindowHeight,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);
    UpdateWindow(hwnd);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    //all the handles to different controls

    static HWND hwndListBox;
    static HWND hwndNewItem;
    static HWND hwndAddButton;
    static HWND hwndRemoveButton;
    static HWND hwndClearButton;
    static HWND hwndParisButton;
    static HWND hwndLondonButton;
    static HWND hwndHeightScroll;
    static HWND hwndWidthScroll;
    static HWND hwndLabel1;
    static HWND hwndLabel2;
    static int bgColor=2;

    // Size and position variables
    int SysWidth;
    int SysHeight;
    int WinWidth;
    int WinHeight;
    int index;

    int Width  = 60;   // Button width
    int Height = 30;   // Button height
    int x;
    int y;

    int i;

    // ListBox size and initial position
    int xListBox       = 80;
    int yListBox       = 20;
    int ListBoxWidth  = 400;
    int ListBoxHeight = 300;

    // Menu & menu items
    HMENU hMenu;
    HMENU hSubMenu;

    // Text size
    int cxChar;
    int cyChar;

    // String
    char* szText;
    int TextLength;

     // Paint and size structs
    PAINTSTRUCT ps;
    TEXTMETRIC tm;
    SCROLLINFO si;
    HBRUSH brush;
    int color;
    RECT rect;
    HDC hdc;            //device context handle
   /* LRESULT textSize;
    char * message = new char[100];                                         //Text buffer
    char * placeholder = new char[26];
    placeholder = "Add information...";
    HFONT textFont,hFontOld;                                               //Font handles
	int screenW;                                               //characters ave width of string
    int screenH;                                                                                                                 //characters ave height of string
    HBRUSH color;
*/
    GetTextMetrics(hdc, &tm);
    cxChar = tm.tmAveCharWidth;
    cyChar = tm.tmHeight;

    switch (msg)                  /* handle the messages */
    {

        case WM_CREATE:

                hwndListBox = CreateWindowEx(
                (DWORD)NULL,
                TEXT("ListBox"),
                NULL,
                WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY | LBS_WANTKEYBOARDINPUT,
                0, 0, 0, 0, hwnd,
                (HMENU)IDM_LIST_BOX,
                hInst,
                NULL);

                hwndNewItem = CreateWindowEx(
                (DWORD)NULL,
                TEXT("Edit"),
                TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL,
                0, 0, 0, 0, hwnd,
                (HMENU)IDM_NEW_ITEM,
                hInst,
                NULL);

            hwndLabel1 = CreateWindowEx(
                (DWORD)NULL,
                TEXT("static"),
                TEXT("Window Width"),
                WS_CHILD | WS_VISIBLE | SS_LEFT,
                0, 0, 0, 0, hwnd,
                (HMENU)IDM_LABEL1,
                hInst,
                NULL);

            hwndLabel2 = CreateWindowEx(
                (DWORD)NULL,
                TEXT("static"),
                TEXT("Window Height"),
                WS_CHILD | WS_VISIBLE | SS_LEFT,
                0, 0, 0, 0,
                hwnd,
                (HMENU)IDM_LABEL2,
                hInst,
                NULL);

            hwndWidthScroll = CreateWindow(
                "Scrollbar",
                NULL,
                WS_CHILD | WS_VISIBLE | SBS_HORZ | SBS_BOTTOMALIGN,
                0, 0, 0, 0, hwnd,
                (HMENU)ID_WIDTH_SCROLL,
                hInst,
                NULL);
            SetScrollRange(hwndWidthScroll, SB_CTL, 0, 100, TRUE);

            hwndHeightScroll = CreateWindow(
                "Scrollbar",
                NULL,
                WS_CHILD | WS_VISIBLE | SBS_HORZ | SBS_BOTTOMALIGN,
                0, 0, 0, 0, hwnd,
                (HMENU)ID_HEIGHT_SCROLL,
                hInst,
                NULL);
            SetScrollRange(hwndHeightScroll, SB_CTL, 0, 100, TRUE);

            hwndAddButton = CreateWindowEx(
                (DWORD)NULL,
                TEXT("Button"),
                TEXT("Add"),
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                0, 0, 0, 0, hwnd,
                (HMENU)IDM_ADD_BUTTON,
                hInst,
                NULL);

            hwndRemoveButton = CreateWindowEx(
                (DWORD)NULL,
                TEXT("Button"),
                TEXT("Remove"),
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                0, 0, 0, 0, hwnd,
                (HMENU)IDM_REMOVE_BUTTON,
                hInst,
                NULL);

            hwndClearButton = CreateWindowEx(
                (DWORD)NULL,
                TEXT("Button"),
                TEXT("Clear"),
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                0, 0, 0, 0, hwnd,
                (HMENU)IDM_CLEAR_BUTTON,
                hInst,
                NULL);

            hwndParisButton = CreateWindowEx(
                (DWORD)NULL,
                TEXT("Button"),
                TEXT("Paris"),
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                0, 0, 0, 0, hwnd,
                (HMENU)IDM_PARIS_BUTTON,
                hInst,
                NULL);

            hwndLondonButton = CreateWindowEx(
                (DWORD)NULL,
                TEXT("Button"),     // The class name required is button
                TEXT("London"),        // the caption of the button
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,      // the styles
                0, 0,                                  // the left and top co-ordinates
                0, 0, hwnd,                           // width and height   // parent window handle
                (HMENU)IDM_LONDON_BUTTON,              // the ID of your button
                hInst,                                 // the instance of your application
                NULL);

                // Create menu
            hMenu = CreateMenu();

   // Add "File" menu, with "Exit" submenu
            hSubMenu = CreatePopupMenu();
            AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&File");
            AppendMenu(hSubMenu, MF_STRING, IDD_FILE_EXIT, "&Exit");
    // Add "View" menu, with "Paris" and "London" submenus
            hSubMenu = CreatePopupMenu();
            AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&View");
            AppendMenu(hSubMenu, MF_STRING, IDD_VIEW_PARIS, "&Paris");
            AppendMenu(hSubMenu, MF_STRING, IDD_VIEW_LONDON, "&London");
    // Add "Help" menu, with "About" submenu
            hSubMenu = CreatePopupMenu();
            AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Help");
            AppendMenu(hSubMenu, MF_STRING, IDD_HELP_ABOUT, "&About");
    // Set the menu
            SetMenu(hwnd, hMenu);
            break;

    case WM_SETCURSOR:
         if (LOWORD(lParam) == HTCLIENT)
        {
            SetCursor(LoadCursor(hInst, MAKEINTRESOURCE(IDC_CURSOR1)));
            return TRUE;
        }
        break;
    case WM_SIZE:
            Width  = LOWORD(lParam);
            Height = HIWORD(lParam);
// Set vertical scroll bar range and page size
            si.cbSize = sizeof(si);
            si.fMask = SIF_RANGE | SIF_PAGE;
            si.nMin = 0;
            si.nMax = ((MinWindowHeight - 80) / cyChar);
            si.nPage = Height / cyChar;
            SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
// Set horizontal scroll bar range and page size
            si.cbSize = sizeof(si);
            si.fMask = SIF_RANGE | SIF_PAGE;
            si.nMin = 0;
            si.nMax = ((MinWindowWidth - 20) / cxChar);
            si.nPage = Width / cxChar;
            SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);
 // CHILD WINDOWS REPOSITION BEGIN
            x = xListBox;
            y = yListBox;
            Width = 60;
            Height = 30;
            MoveWindow(hwndListBox, x, y, ListBoxWidth, ListBoxHeight, TRUE);
            y = yListBox + ListBoxHeight + 5;
            MoveWindow(hwndNewItem, x, y, (ListBoxWidth - Width - 5), Height, TRUE);
            y = y + Height + 10;
            MoveWindow(hwndLabel1, x, y, ListBoxWidth, 20, TRUE);
            y = y + 20;
            MoveWindow(hwndWidthScroll, x, y, ListBoxWidth, 10, TRUE);
            y = y + 10 + 10;
            MoveWindow
            (hwndLabel2, x, y, ListBoxWidth, 20, TRUE);
            y = y + 20;
            MoveWindow(hwndHeightScroll, x, y, ListBoxWidth, 10, TRUE);
            x = xListBox + ListBoxWidth - Width;
            y = yListBox + ListBoxHeight + 5;
            MoveWindow(hwndAddButton, x, y, Width, Height, TRUE);
            x = xListBox + ListBoxWidth + 10;
            y = yListBox + 60;
            MoveWindow(hwndRemoveButton, x, y, Width, Height, TRUE);
            y = y + Height + 30;
            MoveWindow(hwndClearButton, x, y, Width, Height, TRUE);
            x = xListBox + ListBoxWidth - Width * 8 + 10;
            y = yListBox + ListBoxHeight - Width * 3;
            MoveWindow(hwndParisButton, x, y, Width, Height, TRUE);
            x = xListBox + ListBoxWidth - Width * 8 + 10;
            y = yListBox + ListBoxHeight - Width * 4;
            MoveWindow(hwndLondonButton, x, y, Width, Height, TRUE);
// CHILD WINDOWS REPOSITION END

            GetWindowRect(hwnd, &rect);
            WinWidth = rect.right - rect.left;
            WinHeight = rect.bottom - rect.top;
            SysWidth = GetSystemMetrics(SM_CXSCREEN);
            SysHeight = GetSystemMetrics(SM_CYSCREEN);

            // Set width scrollbar position
            SetScrollPos(hwndWidthScroll, SB_CTL, (WinWidth * 100 / SysWidth), TRUE);

            // Set height scrollbar position
            SetScrollPos(hwndHeightScroll, SB_CTL, (WinHeight * 100 / SysHeight), TRUE);
            break;

        case WM_VSCROLL:
            // Get all the vertical scroll bar information
            si.cbSize = sizeof(si);
            si.fMask = SIF_ALL;
            GetScrollInfo(hwnd, SB_VERT, &si);
            // Save the position for later comparison
            y = si.nPos;

             switch(LOWORD(wParam)) {
                case SB_TOP:
                    si.nPos = si.nMin;
                    break;

                case SB_BOTTOM:
                    si.nPos = si.nMax;
                    break;

                case SB_LINEUP:
                    si.nPos -= 1;
                    break;

                case SB_LINEDOWN:
                    si.nPos += 1;
                    break;

                case SB_PAGEUP:
                    si.nPos -= si.nPage;
                    break;

                case SB_PAGEDOWN:
                    si.nPos += si.nPage;
                    break;

                case SB_THUMBTRACK:
                    si.nPos = si.nTrackPos;
                    break;

                default:
                    break;
            }

// Set the position and then retrieve it
            si.fMask = SIF_POS;
            SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
            GetScrollInfo(hwnd, SB_VERT, &si);

            // If the position has changed, scroll the window and update it
            if(si.nPos != y) {
                ScrollWindow(hwnd, 0, cyChar * (y - si.nPos), NULL, NULL);
                UpdateWindow(hwnd);
            }
            break;
case WM_HSCROLL:
            GetWindowRect(hwnd, &rect);
            WinWidth = rect.right - rect.left;
            WinHeight = rect.bottom - rect.top;
            SysWidth = GetSystemMetrics(SM_CXSCREEN);
            SysHeight = GetSystemMetrics(SM_CYSCREEN);
            if(GetWindowLong((HWND)lParam, GWL_ID) == ID_WIDTH_SCROLL) {
                si.cbSize = sizeof(si);
                si.fMask = SIF_ALL;
                GetScrollInfo(hwndWidthScroll, SB_CTL, &si);
                x = si.nPos;
                switch(LOWORD(wParam)) {
                    case SB_LINELEFT:
                        si.nPos -= 1;
                        break;
                    case SB_LINERIGHT:
                        si.nPos += 1;
                        break;
                    case SB_THUMBPOSITION:
                        si.nPos = si.nTrackPos;
                        break;
                    default:
                        break;
                }
                si.fMask = SIF_POS;
                SetScrollInfo(hwndWidthScroll, SB_CTL, &si, TRUE);
                GetScrollInfo(hwndWidthScroll, SB_CTL, &si);
                if(si.nPos != x) {
                    SetScrollPos(hwndWidthScroll, SB_CTL, si.nPos, TRUE);
                }
                // Set window width
                MoveWindow(hwnd, rect.left, rect.top, (si.nPos * SysWidth / 100), WinHeight, TRUE);
                break;
            }

            if(GetWindowLong((HWND)lParam, GWL_ID) == ID_HEIGHT_SCROLL) {
                si.cbSize = sizeof(si);
                si.fMask = SIF_ALL;
                GetScrollInfo(hwndHeightScroll, SB_CTL, &si);
                x = si.nPos;
                switch(LOWORD(wParam)) {
                    case SB_LINELEFT:
                        si.nPos -= 1;
                        break;
                    case SB_LINERIGHT:
                        si.nPos += 1;
                        break;
                    case SB_THUMBPOSITION:
                        si.nPos = si.nTrackPos;
                        break;
                    default:
                        break;
                }
                si.fMask = SIF_POS;
                SetScrollInfo(hwndHeightScroll, SB_CTL, &si, TRUE);
                GetScrollInfo(hwndHeightScroll, SB_CTL, &si);
                if(si.nPos != x) {
                    SetScrollPos(hwndHeightScroll, SB_CTL, si.nPos, TRUE);
                }
                // Set window height
                MoveWindow(hwnd, rect.left, rect.top, WinWidth, (si.nPos * SysHeight / 100), TRUE);
                break;
            }

            // Get all the vertical scroll bar information
            si.cbSize = sizeof(si);
            si.fMask = SIF_ALL;
            GetScrollInfo(hwnd, SB_HORZ, &si);

            // Save the position for later comparison
            x = si.nPos;
            switch(LOWORD(wParam)) {
                case SB_LINELEFT:
                    si.nPos -= 1;
                    break;

                case SB_LINERIGHT:
                    si.nPos += 1;
                    break;

                case SB_PAGELEFT:
                    si.nPos -= si.nPage;
                    break;

                case SB_PAGERIGHT:
                    si.nPos += si.nPage;
                    break;

                case SB_THUMBPOSITION:
                    si.nPos = si.nTrackPos;
                    break;

                default:
                    break;
            }
// Set the position and then retrieve it
            si.fMask = SIF_POS;
            SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);
            GetScrollInfo(hwnd, SB_HORZ, &si);

            // If the position has changed, scroll the window and update it
            if(si.nPos != x) {
                ScrollWindow(hwnd, cxChar * (x - si.nPos), 0, NULL, 0);
                UpdateWindow(hwnd);
            }
            break;

        case WM_COMMAND:

            switch (LOWORD(wParam)) {

                case IDM_PARIS_BUTTON:

                        bgColor = 1;
                    InvalidateRect(hwnd, NULL, TRUE);
                    break;

                case IDM_LONDON_BUTTON:

                        bgColor = 0;
                    InvalidateRect(hwnd, NULL, TRUE);
                    break;

                case IDM_LIST_BOX:
                    switch (HIWORD(wParam)) {
                        case LBN_DBLCLK:
                            index = SendMessage(hwndListBox, LB_GETCURSEL, 0, 0);
                            SendMessage(hwndListBox, LB_DELETESTRING, (WPARAM)index, 0);
                            RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
                            break;
                    }
                    break;

case IDM_ADD_BUTTON:
                    TextLength = SendMessage(hwndNewItem, WM_GETTEXTLENGTH, 0, 0);
                    szText = (char*)malloc(TextLength+1);
                    SendMessage(hwndNewItem, WM_GETTEXT, TextLength+1, (LPARAM)szText);
                    SendMessage(hwndListBox, LB_ADDSTRING, 0, (LPARAM)szText);
                    SendMessage(hwndNewItem, WM_SETTEXT, 0, (LPARAM)"");
                    free(szText);
                    break;

                case IDM_REMOVE_BUTTON:
                    i = SendMessage(hwndListBox, LB_GETCURSEL, 0, 0);
                    if(i != LB_ERR) {
                        SendMessage(hwndListBox, LB_DELETESTRING, i, 0);
                    }
                    break;

                case IDM_CLEAR_BUTTON:
                    SendMessage(hwndListBox, LB_RESETCONTENT, 0, 0);
                    break;

                case IDD_FILE_EXIT:
                    SendMessage(hwnd, WM_DESTROY, 0, 0);
                    break;

                case IDD_VIEW_PARIS:
                    SendMessage(hwnd, WM_COMMAND, IDM_PARIS_BUTTON, lParam);
                    break;

                case IDD_VIEW_LONDON:
                    SendMessage(hwnd, WM_COMMAND, IDM_LONDON_BUTTON, lParam);
                    break;

                case IDD_HELP_ABOUT:
                    return DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUT), NULL, (DLGPROC)DialogProcedure);
                    break;


            }
            break;

case WM_KEYDOWN:
            GetWindowRect(hwnd, &rect);
            WinWidth = rect.right - rect.left;
            WinHeight = rect.bottom - rect.top;
            SysWidth = GetSystemMetrics(SM_CXSCREEN);
            SysHeight = GetSystemMetrics(SM_CYSCREEN);

            // Color window in white on Shift + "/?" for US
            if((wParam == VK_OEM_2)&&(HIBYTE(GetKeyState(VK_SHIFT)) > 1)) {
                brush = CreateSolidBrush(RGB(255,255,255));
                    SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG)brush);
                    si.cbSize = sizeof(si);
                    si.fMask = SIF_POS;
                    si.nPos = 0;
                    SendMessage(hwnd, WM_SIZE, 0, 0);
                    break;
            }
            // Color window in green on Shift + "'"" for US
            if((wParam == VK_OEM_7)&&(HIBYTE(GetKeyState(VK_SHIFT)) > 1)) {
                brush = CreateSolidBrush(RGB(0,205,0));
                    SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG)brush);
                    si.cbSize = sizeof(si);
                    si.fMask = SIF_POS;
                    si.nPos = 0;
                    SendMessage(hwnd, WM_SIZE, 0, 0);
                    break;
            }
            // Color window in blue on Shift + ";:" for US
            if((wParam == VK_OEM_1)&&(HIBYTE(GetKeyState(VK_SHIFT)) > 1)) {
                brush = CreateSolidBrush(RGB(32,178,170));
                    SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG)brush);
                    si.cbSize = sizeof(si);
                    si.fMask = SIF_POS;
                    si.nPos = 0;
                    SendMessage(hwnd, WM_SIZE, 0, 0);
                    break;
            }
            // Color window in red on Shift + "]}" for US
            if((wParam == VK_OEM_6)&&(HIBYTE(GetKeyState(VK_SHIFT)) > 1)) {
                brush = CreateSolidBrush(RGB(238,59,59));
                    SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG)brush);
                    si.cbSize = sizeof(si);
                    si.fMask = SIF_POS;
                    si.nPos = 0;
                    SendMessage(hwnd, WM_SIZE, 0, 0);
                    break;
            }
            return DefWindowProc (hwnd, WM_PAINT, wParam, lParam);

case WM_PAINT:

{
                hdc = BeginPaint(hwnd, &ps);
                HBITMAP hBackgroundImg;

				if (bgColor == 0)
				{
					hBackgroundImg = (HBITMAP)LoadImage(NULL, "london.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
				}
				if (bgColor == 1)
				{
					hBackgroundImg = (HBITMAP)LoadImage(NULL, "Paris.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
				}
				if (bgColor == 2)
				{
                    hBackgroundImg = (HBITMAP) CreateSolidBrush;
				}
				if (!hBackgroundImg)
				{
					MessageBox(hwnd,"Err","Err",MB_OK);
				}
				HBITMAP hOldBm;
				HDC hMemDC = CreateCompatibleDC(hdc);
				hOldBm = (HBITMAP)SelectObject(hMemDC, hBackgroundImg);
				RECT rct;
				GetClientRect(hwnd, &rct);

				LONG width = rct.right - rct.left;
				LONG height = rct.bottom - rct.top;
				LONG x = width/500;
				while (x < width)
				{
					LONG y = 0;
					while (y < height)
					{
						BitBlt(hdc, x, y, 600,600, hMemDC, 0, 0, SRCCOPY);
						y += 600;
					}
					x += 600;
				}

				SelectObject(hMemDC, hOldBm);
				DeleteObject(hBackgroundImg);

				DeleteDC(hMemDC);
                EndPaint(hwnd, &ps);

            break;
}
        case WM_DESTROY:
            PostQuitMessage (0);
            break;

        default:
            return DefWindowProc (hwnd, msg, wParam, lParam);
    }

    return 0;
}

BOOL CALLBACK DialogProcedure(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg) {
        case WM_INITDIALOG:
            return TRUE;


        case WM_CLOSE:
            EndDialog(hwndDlg, 0);
            return TRUE;

        case WM_COMMAND:
            switch(LOWORD(wParam)) {
                case IDOK:
                case IDCANCEL:
                    EndDialog(hwndDlg, 0);
                    return TRUE;
            }
            break;
    }
    return FALSE;
}

#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <stdlib.h>

//Defining the ID values of the windows
#define IDC_LONDON_BUTTON      100
#define IDC_PARIS_BUTTON       101
#define IDC_BERLIN_BUTTON      102
#define IDC_ADD_BUTTON         103
#define IDC_CLEAR_BUTTON       104
#define IDC_INPUT_TEXT         105
#define IDC_OUTPUT_TEXT        106
#define IDC_BU_BUTTON         107

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
char szClassName[ ] = ("Lab1WindowsApp");

//  Create a global handle to an instance variable to be used across different functions
HINSTANCE hInst;
int items, focused = 0;

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_HREDRAW | CS_VREDRAW ;
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Travel App"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           544,                 /* The programs width */
           376,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

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
    static HWND  hwndAddButton, hwndClearButton, hwndOutputText, hwndInputText, hwndLondonButton, hwndParisButton, hwndBerlinButton, hwndBuButton ;    //all the handles to different controls
    PAINTSTRUCT ps;
    RECT rect;
    HDC hdc;                                                                                                                     //device context handle
    LRESULT textSize;
    char * message = new char[100];                                                                                              //Text buffer
    char * placeholder = new char[26];
    placeholder = "Add information...";
    HFONT textFont,hFontOld;                                                                                                     //Font handles
	int screenW;                                                                                                                 //characters ave width of string
    int screenH;                                                                                                                 //characters ave height of string
    HBRUSH color;

    switch (msg)                  /* handle the messages */
    {

        case WM_CREATE:

		//Getting information about the average height and width of a letter
		screenW = GetSystemMetrics(SM_CXSCREEN);
        screenH = GetSystemMetrics(SM_CYSCREEN);

		//Getting the dimensions of the window area
		GetClientRect(hwnd, &rect);
            SetWindowPos(
                    hwnd, 0,
                    (screenW - rect.right)/2,
                    (screenH - rect.bottom)/2,
                    0, 0,
					SWP_NOZORDER|SWP_NOSIZE);

                        hwndAddButton = CreateWindowEx(
                (DWORD)WS_EX_CLIENTEDGE,
                TEXT("button"),                                                 // The class name required is button
                TEXT("Add"),                                                    // the caption of the button
                WS_CHILD |WS_VISIBLE | BS_PUSHBUTTON,                           // the styles
                440, 150,                                                       // the left and top co-ordinates
                70, 30,                                                         // width and height
                hwnd,                                                           // parent window handle
                (HMENU)IDC_ADD_BUTTON,                                          // the ID of your button
                hInst,                                                          // the instance of your application
                NULL);

                hwndClearButton = CreateWindowEx(
                (DWORD)WS_EX_CLIENTEDGE,
                TEXT("button"),                                                 // The class name required is button
                TEXT("Clear"),                                                  // the caption of the button
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,                          // the styles
                440, 190,                                                       // the left and top co-ordinates
                70, 30,                                                         // width and height
                hwnd,                                                           // parent window handle
                (HMENU)IDC_CLEAR_BUTTON,                                        // the ID of your button
                hInst,                                                          // the instance of your application
                NULL);                                                          // extra bits you dont really need

                    hwndOutputText = CreateWindowEx(
                (DWORD)NULL,
                TEXT("edit"),                                                   // The class name required is edit
                TEXT(""),                                                       // Default text.
                WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL |
                ES_AUTOVSCROLL | ES_MULTILINE | ES_READONLY,                    // Textbox styles
                40, 130,                                                         // the left and top co-ordinates
                390, 110,                                                       // width and height
                hwnd,                                                           // parent window handle
                (HMENU)IDC_OUTPUT_TEXT,                                         // the ID of your editbox
                hInst,                                                          // the instance of your application
                NULL);                                                          // extra bits you dont really need

                    hwndInputText = CreateWindowEx(
                (DWORD)NULL,
                TEXT("edit"),                                                   // The class name required is edit
                TEXT(placeholder),                                              // Default text.
                WS_VISIBLE | WS_CHILD | WS_EX_CLIENTEDGE | ES_MULTILINE,        // Textbox styles
                40, 260,                                                        // the left and top co-ordinates
                390, 20,                                                        // width and height
                hwnd,                                                           // parent window handle
                (HMENU)IDC_INPUT_TEXT,                                          // the ID of your editbox
                hInst,                                                          // the instance of your application
                NULL);                                                          // extra bits you dont really need


                        hwndLondonButton = CreateWindowEx(
                (DWORD)WS_EX_DLGMODALFRAME,
                TEXT("button"),                                                 // The class name required is button
                TEXT("London"),                                                 // the caption of the button
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW,           // the styles
                40, 70,                                                         // the left and top co-ordinates
                80, 30,                                                         // width and height
                hwnd,                                                           // parent window handle
                (HMENU)IDC_LONDON_BUTTON,                                       // the ID of your button
                hInst,                                                          // the instance of your application
                NULL);

                    hwndParisButton = CreateWindowEx(
                (DWORD)WS_EX_DLGMODALFRAME,
                TEXT("button"),                                                 // The class name required is button
                TEXT("Paris"),                                                    // the caption of the button
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW,           // the styles
                190, 70,                                                        // the left and top co-ordinates
                80, 30,                                                         // width and height
                hwnd,                                                           // parent window handle
                (HMENU)IDC_PARIS_BUTTON,                                          // the ID of your button
                hInst,                                                          // the instance of your application
                NULL);


                        hwndBerlinButton = CreateWindowEx(
                (DWORD)WS_EX_DLGMODALFRAME,
                TEXT("button"),                                                 // The class name required is button
                TEXT("Berlin"),                                                    // the caption of the button
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW,           // the styles
                350, 70,                                                        // the left and top co-ordinates
                80, 30,                                                         // width and height
                hwnd,                                                           // parent window handle
                (HMENU)IDC_BERLIN_BUTTON,                                          // the ID of your button
                hInst,                                                          // the instance of your application
                NULL);

                    hwndBuButton = CreateWindowEx(
                (DWORD)WS_EX_DLGMODALFRAME,
                TEXT("button"),                                                 // The class name required is button
                TEXT("Choose"),                                                    // the caption of the button
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW,           // the styles
                440, 280,                                                        // the left and top co-ordinates
                70, 48,                                                         // width and height
                hwnd,                                                           // parent window handle
                (HMENU)IDC_BU_BUTTON,                                          // the ID of your button
                hInst,                                                          // the instance of your application
                NULL);
			break;




// WM_SIZE??

        /*This message limits the window's minimal height and width** */

            case WM_GETMINMAXINFO: {
                ((MINMAXINFO*)lParam)->ptMinTrackSize.x = 554;
                ((MINMAXINFO*)lParam)->ptMinTrackSize.y = 376;

            break;
            }


    case WM_COMMAND:

			//Handling button presses
            switch(LOWORD(wParam))
			{
                case IDC_ADD_BUTTON:

				  //sending the message from the edit box to the list box
                    textSize = SendMessage(hwndInputText, WM_GETTEXT, 100, (LPARAM)message);
                    message[textSize] = _T('\0');

                    if(strlen(message) && strcmp(message, placeholder))
                    {
                        char *item = new char[200];
                        if(items)
							strcpy(item, "\r\n > ");
                        else
							strcpy(item, " > ");         // Managing the new string
                        strcat(item, message);
                        SendMessage(hwndOutputText, EM_REPLACESEL,
                            TRUE, (LPARAM)item);                                     // Appending a new item in the list
                        SendMessage(hwndInputText, WM_SETTEXT, TRUE,(LPARAM)"");     // Clearing the text input
                        delete [] item;                                              // Managing the memory
                        items += 1;                                                  // Incrementing the number of items
                        SendMessage(
                            hwndInputText,
                            WM_SETTEXT,
                            TRUE,
                            (LPARAM)placeholder);                                    // Recovering the placeholder
                        focused = 0;
                    }
                    RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
                    break;

                case IDC_CLEAR_BUTTON:
                    SendMessage(hwndOutputText, WM_SETTEXT, 0, (LPARAM)"");
                    break;

                case IDC_INPUT_TEXT:
                    if(HIWORD(wParam) == EN_SETFOCUS)
                    {
                        textSize = SendMessage(hwndInputText, WM_GETTEXT, 100, (LPARAM)message);
                        message[textSize] = _T('\0');

                        if(!strcmp(message, placeholder))
                        {
                            SendMessage(hwndInputText, WM_SETTEXT, TRUE,(LPARAM)"");         // Clearing the text input
                            focused = 1;
                            RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
                        }
                    }
                    else if(HIWORD(wParam) == EN_KILLFOCUS)
                    {
                        textSize = SendMessage(hwndInputText, WM_GETTEXT, 100, (LPARAM)message);
                        message[textSize] = _T('\0');

                        if(!strcmp(message, ""))
                        {
                            SendMessage(
                                hwndInputText,
                                WM_SETTEXT,
                                TRUE,
                                (LPARAM)placeholder);                                         // Recovering the placeholder
                            focused = 0;
                            RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
                        }
                    }
                    break;

                case IDC_LONDON_BUTTON:

                    SendMessage(hwndOutputText, WM_SETTEXT, 0, (LPARAM)" London, England’s capital, set on the River Thames, "
                                                                       " is a 21st-century city with history stretching back to Roman times."
                                                                       " At its centre stand the imposing Houses of Parliament, the iconic ‘Big Ben’ "
                                                                       " clock tower and Westminster Abbey, site of British monarch coronations."
                                                                       " Across the Thames, the London Eye observation wheel provides panoramic views "
                                                                       " of the South Bank cultural complex, and the entire city."
                                                                       " London attracts 27 million overnight-stay visitors every year."
                                                                       " London is a major global centre of higher education teaching and research and "
                                                                       " its 43 universities form the largest concentration of higher education institutes in Europe.");
            break;

            case IDC_PARIS_BUTTON:

                    SendMessage(hwndOutputText, WM_SETTEXT, 0, (LPARAM)" Paris is the capital and most populous city of France. "
                                                                       " Situated on the Seine River, in the north of the country, it is in the centre of the Île-de-France region, also known as the région parisienne, Paris Region."
                                                                       " Since the 19th century, the built-up area of Paris has grown far beyond its administrative borders;"
                                                                       " together with its suburbs, the whole agglomeration has a population of 10,550,350"
                                                                       " Paris was founded in the 3rd century BC by a Celtic people called the Parisii, who gave the city its name."
                                                                       " By the 12th century, Paris was the largest city in the western world, a prosperous trading centre, "
                                                                       " and the home of the University of Paris, one of the first in Europe."
                                                                       " In the 18th century, it was the centre stage for the French Revolution, and became an important centre of "
                                                                       " finance, commerce, fashion, science, and the arts, a position it still retains today. "
                                                                       " The city is a major rail, highway, and air-transport hub, served by the two international airports Paris-Charles de Gaulle and Paris-Orly." );



            break;

            case IDC_BERLIN_BUTTON:

                    SendMessage(hwndOutputText, WM_SETTEXT, 0, (LPARAM)" Berlin is the capital of Germany and one of the 16 states of Germany. With a population of 3.5 million people,"
                                                                       " it is the second most populous city proper and the seventh most populous urban area in the European Union."
                                                                       " Located in northeastern Germany on the banks of Rivers Spree and Havel, it is the centre of the"
                                                                       " Berlin-Brandenburg Metropolitan Region, which has about six million residents from over 180"
                                                                       " nations.Due to its location in the European Plain, Berlin is influenced by a temperate seasonal"
                                                                       " climate. Around one-third of the city's area is composed of forests, parks, gardens, rivers and lakes.");




            break;

            case IDC_BU_BUTTON:
                    if (MessageBox(NULL, TEXT("Are you sure you want to choose that destination?"), TEXT("The city you love"), MB_YESNO | MB_DEFBUTTON2 | MB_ICONWARNING) == IDYES) {
                        return MessageBox(NULL, TEXT("Great Decision !!!"), TEXT("Congratulations!"), MB_OK | MB_ICONASTERISK);
                    };
                   break;
            }
            break;

    case WM_CTLCOLOREDIT:
            if(GetDlgCtrlID((HWND)lParam) == IDC_INPUT_TEXT)
            {
                hdc = (HDC)wParam;                                              //Get handles
                if(focused)
                {
                    color = CreateSolidBrush(RGB(255, 255, 255));
                    SetTextColor(hdc, RGB(0,0,0));                              // Text color
                    SetBkMode(hdc, TRANSPARENT);                                // EditBox Backround Mode
                    SetBkColor(hdc,(LONG)color);                                // Backround color for EditBox
                }
                else
                {
                    color = CreateSolidBrush(RGB(255, 255, 255));
                    SetTextColor(hdc, RGB(110,123,139));                        // Text color
                    SetBkMode(hdc, TRANSPARENT);                                // EditBox Backround Mode
                    SetBkColor(hdc,(LONG)color);                                // Backround color for EditBox
                }
                return (LONG)color;                                             // Paint it
            }
            break;

        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);
            GetClientRect(hwnd, &rect);                                                                        // Getting coordinates of window client area
            SetBkMode(hdc, TRANSPARENT);                                                                       // Set the background to be transparent
            SetTextColor(hdc, RGB(255,231,186));                                                               // Setting the text color to a pale orange
			DrawText(hdc, "\nTravel and discover", -1, &rect, DT_CENTER | DT_TOP);                                    // Drawing the text on top aligning it to center
            textFont  = CreateFont(0, 0, 0, 0, FW_SEMIBOLD, TRUE, 0, 0, 0, 0, 0, 0, 0, "Times New Roman");     // Creating the text font to semibold, italic, choosing Times New Roman font
            hFontOld  = (HFONT)SelectObject(hdc,textFont);                                                     // Setting the text font
            SetTextColor(hdc,RGB(238,173,14));                                                                 // Setting the text color to a dark orange
            SetBkMode(hdc, TRANSPARENT);                                                                       // Set the background to be transparent
            DrawText(hdc, "\n\nChoose your destination", -1, &rect, DT_CENTER | DT_TOP);                       // Drawing the text on top aligning it to center
            SetTextColor(hdc, RGB(0, 100, 0));                                                                 // Resetting the color to black
			EndPaint(hwnd, &ps);
            break;


                    case WM_DRAWITEM:
            if ((UINT)wParam == IDC_LONDON_BUTTON) {
                LPDRAWITEMSTRUCT lpdis = (DRAWITEMSTRUCT*)lParam;
                SIZE size;
                char szLondonBtnText[7];
                strcpy(szLondonBtnText, "London");
                GetTextExtentPoint32(lpdis->hDC, szLondonBtnText, strlen(szLondonBtnText), &size);
                SetTextColor(lpdis->hDC, RGB(245,245,220));
                SetBkColor(lpdis->hDC, RGB(150,104,108));

                ExtTextOut(
                    lpdis->hDC,
                    ((lpdis->rcItem.right - lpdis->rcItem.left) - size.cx) / 2,
                    ((lpdis->rcItem.bottom - lpdis->rcItem.top) - size.cy) / 2,
                    ETO_OPAQUE | ETO_CLIPPED,
                    &lpdis->rcItem,
                    szLondonBtnText,
                    strlen(szLondonBtnText),
                    NULL);

                DrawEdge(
                    lpdis->hDC,
                    &lpdis->rcItem,
                    (lpdis->itemState & ODS_SELECTED ? EDGE_SUNKEN : EDGE_RAISED ),
                    BF_RECT);
                return TRUE;
			}

			else if ((UINT)wParam == IDC_PARIS_BUTTON) {
                LPDRAWITEMSTRUCT lpdis = (DRAWITEMSTRUCT*)lParam;
                SIZE size;
                char szParisBtnText[6];
                strcpy(szParisBtnText, "Paris");
                GetTextExtentPoint32(lpdis->hDC, szParisBtnText, strlen(szParisBtnText), &size);
                SetTextColor(lpdis->hDC, RGB(245,245,220));
                SetBkColor(lpdis->hDC, RGB(150,104,108));

                ExtTextOut(
                    lpdis->hDC,
                    ((lpdis->rcItem.right - lpdis->rcItem.left) - size.cx) / 2,
                    ((lpdis->rcItem.bottom - lpdis->rcItem.top) - size.cy) / 2,
                    ETO_OPAQUE | ETO_CLIPPED,
                    &lpdis->rcItem,
                    szParisBtnText,
                    strlen(szParisBtnText),
                    NULL);

                DrawEdge(
                    lpdis->hDC,
                    &lpdis->rcItem,
                    (lpdis->itemState & ODS_SELECTED ? EDGE_SUNKEN : EDGE_RAISED ),
                    BF_RECT);

                return TRUE;

			}

			else if ((UINT)wParam == IDC_BERLIN_BUTTON) {
                LPDRAWITEMSTRUCT lpdis = (DRAWITEMSTRUCT*)lParam;
                SIZE size;
                char szBerlinBtnText[7];
                strcpy(szBerlinBtnText, "Berlin");
                GetTextExtentPoint32(lpdis->hDC, szBerlinBtnText, strlen(szBerlinBtnText), &size);
                SetTextColor(lpdis->hDC, RGB(245,245,220));
                SetBkColor(lpdis->hDC, RGB(150,104,108));

                ExtTextOut(
                    lpdis->hDC,
                    ((lpdis->rcItem.right - lpdis->rcItem.left) - size.cx) / 2,
                    ((lpdis->rcItem.bottom - lpdis->rcItem.top) - size.cy) / 2,
                    ETO_OPAQUE | ETO_CLIPPED,
                    &lpdis->rcItem,
                    szBerlinBtnText,
                    strlen(szBerlinBtnText),
                    NULL);

                DrawEdge(
                    lpdis->hDC,
                    &lpdis->rcItem,
                    (lpdis->itemState & ODS_SELECTED ? EDGE_SUNKEN : EDGE_RAISED ),
                    BF_RECT);

                return TRUE;

			}

			else if ((UINT)wParam == IDC_BU_BUTTON) {
                LPDRAWITEMSTRUCT lpdis = (DRAWITEMSTRUCT*)lParam;
                SIZE size;
                char szBuBtnText[7];
                strcpy(szBuBtnText, "Choose");
                GetTextExtentPoint32(lpdis->hDC, szBuBtnText, strlen(szBuBtnText), &size);
                SetTextColor(lpdis->hDC, RGB(245,245,220));
                SetBkColor(lpdis->hDC, RGB(50,174,208));

                ExtTextOut(
                    lpdis->hDC,
                    ((lpdis->rcItem.right - lpdis->rcItem.left) - size.cx) / 2,
                    ((lpdis->rcItem.bottom - lpdis->rcItem.top) - size.cy) / 2,
                    ETO_OPAQUE | ETO_CLIPPED,
                    &lpdis->rcItem,
                    szBuBtnText,
                    strlen(szBuBtnText),
                    NULL);

                DrawEdge(
                    lpdis->hDC,
                    &lpdis->rcItem,
                    (lpdis->itemState & ODS_SELECTED ? EDGE_SUNKEN : EDGE_RAISED ),
                    BF_RECT);

                return TRUE;

			}

             break;


             case WM_SYSCOMMAND:
            switch(wParam) {

                case SC_MINIMIZE:
                    return MessageBox(NULL, TEXT("STOP! Do not do it!"), TEXT("Minimize Button Clicked!"), MB_OK | MB_ICONSTOP);

                case SC_MAXIMIZE:
                    return MessageBox(NULL, TEXT("Hey! You just clicked Maximize button"), TEXT("Maximize Button Clicked!"), MB_OK | MB_ICONEXCLAMATION);

                case SC_CLOSE:
            if(MessageBox(hwnd, "Are you sure that you want to close this window?", "Close Travel App", MB_OKCANCEL) == IDOK)
                DestroyWindow(hwnd);
			break;

                default:
                    return DefWindowProc(hwnd, msg, wParam, lParam);
            }
            break;


        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, msg, wParam, lParam);
    }

    return 0;
}

#include <iostream>
#include <windows.h>
#include <cmath>
#include "header.h"



LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

static animationB *obj[60]; //limitation of balls
char szClassName[ ] = "Lab4";

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nCmdShow)
{
    HWND hwnd;
    MSG messages;
    WNDCLASSEX wincl;

    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;         // Catching double-clicks
    wincl.cbSize = sizeof (WNDCLASSEX);
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = CreateSolidBrush( RGB(255, 255, 255) );


    if (!RegisterClassEx (&wincl))
        return 0;

       hwnd = CreateWindowEx (
           0,
           szClassName,
           "Laboratory Work 4",
           WS_OVERLAPPEDWINDOW,
           CW_USEDEFAULT,
           CW_USEDEFAULT,
           800,
           500,
           HWND_DESKTOP,
           NULL,
           hThisInstance,
           NULL
           );

    ShowWindow (hwnd, nCmdShow);

    while (GetMessage (&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }

    return messages.wParam;
}

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HDC hdc;
    static HDC hdcMem;
    static PAINTSTRUCT ps;
    static RECT rect;
    static HBRUSH hBrush;
    static HBITMAP hndbmMem;
    static HANDLE hndOld;
    static int timerSpeed=20;
    static int nrBall=0;


    switch (message)
    {
          case WM_CREATE:

            hdc=GetDC(hwnd);
            GetClientRect(hwnd,&rect);
            hdcMem=CreateCompatibleDC(hdc);
            hndbmMem=CreateCompatibleBitmap(hdc,rect.right,rect.bottom);
            hndOld = SelectObject(hdcMem,hndbmMem);
            SetTimer(hwnd,ID_TIMER,timerSpeed,NULL);
            break;


        case WM_SIZE:

            SelectObject(hdcMem,hndOld);
            DeleteObject(hndbmMem);
            DeleteDC(hdcMem);
            hdc=GetDC(hwnd);
            GetClientRect(hwnd,&rect);
            hdcMem=CreateCompatibleDC(hdc);
            hndbmMem=CreateCompatibleBitmap(hdc,rect.right,rect.bottom);
            hndOld = SelectObject(hdcMem,hndbmMem);
            break;


        case WM_LBUTTONDOWN:

            POINT newCenter;
            newCenter.x=LOWORD(lParam);
            newCenter.y=HIWORD(lParam);

            obj[nrBall]=new Circle(newCenter, 5 + newCenter.x % 5);
            obj[nrBall]->BallColor(RGB(newCenter.x % 255, newCenter.x % 125 + newCenter.y % 125, newCenter.y % 255));
            nrBall++;
            break;


        case WM_MOUSEWHEEL:
            if((short)HIWORD(wParam)<0) {
                timerSpeed += 10;
            }else {
                timerSpeed -= 10;
                if (timerSpeed < 0) timerSpeed = 1;
            }

            KillTimer(hwnd,ID_TIMER);
            SetTimer(hwnd,ID_TIMER,timerSpeed,NULL);
            break;


        case WM_PAINT:

            hdc=BeginPaint(hwnd,&ps);
            GetClientRect(hwnd,&rect);

            for(int i=0;i<nrBall-1;i++) {
                for(int j=i+1;j<nrBall;j++) {
                    Interaction(*obj[i],*obj[j]);
                }
            }

            FillRect(hdcMem,&rect,(HBRUSH)GetStockObject(WHITE_BRUSH));


            for(int i=0;i<nrBall;i++) {
                obj[i]->moveB(hdcMem,rect,hBrush);
            }

            BitBlt(hdc,0,0,rect.right,rect.bottom,hdcMem,0,0,SRCCOPY);
            EndPaint(hwnd,&ps);
            break;


        case WM_TIMER:

            InvalidateRect(hwnd,NULL,FALSE);
            break;


        case WM_DESTROY:


            SelectObject(hdcMem,hndOld);
            DeleteObject(hndbmMem);
            DeleteDC(hdcMem);
            KillTimer(hwnd,ID_TIMER);

            PostQuitMessage (0);
            break;

        default:
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}


animationB::animationB(POINT center,const int &speed) {

    this->center=center;
    this->SpeedX=speed;
    this->SpeedY=speed;
    Bcolor=RGB(0,0,0);

}

bool animationB::accelerateB(const int& DSpeedX,const int& DSpeedY) {
    SpeedX=DSpeedX;
    SpeedY=DSpeedY;
    return TRUE;
}

bool animationB::BallColor(const COLORREF &Bcolor) {
    this->Bcolor=Bcolor;
    return TRUE;
}

bool Circle::moveB(const HDC &hdc,const RECT& rect,HBRUSH &hBrush) {

    hBrush=CreateSolidBrush(Bcolor);
    SelectObject(hdc,hBrush);
    BallCollision(rect);
    center.x-=SpeedX;
    center.y-=SpeedY;

    if(transBall)
    {
        Rectangle(hdc, center.x - 30, center.y - 30, center.x + 30, center.y + 30 );
        SelectObject(hdc, GetStockObject(WHITE_BRUSH));
        DeleteObject(hBrush);
        return TRUE;
    }

    Ellipse(hdc,center.x - 30, center.y - 30, center.x + 30, center.y + 30);
    SelectObject(hdc,GetStockObject(WHITE_BRUSH));
    DeleteObject(hBrush);
    return TRUE;

}

bool animationB::BallCollision(const RECT &rect) {

    if(center.x - 20 > rect.right - 1)
        {
            SpeedX=abs(SpeedX);
            transBall = true;     }

    if(center.x + 20 < rect.left + 1)
        {
            SpeedX=-abs(SpeedX);
            transBall = true;    }

    if(center.y + 20 > rect.bottom - 1)
        {
            SpeedY=abs(SpeedY + 5);
                }

    if(center.y - 20 < rect.top + 1)
        {
            SpeedY=-abs(SpeedY + 5) ;
                }

    return TRUE;
}

bool Interaction(animationB &first,animationB &second) {

    float distance;
    POINT totalSpeed;

    distance = sqrt( pow(first.center.x-second.center.x,2)+ pow(first.center.y-second.center.y,2) );


    if ( distance < 9 ) {
    totalSpeed.x=(abs(first.SpeedX)+abs(second.SpeedX))/2;
    totalSpeed.y=(abs(first.SpeedY)+abs(second.SpeedY))/2;

    first.accelerateB(-first.SpeedX*totalSpeed.x/abs(first.SpeedX),-first.SpeedY*totalSpeed.y/abs(first.SpeedY));
    second.accelerateB(-second.SpeedX*totalSpeed.x/abs(second.SpeedX),-second.SpeedY*totalSpeed.y/abs(second.SpeedY));

    first.BallColor(RGB(totalSpeed.x * 50 % 255, totalSpeed.x * 50 % 255, totalSpeed.x * 50 % 255));
    }

    return TRUE;
}

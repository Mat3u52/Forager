#include <windows.h>
#include <io.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include "AXIRecipe.h"
#include <filesystem>
namespace fs = std::filesystem;

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
char szClassName[ ] = "WindowsApp";

int WINAPI WinMain(HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nFunsterStil){
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;

    // Inicjowanie GDIplus.
    GdiplusStartup( & gdiplusToken, & gdiplusStartupInput, NULL );

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof(WNDCLASSEX);

    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wincl.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(1074));
	wincl.hIconSm = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(1074));

    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /*danePliku.name* structure or the window instance */
    /* Use Windows's default color as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

//-----------Only one instance--------------------------------------
	HANDLE hMutex = CreateMutex(NULL, FALSE, "Forager_v02");
	if(hMutex && GetLastError() != 0){
		PostQuitMessage( 0 );
		return 0;
	}
//-----------Only one instance / the end------------------------------

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx(&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx(
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           NazwaProgramu,       /* Title Text */
           WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           MaxX+8,                 /* The programs width */
           MaxY+34,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow(hwnd, nFunsterStil);

    HMENU menu = LoadMenu(hThisInstance, MAKEINTRESOURCE(ID_MENU));
    SetMenu(hwnd, menu);

    DirMap();
    //std::cout << "Data: " << data;
    /* Run the message loop. It will run until GetMessage() returns 0 */
    while(GetMessage (&messages, NULL, 0, 0)){
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    GdiplusShutdown(gdiplusToken);
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    HDC hdc;
    PAINTSTRUCT ps;
    DWORD p;
    HFONT hFont, hFontSmall;
    int offset = 50;

    RECT rect0[0];
    rect0[0].left = 215;
    rect0[0].right = 255; //255
    rect0[0].top = 33;
    rect0[0].bottom = 53;

    static int x_kursora, y_kursora, ile;

    int k = 1;

    int nrPic = 0;
    int nrPic1 = 0;
    int nrPic2 = 0;
    int nrPic3 = 0;
    int nrPic4 = 0;
    int nrPic5 = 0;
    int nrPic6 = 0;
    int nrPic7 = 0;
    int nrPic8 = 0;
    int nrPic9 = 0;

    switch(message){
        case WM_CREATE:
            //static HINSTANCE hInst = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);
            static HINSTANCE hInst = (HINSTANCE)GetWindowLong(hwnd, GWLP_HINSTANCE);
            //uruchom w¹tek pierwszego zegara
            CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Zegar1, hwnd, 0, &p);
            /* Deklaracja zmiennej struktury LOGFONT*/
            static LOGFONT lf;
            lf.lfHeight = 30;
            lf.lfWidth = 0;
            lf.lfEscapement = 0;
            lf.lfOrientation = 0;
            lf.lfWeight = 0;
            lf.lfItalic = 0;
            lf.lfUnderline = 0;
            lf.lfStrikeOut = 0;
            lf.lfCharSet = 0;
            lf.lfOutPrecision = 0;
            lf.lfClipPrecision = 0;
            lf.lfQuality = 0;
            lf.lfPitchAndFamily = 0;
            lstrcpy(lf.lfFaceName, TEXT("Crystal"));

            static LOGFONT lfsmall;
            lfsmall.lfHeight = 15;
            lfsmall.lfWidth = 0;
            lfsmall.lfEscapement = 0;
            lfsmall.lfOrientation = 0;
            lfsmall.lfWeight = 0;
            lfsmall.lfItalic = 0;
            lfsmall.lfUnderline = 0;
            lfsmall.lfStrikeOut = 0;
            lfsmall.lfCharSet = 0;
            lfsmall.lfOutPrecision = 0;
            lfsmall.lfClipPrecision = 0;
            lfsmall.lfQuality = 0;
            lfsmall.lfPitchAndFamily = 0;
            lstrcpy(lfsmall.lfFaceName, TEXT("Crystal"));

            hwndEdytora = CreateWindowEx(0, "EDIT", NULL,
                                        WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE,
                                        5, 7, 250, 25, hwnd, NULL, hInst, NULL);
            SetFocus(hwndEdytora);

            break;
        case WM_MOUSEMOVE:
            x_kursora = LOWORD(lParam);
            y_kursora = HIWORD(lParam);
            //std::cout<< x_kursora + " " + y_kursora << std::endl;
            //InvalidateRect(hwnd, NULL, TRUE);
        case WM_COMMAND:
                switch(LOWORD(wParam)){
                    case IDB_BUTTON1:
                        if(range <= amount-10){
                            flagaAdd = 2;
                            range += 10;
                            show = 0;
                        }
                        break;
                    case IDB_BUTTON2:
                        if(range >= 10){
                            flagaAdd = 3;
                            range -= 10;
                            show = 0;
                        }
                        break;
                    case IDB_BUTTON3:
                            amount = 0;
                            DirMap();
                            SetWindowText(hwndEdytora, "");
                            InvalidateRect(hwnd, &rect0[0], TRUE);
                            flagaAdd = 1;
                        break;
                    case IDB_BUTTON4:
                            if(fileExists("RecipeDump.txt")){
                                remove("RecipeDump.txt");
                            }
                            for(int i = 0; i < amount; i++){
                                    Save(recipe[i].c_str());

                            }
                            SavePNG();
                        break;
                    case IDB_BUTTON5:
                            SavePlik(hwnd);
                            InvalidateRect(hwnd, NULL, TRUE);
                        break;
                    case IDB_BUTTON_OPROG:
                            MessageBox(hwnd, "Author: Mateusz Kolodziej \nCopyright (c) 2022 r.", "About Program", MB_OK);
                        break;
                    case IDB_BUTTON_KONIEC:
                        SendMessage(hwnd, WM_DESTROY, 0, 0);
                        break;
                }
            break;
        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);
            switch(flaga){
                case 1:
                    SetBkMode(hdc, TRANSPARENT);
                    hFont = CreateFontIndirect(&lf);
                    SelectObject(hdc, hFont);
                    TextOut(hdc, 270, 5, tekst, strlen(tekst));
                    DeleteObject(hFont);

                    GetWindowText(hwndEdytora, tekst0, MaxT);
                    std::string tekst0Str = tekst0;
                    //lineY = 42;
                    switch(flagaAdd){
                        case 1:
                            for(int i = 0; i < amount; i++){
                                strcpy(buffer, recipe[i].c_str());
                                int pozycja = recipe[i].find(tekst0Str);
                                if(pozycja!=std::string::npos){
                                    hFontSmall = CreateFontIndirect(&lfsmall);
                                    SelectObject(hdc, hFontSmall);
                                        sprintf(iStr, "%d", i+1);
                                        TextOut(hdc, 1, offset, iStr, strlen(iStr));
                                    DeleteObject(hFontSmall);
                                    hFont = CreateFontIndirect(&lf);
                                    SelectObject(hdc, hFont);
                                        TextOut(hdc, 20, offset, buffer, strlen(buffer));
                                    DeleteObject(hFont);


                                    offset += 50;
                                    range = 10;
                                    ile = k;
                                    //std::cout << k << std::endl;
                                    k++;

                                    if(nrPic == 0){
                                        nrPic = i;
                                    }else if(nrPic >= 0 && nrPic1 == 0){
                                        nrPic1 = i;
                                    }else if(nrPic >= 0 && nrPic1 > 0 && nrPic2 == 0){
                                        nrPic2 = i;
                                    }else if(nrPic >= 0 && nrPic1 > 0 && nrPic2 > 0 && nrPic3 == 0){
                                        nrPic3 = i;
                                    }else if(nrPic >= 0 && nrPic1 > 0 && nrPic2 > 0 && nrPic3 > 0 && nrPic4 == 0){
                                        nrPic4 = i;
                                    }else if(nrPic >= 0 && nrPic1 > 0 && nrPic2 > 0 && nrPic3 > 0 && nrPic4 > 0 && nrPic5 == 0){
                                        nrPic5 = i;
                                    }else if(nrPic >= 0 && nrPic1 > 0 && nrPic2 > 0 && nrPic3 > 0 && nrPic4 > 0 && nrPic5 > 0 && nrPic6 == 0){
                                        nrPic6 = i;
                                    }else if(nrPic >= 0 && nrPic1 > 0 && nrPic2 > 0 && nrPic3 > 0 && nrPic4 > 0 && nrPic5 > 0 && nrPic6 > 0 && nrPic7 == 0){
                                        nrPic7 = i;
                                    }else if(nrPic >= 0 && nrPic1 > 0 && nrPic2 > 0 && nrPic3 > 0 && nrPic4 > 0 && nrPic5 > 0 && nrPic6 > 0 && nrPic7 > 0 && nrPic8 == 0){
                                        nrPic7 = i;
                                    }else if(nrPic >= 0 && nrPic1 > 0 && nrPic2 > 0 && nrPic3 > 0 && nrPic4 > 0 && nrPic5 > 0 && nrPic6 > 0 && nrPic7 > 0 && nrPic8 > 0 && nrPic9 == 0){
                                        nrPic7 = i;
                                    }

                                    if(strlen(tekst0) == 0){
                                        flagaAdd = 4;
                                        k=0;
                                    }
                                }
                            }
                            if(x_kursora > 20 && y_kursora > 50 && ile <= 10){
                                //Rysuj(hdc, x_kursora, y_kursora, 0, ile);

                                if(y_kursora>50 && y_kursora<100){
                                    Rysuj(hdc, x_kursora, y_kursora, nrPic, ile);
                                }
                                if(y_kursora>100 && y_kursora<150){
                                    Rysuj(hdc, x_kursora, y_kursora, nrPic1, ile);
                                }
                                if(y_kursora>150 && y_kursora<200){
                                    Rysuj(hdc, x_kursora, y_kursora, nrPic2, ile);
                                }
                                if(y_kursora>200 && y_kursora<250){
                                    Rysuj(hdc, x_kursora, y_kursora, nrPic3, ile);
                                }
                                if(y_kursora>250 && y_kursora<300){
                                    Rysuj(hdc, x_kursora, y_kursora, nrPic4, ile);
                                }
                                if(y_kursora>300 && y_kursora<350){
                                    Rysuj(hdc, x_kursora, y_kursora, nrPic5, ile);
                                }
                                if(y_kursora>350 && y_kursora<400){
                                    Rysuj(hdc, x_kursora, y_kursora, nrPic6, ile);
                                }
                                if(y_kursora>400 && y_kursora<450){
                                    Rysuj(hdc, x_kursora, y_kursora, nrPic7, ile);
                                }
                                if(y_kursora>450 && y_kursora<500){
                                    Rysuj(hdc, x_kursora, y_kursora, nrPic8, ile);
                                }
                                if(y_kursora>500 && y_kursora<550){
                                    Rysuj(hdc, x_kursora, y_kursora, nrPic8, ile);
                                }
                                ile = 0;
                                show = 0;
                            }

                            break;
                        case 2:
                            for(int i = 0; i < amount; i++){
                                strcpy(buffer, recipe[i].c_str());
                                int pozycja = recipe[i].find(tekst0Str);
                                if(pozycja!=std::string::npos){
                                    if(i <= range && i >= range - 9){

                                    hFontSmall = CreateFontIndirect(&lfsmall);
                                    SelectObject(hdc, hFontSmall);
                                        sprintf(iStr, "%d", i+1);
                                        TextOut(hdc, 1, offset, iStr, strlen(iStr));
                                    DeleteObject(hFontSmall);
                                    hFont = CreateFontIndirect(&lf);
                                    SelectObject(hdc, hFont);
                                        TextOut(hdc, 20, offset, buffer, strlen(buffer));
                                    DeleteObject(hFont);

                                    if(x_kursora > 20 && y_kursora > 50){
                                        Rysuj(hdc, x_kursora, y_kursora, i);
                                    }

                                    offset += 50;
                                    }
                                }else{
                                    flagaAdd = 1;
                                }
                            }
                            break;
                            case 3:
                            for(int i = range; i < amount; i++){
                                strcpy(buffer, recipe[i].c_str());
                                int pozycja = recipe[i].find(tekst0Str);
                                if(pozycja!=std::string::npos){
                                    if(i >= range && i <= range + 9){

                                    hFontSmall = CreateFontIndirect(&lfsmall);
                                    SelectObject(hdc, hFontSmall);
                                        sprintf(iStr, "%d", i+1);
                                        TextOut(hdc, 1, offset, iStr, strlen(iStr));
                                    DeleteObject(hFontSmall);
                                    hFont = CreateFontIndirect(&lf);
                                    SelectObject(hdc, hFont);
                                        TextOut(hdc, 20, offset, buffer, strlen(buffer));
                                    DeleteObject(hFont);

                                    if(x_kursora > 20 && y_kursora > 50){
                                        Rysuj(hdc, x_kursora, y_kursora, i);
                                    }

                                    offset += 50;
                                    }
                                }else{
                                    flagaAdd = 1;
                                }
                            }
                            break;
                            case 4:
                            for(int i = 0; i < amount; i++){
                                strcpy(buffer, recipe[i].c_str());
                                int pozycja = recipe[i].find(tekst0Str);
                                if(pozycja!=std::string::npos){
                                    if(i < 10){
                                    hFontSmall = CreateFontIndirect(&lfsmall);
                                    SelectObject(hdc, hFontSmall);
                                        sprintf(iStr, "%d", i+1);
                                        TextOut(hdc, 1, offset, iStr, strlen(iStr));
                                    DeleteObject(hFontSmall);
                                    hFont = CreateFontIndirect(&lf);
                                    SelectObject(hdc, hFont);
                                        TextOut(hdc, 20, offset, buffer, strlen(buffer));
                                    DeleteObject(hFont);

                                    if(x_kursora > 20 && y_kursora > 50){

                                        if(y_kursora>50 && y_kursora<100){
                                            Rysuj(hdc, x_kursora, y_kursora, 0);
                                        }
                                        if(y_kursora>100 && y_kursora<150){
                                            Rysuj(hdc, x_kursora, y_kursora, 1);
                                        }
                                        if(y_kursora>150 && y_kursora<200){
                                            Rysuj(hdc, x_kursora, y_kursora, 2);
                                        }
                                        if(y_kursora>200 && y_kursora<250){
                                            Rysuj(hdc, x_kursora, y_kursora, 3);
                                        }
                                        if(y_kursora>250 && y_kursora<300){
                                            Rysuj(hdc, x_kursora, y_kursora, 4);
                                        }
                                        if(y_kursora>300 && y_kursora<350){
                                            Rysuj(hdc, x_kursora, y_kursora, 5);
                                        }
                                        if(y_kursora>350 && y_kursora<400){
                                            Rysuj(hdc, x_kursora, y_kursora, 6);
                                        }
                                        if(y_kursora>400 && y_kursora<450){
                                            Rysuj(hdc, x_kursora, y_kursora, 7);
                                        }
                                        if(y_kursora>450 && y_kursora<500){
                                            Rysuj(hdc, x_kursora, y_kursora, 8);
                                        }
                                        if(y_kursora>500 && y_kursora<550){
                                            Rysuj(hdc, x_kursora, y_kursora, 9);
                                        }
                                    }else{
                                        show = 0;
                                    }

                                    offset += 50;
                                    }
                                }else{
                                    flagaAdd = 1;
                                    show = 0;
                                }
                            }
                            break;
                    }
                    hFontSmall = CreateFontIndirect(&lfsmall);

                    SelectObject(hdc, hFontSmall);

                    sprintf(amountStr, "%d", amount);

                    TextOut(hdc, 220, 30, amountStr, strlen(amountStr));

                    DeleteObject(hFontSmall);
                    break;
            }
            EndPaint(hwnd, &ps);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

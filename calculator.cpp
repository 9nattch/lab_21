#include <windows.h>
#include<string>
#include<stdlib.h>

#define ID_INPUT1 101
#define ID_INPUT2 102
#define ID_BTN_ADD 103
#define ID_BTN_SUB 104
#define ID_BTN_MUL 105
#define ID_BTN_DIV 106
/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {

		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		case WM_ERASEBKGND: {
		    HDC hdc = (HDC)wParam;

		    HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0));
		    RECT rect;

		    GetClientRect(hwnd, &rect);
		    FillRect(hdc, &rect, hBrush);

		    return 1;

		}
		case WM_CREATE:
            CreateWindow("STATIC", "Please input two numbers",
                                    WS_VISIBLE | WS_CHILD, 20, 15, 200, 25, hwnd, NULL, NULL, NULL);
            CreateWindow("EDIT", "",
                                    WS_VISIBLE | WS_CHILD | ES_LEFT,
                                    45, 45, 150, 25, hwnd, (HMENU)ID_INPUT1, NULL, NULL);
            CreateWindow("EDIT", "",
                                    WS_VISIBLE | WS_CHILD | ES_LEFT,
                                    45, 75, 150, 25, hwnd, (HMENU)ID_INPUT2 , NULL, NULL);
            CreateWindow("BUTTON", "+",
                                      WS_VISIBLE | WS_CHILD |BS_PUSHBUTTON,
                                      60, 115, 25, 25, hwnd, (HMENU)ID_BTN_ADD, NULL, NULL);
            CreateWindow("BUTTON", "-",
                                      WS_VISIBLE | WS_CHILD |BS_PUSHBUTTON,
                                      90, 115, 25, 25, hwnd, (HMENU)ID_BTN_SUB, NULL, NULL);
            CreateWindow("BUTTON", "*",
                                      WS_VISIBLE | WS_CHILD |BS_PUSHBUTTON,
                                      120, 115, 25, 25, hwnd, (HMENU)ID_BTN_MUL, NULL, NULL);
            CreateWindow("BUTTON", "/",
                                      WS_VISIBLE | WS_CHILD |BS_PUSHBUTTON,
                                      150, 115, 25, 25, hwnd, (HMENU)ID_BTN_DIV, NULL, NULL);
        break;

        case WM_COMMAND:{
            int controlID = LOWORD(wParam);
            if(controlID >= ID_BTN_ADD && controlID <= ID_BTN_DIV){
            char buffer1[100], buffer2[100];
            GetWindowText(GetDlgItem(hwnd, ID_INPUT1), buffer1, 100);
            GetWindowText(GetDlgItem(hwnd, ID_INPUT2), buffer2, 100);

            double num1 = atof(buffer1);
            double num2 = atof(buffer2);
            double result;
            switch (controlID){
                case ID_BTN_ADD: result = num1 + num2; break;
                case ID_BTN_SUB: result = num1 - num2; break;
                case ID_BTN_MUL: result = num1 * num2; break;
                case ID_BTN_DIV:
                    if(num2 != 0){
                        result = num1 / num2;
                    }else{
                        MessageBox(hwnd, "Cannot divide by Zero!","Error", MB_OK | MB_ICONERROR);
                        return 0;
                    }
                    break;
            }

            char resultText[100];
            sprintf(resultText,"Result: %.6lf", result);
            MessageBox(hwnd, resultText, "Result", MB_OK);
            }
            break;

        }
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);

	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE|WS_CAPTION|
		WS_SYSMENU,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}

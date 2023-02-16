#include <windows.h>

/*

       cr0w
    _          _
   /.)        (.\
  /)\|        |/(\
 //)/          \(\\
/'"^"          "^"`\

*/

/*

SETUP THE WINDOWS PROCEDURE:

LRESULT CALLBACK WndProc(
   _In_ HWND   hWnd, // HANDLE TO THE WINDOW
   _In_ UINT   message, // THE MESSAGE CODE; FOR EXAMPLE, THE WM_SIZE MESSAGE INDICATES THE WINDOW WAS RESIZED, WM_DESTROY INDICATES A REQ. TO TERMINATE AN APPLICATION, ETC.
   _In_ WPARAM wParam, // ADDITIONAL DATA
   _In_ LPARAM lParam); // ADDITIONAL DATA

LRESULT IS AN INT VALUE THAT THE PROGRAM RETURNS TO WINDOWS. IT CONTAINS YOUR PROGRAM'S RESPONSE TO A PARTICULAR MESSAGE. 

*/

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    switch (uMsg)
    {
    case WM_DESTROY: // THIS IS A MESSAGE THAT WILL CAUSE THE GetMessage() FUNCTION TO RETURN 0. INDICATES A REQUEST TO TERMINATE AN APPLICATION.

        MessageBox(NULL, L"GOODBYE", L"SORRY TO SEE YOU GO : (",  MB_ICONEXCLAMATION); // DISPLAY A MESSAGE UPON TERMINATION REQUEST ---> MessageBox().
        
        PostQuitMessage(0); // INDICATES TO THE SYSTEM THAT A THREAD HAS MADE A REQUEST TO TERMINATE. ---> void PostQuitMessage(int nExitCode); PLACE THE MESSAGE BOX ABOVE THIS, OTHERWISE THE PROGRAM WILL CLOSE BEFORE THE BOX CAN SHOW.
        return 0;

    case WM_PAINT: // THIS MESSAGE IS SENT WHEN THE SYSTEM OR ANOTHER APPLICATION MAKES A REQUEST TO PAINT A PORTION OF AN APPLICATION'S WINDOW. 
        {

        PAINTSTRUCT ps; /* INITIALIZE THE PAINTSTRUCT STRUCTURE :
        
        typedef struct tagPAINTSTRUCT {
          HDC  hdc;
          BOOL fErase;
          RECT rcPaint;
          BOOL fRestore;
          BOOL fIncUpdate;
          BYTE rgbReserved[32];
        } PAINTSTRUCT, *PPAINTSTRUCT, *NPPAINTSTRUCT, *LPPAINTSTRUCT;

        */
       
        HDC hdc = BeginPaint(hwnd, &ps); // HANDLE TO THE DISPLAY DC TO BE USED FOR PAINTING.
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1)); /*
        int FillRect(
          [in] HDC        hDC, 
          [in] const RECT *lprc,
          [in] HBRUSH     hbr // HANDLE TO THE BRUSH USED TO FILL THE RECTANGLE
        );   
        */
        EndPaint(hwnd, &ps);

        }

        return 0;

        }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);

}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

    const wchar_t BLACKBIRD[] = L"CROWS WINDOW CLASS"; // CREATE A WNDCLASS STRUCTURE:

    /*
    typedef struct tagWNDCLASSA {
      UINT      style;
      WNDPROC   lpfnWndProc;
      int       cbClsExtra;
      int       cbWndExtra;
      HINSTANCE hInstance;
      HICON     hIcon;
      HCURSOR   hCursor;
      HBRUSH    hbrBackground;
      LPCSTR    lpszMenuName;
      LPCSTR    lpszClassName;
    } WNDCLASSA, *PWNDCLASSA, *NPWNDCLASSA, *LPWNDCLASSA;
    */

    LPMSG msg; /* 
    
    typedef struct tagMSG {
      HWND   hwnd;
      UINT   message;
      WPARAM wParam;
      LPARAM lParam;
      DWORD  time;
      POINT  pt;
      DWORD  lPrivate;
    } MSG, *PMSG, *NPMSG, *LPMSG; <--- 

    */

    WNDCLASS wc = { };

    wc.hInstance = hInstance; // HANDLE TO THE APPLICATION; GET THIS VALUE FROM THE HINSTANCE PARAM. OF ---> wWinMain().
    wc.lpfnWndProc = WndProc; // POINTER TO THE WINDOW PROCEDURE - WHICH DEFINES MOST OF THE BEHAVIOUR OF THE WINDOW.
    wc.lpszClassName = BLACKBIRD; 

    RegisterClass(&wc); // PASS &WNDCLASS STRUCTURE ---> RegisterClass() FUNCTION. THIS REGISTERS THE WINDOW CLASS WITH THE OPERATING SYSTEM.

    /*
    
    CREATE THE WINDOW; CALL CreateWindowEx().

    HWND CreateWindowExA(
      [in]           DWORD     dwExStyle,
      [in, optional] LPCSTR    lpClassName,
      [in, optional] LPCSTR    lpWindowName,
      [in]           DWORD     dwStyle,
      [in]           int       X,
      [in]           int       Y,
      [in]           int       nWidth,
      [in]           int       nHeight,
      [in, optional] HWND      hWndParent,
      [in, optional] HMENU     hMenu,
      [in, optional] HINSTANCE hInstance,
      [in, optional] LPVOID    lpParam);

    */

    HWND hwnd = CreateWindowEx(
        0, // PARENT WINDOW
        BLACKBIRD, // WINDOW CLASS
        L"CROW'S FIRST WINDOW!", // WINDOW TEXT
        WS_OVERLAPPEDWINDOW,  // WINDOW STYLE, YOU CAN ADD --> WS_VSCROLL (0x00200000L) | WS_HSCROLL (0x00100000L) FOR SCROLLBARS
        
        /* 
        
        WE CAN ALSO USE ADDRESS VALUES (CONSTANT VALUES) FOR THIS ---> WS_SYSMENU == 0x00080000L; FOR EXAMPLE, WE COULD ALSO DO THIS: 
        WS_OVERLAPPED | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU ---> 0x00000000L | 0x00020000L | 0x00010000L | 0x00080000L

        */

        // SIZE AND POSITION
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL, // PARENT WINDOW
        NULL, // MENU
        hInstance, // INSTANCE HANDLE
        NULL // ADDITIONAL APPLICATION DATA

    );

    if (hwnd == NULL) {

        MessageBox(NULL, L"SOMETHING WENT WRONG", L"ERROR", MB_ICONERROR); // SETUP WINDOWS MESSAGE BOX TO SIGNIFY ERROR ---> MessageBox().
        return 0;
    }

    else {

        MessageBox(NULL, L"LAUNCHING WINDOW...", L"SUCCESS", MB_ICONINFORMATION); // SETUP WINDOWS MESSAGE BOX TO SIGNIFY SUCCESS ---> MessageBox().

        /*
        
        SHOW THE WINDOW USING ShowWindow().

        BOOL ShowWindow(
          [in] HWND hWnd,     ---> THE WINDOW HANDLE THAT WAS RETURNED BY CreateWindowEx().
          [in] int  nCmdShow); ---> LETS US MINIMIZE/MAXIMIZE A WINDOW. THE OS PASSES THIS VALUE TO wWinMain().

        */

        ShowWindow(hwnd, nCmdShow); // SHOW THE WINDOW
        UpdateWindow(hwnd); // UPDATE THE WINDOW

        // RUN THE MESSAGE LOOP
        MSG msg = { };
        while (GetMessage(&msg, NULL, 0, 0) > 0) {

            TranslateMessage(&msg); /* THIS TRANSLATES VIRTUAL-KEY MESSAGES INTO CHARACTER MESSAGES; THEN THEY'RE POSTED TO THE CALLING THREAD'S MESSAGE QUEUE. 
            IT DOES NOT MODIFY THE MESSAGE POINTED BY THE lpMsg PARAMETER.
            BOOL TranslateMessage(
              [in] const MSG *lpMsg
            );
            */
            DispatchMessage(&msg); // SENDS MESSAGE TO THE WINDOW PROCEDURE.
        }

        return 0;

    }

}

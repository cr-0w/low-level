## DEMO


https://user-images.githubusercontent.com/59679082/219421536-4dc76718-3168-46ac-bda4-557ebb5b8e4a.mp4

## MY FIRST RUN OF THE WINDOW

https://user-images.githubusercontent.com/59679082/219421702-58f29e49-700c-4dbc-979c-2ddc3d612367.mp4

As we can see, this window initially lacked the buttons on the top-right of the window. I had my `CreateWindowEx()` setup to: 

```cpp
    HWND hwnd = CreateWindowEx(
        0,
        BLACKBIRD,
        L"CROW'S FIRST WINDOW!",
        WS_OVERLAPPED,

        // SIZE AND POSITION
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        
        NULL,
        NULL,
        hInstance,
        NULL
        );
```

After a bit of scouring the DOCS (more specifically, the [Window Styles](https://learn.microsoft.com/en-us/windows/win32/winmsg/window-styles)) I found that I had been using the wrong flag. I had been using `WS_OVERLAPPED` instead of the intended `WS_OVERLAPPEDWINDOW`.

![image](https://user-images.githubusercontent.com/59679082/219434625-e943cf76-961f-4575-866b-e5b2648ee13e.png)

My workaround for this was to use the additional flags for the required buttons I needed, which were the minimize, maximize, and close button:

```cpp
WS_OVERLAPPED | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU
```

And indeed, it *did work*:

```cpp
[snip ...]

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

    const wchar_t BLACKBIRD[] = L"CROWS WINDOW CLASS";

    LPMSG msg;
    WNDCLASS wc = { };

    wc.hInstance = hInstance;
    wc.lpfnWndProc = WndProc;
    wc.lpszClassName = BLACKBIRD;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        BLACKBIRD,
        L"CROW'S FIRST WINDOW!",
        WS_OVERLAPPED | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU, // FORCEFULLY SET THE WINDOW FLAGS ---> [MIN][MAX][CLOSE]

        // SIZE AND POSITION
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,
        NULL,
        hInstance,
        NULL

    );

    if (hwnd == NULL) {

[snip ...]
```

https://user-images.githubusercontent.com/59679082/219438995-11991676-c7f6-4976-88fa-19f4b09f3fb6.mp4

I then realized that, you don't need to do all of this, and that the *actual* flag I was supposed to be using from the start was `WS_OVERLAPPEDWINDOW` LOL. This style/flag seems to incorporate all the other flags I was using, and then some.

## THE FIX/FINAL

Another cool thing I learned is that, these flags expand out to "constant values":

![image](https://user-images.githubusercontent.com/59679082/219439486-bc639404-2ebe-4c79-b718-d70564c3e239.png)

I attempted to create a window (the previous `WS_OVERLAPPED | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU` contraption) using only these constant values and it also totally works! 

```cpp
WND hwnd = CreateWindowEx(
        0, // PARENT WINDOW
        BLACKBIRD, // WINDOW CLASS
        L"CROW'S FIRST WINDOW!", // WINDOW TEXT
        WS_OVERLAPPEDWINDOW,

        /* WE CAN ALSO USE ADDRESS VALUES (CONSTANT VALUES) FOR THIS ---> WS_SYSMENU == 0x00080000L; FOR EXAMPLE, WE COULD ALSO DO THIS: 

        WS_OVERLAPPED | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU ---> 0x00000000L | 0x00020000L | 0x00010000L | 0x00080000L

        */

        // SIZE AND POSITION
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL, // PARENT WINDOW
        NULL, // MENU
        hInstance, // INSTANCE HANDLE
        NULL // ADDITIONAL APPLICATION DATA

    );
```

![image](https://user-images.githubusercontent.com/59679082/219440394-4edbb44a-046d-412b-a31a-47ffad72387c.png)

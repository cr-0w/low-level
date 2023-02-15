## DEMO

https://user-images.githubusercontent.com/59679082/219112764-d5060c68-da0a-437e-bf9b-fcbafff4d19b.mp4

---

By default, WIN32 API functions use unicode. You'll see that functions will expand from: 

```cpp
functionName() --> functionNameW()
```

![image](https://user-images.githubusercontent.com/59679082/219121504-7a1bd310-7981-4f50-b410-1f2b2f09292b.png)

The `functionNameW()` means "wide", or in other words, unicode. Because of this, the strings that are supplied to these functions need to be encoded accordingly. Considering example_1.cpp:

```cpp
#include <windows.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

    MessageBox(nullptr, "BOX_CONTENTS", "BOX_TITLE", MB_OK); // by default win32 api funcs use unicode; so this will cause an error

    // this function will also tell you that it expands to: MessageBox --> MessageBoxW (W == wide string == unicode)

    return 0;
}
```

The strings: `"BOX_CONTENTS"` and `"BOX_TITLE"` aren't set properly and we would get an error. So, let's continue with possible fixes of these problems.


## TYPECASTING STRINGS  

We could forcefully set the strings to an "acceptable" value by using `(LPCWSTR)`:

```cpp
#include <windows.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

    MessageBox(nullptr, (LPCWSTR)"BOX_CONTENTS", (LPCWSTR)"BOX_TITLE", MB_OK); // can fix this by type-casting to LPCWSTR 

    // if you do this, it'll output some random garbage, so not recommended.

    return 0;
}
```

![image](https://user-images.githubusercontent.com/59679082/219120513-2798a492-c9d8-4cbf-a3ba-36009ba92603.png)

From this example, we can see that if we were to typecast the strings using the output is complete gibberish. Therefore, although it would get rid of an error; the output would be wrong. Let's try to keep the integrity of our strings.

## ANSI

![image](https://user-images.githubusercontent.com/59679082/219120889-d7fef7b9-67cc-4b9c-8ebd-b35b0347709a.png)

Here, we're able to actual use a different version of the same function: `MessageBoxA()`. The `A` denotes the usage of ANSI. 

```cpp
#include <windows.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

    MessageBoxA(nullptr, "BOX_CONTENTS", "BOX_TITLE", MB_OK); // you can change the function to use ANSI; MessageBoxA().

    // the code should work fine, however, ANSI is very outdated so this isn't recommended.
 
    return 0;
}
```

This will work perfectly fine. However, ANSI *is* a bit dated, so we should find another, more reliable method. Let's see the intended way: 

## UNICODE

The intended way is actually quite simple. All we have to do is prepend our strings with an `L`.

```cpp
#include <windows.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

    MessageBox(nullptr, L"BOX_CONTENTS", L"BOX_TITLE", MB_OK); // best way --> stick to MessageBox() [a.k.a MessageBoxW()]

    // prepend the strings with an "L" to turn them into unicode and viola! your code should be working.

    return 0;
}
```

![image](https://user-images.githubusercontent.com/59679082/219121106-c27caa35-61bd-4829-b4c5-4d4b0f585656.png)

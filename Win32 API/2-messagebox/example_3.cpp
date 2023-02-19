#include <windows.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

    MessageBoxA(NULL, "BOX_CONTENTS", "BOX_TITLE", MB_OK); // you can change the function to use ANSI; MessageBoxA().

    // the code should work fine, however, ANSI is very outdated so this isn't recommended.
 
    return 0;
}

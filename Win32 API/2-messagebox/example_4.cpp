#include <windows.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

    MessageBox(NULL, L"BOX_CONTENTS", L"BOX_TITLE", MB_OK); // best way --> stick to MessageBox() [a.k.a MessageBoxW()]

    // prepend the strings with an "L" to turn them into unicode and viola! your code should be working.

    return 0;
}

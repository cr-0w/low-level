#include <windows.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

    MessageBox(NULL, "BOX_CONTENTS", "BOX_TITLE", MB_OK); // by default win32 api funcs use unicode; so this will cause an error

    // this function will also tell you that it expands to: MessageBox --> MessageBoxW (W == wide string == unicode)

    return 0;
}

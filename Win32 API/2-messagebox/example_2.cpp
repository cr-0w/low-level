#include <windows.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

    MessageBox(NULL, (LPCWSTR)"BOX_CONTENTS", (LPCWSTR)"BOX_TITLE", MB_OK); // can fix this by type-casting to LPCWSTR 

    // if you do this, it'll output some random garbage, so not recommended.

    return 0;
}

#include <windows.h>

/*
 
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

return 0;

}

*/

// every windows program includes an entry-point function that is named either WinMain() or wWinMain() --> this is C/C++'s equivalent to main().

int WINAPI wWinMain(			         // this is the signature for wWinMain().

     HINSTANCE hInstance,		     // this is called a "handle to an instance/module." the OS uses this value to identify the EXE when it's loaded into memory. it's also required for many windows functions (as we'll see later on).
     HINSTANCE hPrevInstance,	  // apparently this has no meaning, it was used in 16-bit windows; but now is always 0.
    	PWSTR pCmdLine,				        // this is responsible for taking command-line args. it contains the cli-args as a unicode string.
    	int CmdShow					           // this is a flag that says whether the window will be minimized, maximized, or shown normally. 
) 

{	

    return 0;					              // i'll just have an empty windows main function that returns 0.

}

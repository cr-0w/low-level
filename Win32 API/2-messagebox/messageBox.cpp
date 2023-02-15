#include <windows.h>

/*
int MessageBox(
  [in, optional] HWND    hWnd,	       |    a handle to the owner window of the message box to be created; if this is set to NULL, then the box has no owner window.
  [in, optional] LPCTSTR lpText,       |    the message box's message itself.
  [in, optional] LPCTSTR lpCaption,    |    the message box's title.
  [in]           UINT    uType         |    The contents and behavior of the dialog box. This parameter can be a combination of flags from the following groups of flags.
);
*/

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

    /* the MessageBox function (which is really MessageBoxW -> W = wide; which is unicode) returns an integer value that indicates what button the user clicked.
    i.e., if the user clicked on "No", MessageBox() would return an int value of 7 (IDNO == 7). A list of some of the values can be seen below:

    ...
    [ok] button selected     ---returns---> IDOK (INT 1).
    [no] button selected     ---returns---> IDNO (INT 7).
    [yes] button selected    ---returns---> IDYES (INT 6).
    [cancel] button selected ---returns---> IDCANCEL (INT 2).
    ...
    
    */
	
    // asign the output of the MessageBox() function to a value called MessageID so that we can use the returned value for some case-switches.

    int MessageID = MessageBox(NULL, L"WOAH. THIS REALLY FUCKING SUCKS. DON'T YOU THINK SO?", L"CROW'S FIRST MESSAGE BOX!", MB_ICONQUESTION | MB_YESNO); // we can choose to have multiple *compatible* flags in one message box. 
	
    // based on the value of what the MessageBox() function returns, go to the appropriate case.

	switch (MessageID) { 

	case IDYES: // if the user pressed the yes button

		MessageBox(NULL, L"WHAT THE FUCK DID YOU JUST SAY?", L">:(", MB_ICONERROR | MB_HELP);
		return 0;

	case IDNO: // if the user pressed the no button

		MessageBox(NULL, L"I LOVE YOU <3", L":)", MB_ICONEXCLAMATION);
		return 0;

	}

}

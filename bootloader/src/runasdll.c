/*
 *	   Copyright (c) 2000-2013 Thomas Heller
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifdef _WIN32
    #include <windows.h>
#endif

#ifdef __FreeBSD__
    #include <floatingpoint.h>
#endif

#include "pyi_main.h"


#if defined(_WIN32)

#include <stdio.h>
#include <string.h>

HMODULE gInstance = NULL;

/*
  The main function for our exe.
*/
__declspec(dllexport) int WINAPI initPython ()
{
    /* Store arguments in global context structure. */
    global_pyi_ctx->argc = 0;
    global_pyi_ctx->argv_w = NULL;

    return pyi_main(global_pyi_ctx, gInstance);
}

__declspec(dllexport) int WINAPI runPython ()
{
	int result;

    printf("running");
	result = initPython();
	printf("initialization: %d\n", (int) result);

	return 0;
}

__declspec(dllexport) int WINAPI closePython ()
{
    printf("running");

	initPython();

	return 0;
}



// *****************************************************************
// All the public entry points needed for COM, Windows, and anyone
// else who wants their piece of the action.
// *****************************************************************
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	OutputDebugStringA("DllMain");
    if ( dwReason == DLL_PROCESS_ATTACH) {
		gInstance = hInstance;
	}
	else if ( dwReason == DLL_PROCESS_DETACH ) {
		gInstance = NULL;
	}
	return TRUE; 
}
#endif
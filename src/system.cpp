#ifdef _WIN32
#	include <Windows.h>
#	include <stdio.h>
#	include <io.h>
#	include <fcntl.h>
#endif // _WIN32


void init_console()
{
#ifdef _WIN32
	AllocConsole();

	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
#endif // _WIN32
}


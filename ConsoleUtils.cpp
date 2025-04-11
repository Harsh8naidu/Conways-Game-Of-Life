#include "ConsoleUtils.h"
#include <cstdlib>

void ClearConsole()
{
    // Clear the console for the depending on the OS
#if defined (_WIN32)
    system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
#elif defined (__APPLE__)
    system("clear");
#endif
}

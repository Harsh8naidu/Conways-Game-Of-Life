#include "ConsoleUtils.h"
#include <cstdlib>

#if defined (_WIN32)
    #include <conio.h>
#elif defined (defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)) || defined (__APPLE__)
    #include <termios.h>
    #include <unistd.h>
    #include <fcntl.h>
#endif

void ClearConsole() {
    // Clear the console for the depending on the OS
#if defined (_WIN32)
    system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
#elif defined (__APPLE__)
    system("clear");
#endif
}

bool IsEscapeKeyPressed() {
#if defined (_WIN32)
    if (_kbhit()) {
        int key = _getch();
        return key == 27; // ESC key
    }
    return false;

#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__) || defined(__APPLE__)
    // Set terminal to non-blocking, no echo
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Set stdin to non-blocking
    int oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    int ch = getchar();

    // Reset terminal
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        return ch == 27; // ESC key
    }
    return false;
#endif
}

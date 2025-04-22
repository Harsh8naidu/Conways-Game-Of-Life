#include "ConsoleUtils.h"
#include <cstdlib>

#if defined (_WIN32)
    #include <conio.h>
#elif defined (defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)) || defined (__APPLE__)
    #include <termios.h>
    #include <unistd.h>
    #include <fcntl.h>
#endif

// -----------------------
// Cross-platform Clear Console
// -----------------------
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

// ----------------------
// Windows Key Press Handling
// ----------------------
#if defined (_WIN32)

bool IsKeyPressed() {
    return _kbhit();
}

int GetKeyPressed() {
    if (_kbhit()) {
        return _getch();
    }
    return -1; // No key pressed
}

// ----------------------
// Linux/macOS Key Press Handling
// ----------------------
#elif defined (__linux__) || defined (__APPLE__)

bool IsKeyPressed() {
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    int oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    int ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin); // Put it back for GetKeyPressed
        return true;
    }
    return false;
}

int GetKeyPressed() {
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    int ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

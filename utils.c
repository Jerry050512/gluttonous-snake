#include <stdio.h>
#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#endif
#include <locale.h>
#include <wchar.h>

void gotoxy(int x, int y) {
    wprintf(L"\033[%d;%dH", y + 1, x + 1);
}

void hideCursor() {
    wprintf(L"\033[?25l");
}

void showCursor() {
    wprintf(L"\033[?25h");
}

void clearScreen() {
    wprintf(L"\033[2J");
}

int kbhit(void)
{
#if defined(_WIN32)
    return _kbhit();
#else
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
#endif
}
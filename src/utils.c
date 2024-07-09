#include <stdio.h>
#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#endif

int getch() {
    #if defined(_WIN32)
    int ch = _getch();
    #else
    int ch = getchar();
    #endif
    return ch;
}

void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y + 1, x + 1);
}

void hideCursor() {
    printf("\033[?25l");
}

void showCursor() {
    printf("\033[?25h");
}

void clearScreen() {
    printf("\033[2J");
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

void press_any_key_to_continue()
{
    while(kbhit()) getch();
    printf("Press any key to continue...");
    while (!kbhit());
    getch();
}

void press_space_to_continue()
{
    while(kbhit()) getch();
    printf("Press space to continue...");
    do {
        while (!kbhit());
    } while(getch() != ' ');
    
}
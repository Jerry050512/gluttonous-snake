#include <stdio.h>
#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#endif

int getch()
{
#if defined(_WIN32)
    // windows.h Win32 API
    int ch = _getch();
#else
    int ch = getchar();
#endif
    return ch;
}

void gotoxy(int x, int y)
{
    printf("\033[%d;%dH", y + 1, x + 1);
}

void hideCursor()
{
    printf("\033[?25l");
}

void showCursor()
{
    printf("\033[?25h");
}

void clearScreen()
{
    printf("\033[2J");
}

int kbhit(void)
{
#if defined(_WIN32)
    return _kbhit();
#else
    // Mannully implement kbhit()
    /* 设置标准输入为非阻塞模式，以便快速响应输入 */
    struct termios oldt, newt;
    int ch;
    int oldf;

    /* 获取当前标准输入的终端属性 */
    tcgetattr(STDIN_FILENO, &oldt);
    /* 创建一个新的终端属性，基于当前属性 */
    newt = oldt;
    /* 修改新属性，禁用回显和行编辑 */
    newt.c_lflag &= ~(ICANON | ECHO);
    /* 应用新的终端属性 */
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    /* 获取标准输入的文件描述符当前状态 */
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    /* 修改文件描述符状态，设置为非阻塞模式 */
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    /* 从标准输入读取一个字符 */
    ch = getchar();

    /* 恢复原来的终端属性 */
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    /* 恢复原来的文件描述符状态 */
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    /* 如果读取到字符，将其放回输入流并返回1 */
    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    /* 如果没有读取到字符，返回0 */
    return 0;
#endif
}

void press_any_key_to_continue()
{
    while (kbhit())
        getch();
    printf("Press any key to continue...");
    while (!kbhit())
        ;
    getch();
}

void press_space_to_continue()
{
    while (kbhit())
        getch();
    printf("Press space to continue...");
    do
    {
        while (!kbhit())
            ;
    } while (getch() != ' ');
}
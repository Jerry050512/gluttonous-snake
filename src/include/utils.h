#ifndef UTILS_H
#define UTILS_H

// Control the cursor
void gotoxy(int x, int y);
void hideCursor();
void showCursor();
void clearScreen();

// Non-Blocking I/O
int kbhit();
int getch();

// Waiting functions
void press_any_key_to_continue();
void press_space_to_continue();

#endif // UTILS_H
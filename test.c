#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include "utils.h"


int main() {
    setlocale(LC_ALL, "");
    clearScreen();
    for(int i=0; i<10; i++) {
        for(int j=0; j<10; j++) {
            if(i < 2 || i > 7 || j < 2 || j > 7) {
                gotoxy(i*2, j);
                wprintf(L"口");
            }
        }
    }
    wprintf(L"\n");
}
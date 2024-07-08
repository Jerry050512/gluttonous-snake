// #include <stdio.h>
// #include <stdlib.h>
// #include <locale.h>
// #include <wchar.h>
// #include "utils.h"


// int main() {
//     setlocale(LC_ALL, "");
//     clearScreen();
//     system("chcp 65001");
//     for(int i=0; i<10; i++) {
//         for(int j=0; j<10; j++) {
//             if(i < 2 || i > 7 || j < 2 || j > 7) {
//                 gotoxy(i*2, j);
//                 wprintf(L"口");
//             }
//         }
//     }
//     wprintf(L"\n");
// }

#include <stdio.h>

int main() {
    FILE* a = fopen("test.txt", "w");
    if(a != NULL) {
        fprintf(a, "H123\nd145\n");
    }
    fclose(a);
    FILE* b = fopen("test.txt", "r");
    int x, y;
    fscanf(b, "H%d\n", &x);
    fscanf(b, "d%d\n", &y);
    printf("%d %d", x, y);

}
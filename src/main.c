#include "menu.h"
#include "utils.h"
#include "structs.h"

Config config;

int main()
{
    hideCursor();
    while(display_menu()) ;
    showCursor();
    return 0;
}
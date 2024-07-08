#include "menu.h"
#include "utils.h"
#include "structs.h"
#include "settings.h"

Config config;

int main()
{
    hideCursor();
    read_config(&config);
    while(display_menu());
    showCursor();
    return 0;
}
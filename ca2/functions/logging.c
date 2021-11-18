#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

#include "logging.h"
#include "../main.h"

void ncursesInitialization()
{
    initscr();
    refresh();

    getbegyx(stdscr, y_min, x_min);
    getmaxyx(stdscr, y_max, x_max);

    printw("Hello\n");
    printw("Y min %d\n", y_min);

    refresh();
}
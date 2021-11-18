#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

#include "logging.h"
#include "../main.h"

void ncursesInitialization()
{
    initscr();
    clear();
    noecho();
    cbreak();

    getbegyx(stdscr, y_min, x_min);
    getmaxyx(stdscr, y_max, x_max);

    win = newwin(y_max - y_min, x_max - x_min, 0, 0);

    keypad(win, TRUE);

    mvwprintw(win, 1, x_max / 2 - 4, "Metronome");
    mvwhline(win, 2, 1, '-', x_max - 2);

    wrefresh(win);
}
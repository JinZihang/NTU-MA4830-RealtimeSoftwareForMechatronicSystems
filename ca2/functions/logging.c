#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

#include "logging.h"
#include "../main.h"

void ncursesInitialization() {
    int y_min, x_min, y_max, x_max, i;

    initscr();
    clear();
    noecho();
    cbreak();

    getbegyx(stdscr, y_min, x_min);
    getmaxyx(stdscr, y_max, x_max);
    if (y_max - y_min < 23 || x_max - x_min < 71) {
        printw("Terminal too small!");
        getch();
        exit(1);
    }

    if (!has_colors()) {
        printw("Terminal does not support color!");
        getch();
        exit(1);
    }
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE); // general
    init_pair(2, COLOR_WHITE, COLOR_BLACK); // selected waveform
    init_pair(3, COLOR_BLACK, COLOR_GREEN); // amp and freq bar-positive
    init_pair(4, COLOR_BLACK, COLOR_RED);   // amp and freq bar-negative

    keypad(stdscr, TRUE);

    // title
    mvprintw(1, x_max / 2 - 4, "Metronome");
    mvhline(2, 1, '-', x_max - 2);

    refresh();
}

#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

#include "logging.h"
#include "../main.h"

void NcursesInitialization() {
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

    // process information
    mvprintw(3, 5, "Process Information");
    mvhline(4, 1, '-', 26);
    mvvline(3, 27, '|', 6);

    // adjust instruction
    mvprintw(3, (x_max - 27) / 2 + 16, "Adjust Wave Attributes");
    mvhline(4, 28, '-', x_max - 29);
    mvprintw(5, 29, "* Waveform:\tSwitches");
    mvprintw(6, 29, "* Amplitude:\tPotentiometer-0");
    mvprintw(7, 29, "* Frequency:\tPotentiometer-1");
    mvprintw(8, 29, "\t\t\tor Vertical Arrow Keys");
    mvhline(9, 1, '-', x_max - 2);

    // realtime wave attributes
    mvprintw(10, x_max / 2 - 12, "Realtime Wave Attributes");
    mvhline(11, 1, '-', x_max - 2);

    // logging
    mvprintw(20, x_max / 2 - 3, "Logging");
    mvhline(21, 1, '-', x_max - 2);

    refresh();
}

void *UpdateDisplay() {

}

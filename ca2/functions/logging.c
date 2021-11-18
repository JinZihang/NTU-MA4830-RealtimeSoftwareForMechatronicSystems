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
    keypad(stdscr, TRUE);

    getbegyx(stdscr, y_min, x_min);
    getmaxyx(stdscr, y_max, x_max);
    if (y_max - y_min < 26 || x_max - x_min < 71) {
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

    // general
    box(stdscr, 0, 0);
    wbkgd(stdscr, COLOR_PAIR(1));

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
    mvprintw(7, 29, "* Frequency:\tVertical Arrow Keys");
    mvprintw(8, 29, "* Duty Cycle:\tPotentiometer-1");
    mvhline(9, 1, '-', x_max - 2);

    // realtime wave attributes
    mvprintw(10, x_max / 2 - 12, "Realtime Wave Attributes");
    mvhline(11, 1, '-', x_max - 2);
    mvhline(22, 1, '-', x_max - 2);

    // logging
    mvprintw(23, x_max / 2 - 3, "Logging");
    mvhline(24, 1, '-', x_max - 2);

    refresh();
}

void *UpdateDisplay() {
    init_pair(2, COLOR_WHITE, COLOR_BLACK); // selected waveform
    init_pair(3, COLOR_BLACK, COLOR_GREEN); // percentage bar-positive
    init_pair(4, COLOR_BLACK, COLOR_RED);   // percentage bar-negative

    while (1) {
        // process information
        mvprintw(7, 2, "* Remaining Time for the");
        mvprintw(8, 2, "  Current Wave (sec):\t%d", count_down);

        // waveform
        mvprintw(12, 2, "* Waveform:");
        mvprintw(12, 24, "Sine    Rectangle    Triangle    Sawtooth");
        attron(COLOR_PAIR(2));
        switch (wave.waveform) {
            case (Sine):
                mvprintw(12, 24, "Sine");
                break;
            case (Rectangle):
                mvprintw(12, 32, "Rectangle");
                break;
            case (Triangle):
                mvprintw(12, 45, "Triangle");
                break;
            case (Sawtooth):
                mvprintw(12, 57, "Sawtooth");
                break;
            default:
                // Warning-None waveform is selected!
                attroff(COLOR_PAIR(2));
                mvprintw(12, 24, "Sine    Rectangle    Triangle    Sawtooth");
                break;
        }
        attroff(COLOR_PAIR(2));

        // wave amplitude
        mvprintw(14, 2, "* Amplitude:\t%.2lf", wave.amplitude);
        mvprintw(14, 24, "|");
        attron(A_INVIS);
        for (i = 0; i < 40; i++) {
            if (i < (int) wave.amplitude * 40 / 2.5) {
                attron(COLOR_PAIR(3));
                mvprintw(14, 25 + i, "/");
                attroff(COLOR_PAIR(3));
            } else {
                attron(COLOR_PAIR(4));
                mvprintw(14, 25 + i, "-");
                attroff(COLOR_PAIR(4));
            }
        }
        attroff(A_INVIS);
        mvprintw(14, 64, "|");
        mvprintw(15, 24, "0                                     2.5");

        // wave frequency
        mvprintw(17, 2, "* Frequency:\t%.2lf", wave.frequency);
        mvprintw(17, 24, "|");
        attron(A_INVIS);
        for (i = 0; i < 40; i++) {
            if (i < (int) wave.frequency * 40 / 300) {
                attron(COLOR_PAIR(3));
                mvprintw(17, 25 + i, "/");
                attroff(COLOR_PAIR(3));
            } else {
                attron(COLOR_PAIR(4));
                mvprintw(17, 25 + i, "-");
                attroff(COLOR_PAIR(4));
            }
        }
        attroff(A_INVIS);
        mvprintw(17, 64, "|");
        mvprintw(18, 24, "0                                     300");

        // duty cycle
        mvprintw(20, 2, "* Duty Cycle: %.2lf", wave.duty_cycle);
        mvprintw(20, 24, "|");
        attron(A_INVIS);
        for (i = 0; i < 40; i++) {
            if (i < (int) wave.duty_cycle * 40 / 100) {
                attron(COLOR_PAIR(3));
                mvprintw(20, 25 + i, "/");
                attroff(COLOR_PAIR(3));
            } else {
                attron(COLOR_PAIR(4));
                mvprintw(20, 25 + i, "-");
                attroff(COLOR_PAIR(4));
            }
        }
        attroff(A_INVIS);
        mvprintw(20, 64, "|");
        mvprintw(21, 24, "0                                     100");
    }
}

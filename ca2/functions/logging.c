#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

#include "logging.h"
#include "../main.h"

void NcursesInitialization() {
    int y_min, x_min, y_max, x_max;

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
    init_pair(2, COLOR_WHITE, COLOR_BLACK); // selected waveform
    init_pair(3, COLOR_BLACK, COLOR_GREEN); // percentage bar-positive
    init_pair(4, COLOR_BLACK, COLOR_RED);   // percentage bar-negative
    init_pair(5, COLOR_YELLOW, COLOR_WHITE); // warning message
    init_pair(6, COLOR_RED, COLOR_WHITE); // error message
    init_pair(7, COLOR_BLUE, COLOR_WHITE); // info message

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

void ClearLoggingLine() {
    int i;
    for (i = 0; i < getmaxx(stdscr) - 2; i++) {
        mvprintw(25, 2 + i, " ");
    }
}

void Error_SliceString() {
    ClearLoggingLine();

    attron(COLOR_PAIR(6));
    mvprintw(25, 2, "[Error] Invalid SliceString() arguments!");
    attroff(COLOR_PAIR(6));
    refresh();
    getch();
    exit(1);
}

void ArgumentInstructions() {
    clear();
    printw("help\n");
    printw("\t\t--h\t\tshow program argument instructions\n");
    printw("\t\t--fp\t\trun the program based on the data from a specific file\n");
    printw("\t\t--w\t\tselect a waveform (sine/rectangle/triangle/sawtooth) (default is sine)\n");
    printw("\t\t--a\t\treplace the default wave amplitude with your own value (default is 1)\n");
    printw("\t\t--f\t\treplace the default wave frequency with your own value (default is 1)\n");
    printw("\t\t--d\t\treplace the default wave duty cycle with your own value (default is 50)\n");
    printw("notes\n");
    printw("\t\t*\t--h, --fp cannot be used together with other arguments\n");
    printw("\t\t*\tincomplete or duplicate declarations are not allowed\n");
    printw("\t\t*\twave amplitude and frequency arguments only accept positive numeric values\n");
    printw("\t\t*\tthe allowed maximum amplitude and frequency are 2.5 and 300 correspondingly (if the input value\n");
    printw("\t\t\tis greater than the allowed maximum value, program will continue with the maximum value)\n");
    printw("\t\t*\tfile\n");
    printw("\t\t\t\t**\teach row defines a wave, maximum 10 rows\n");
    printw("\t\t\t\t**\tthe first column defines waveform,\n");
    printw("\t\t\t\t\t\t1 -> sine\n\t\t\t\t\t\t2 -> rectangle\n\t\t\t\t\t\t3 -> triangle\n\t\t\t\t\t\t4 -> sawtooth\n");
    printw("\t\t\t\t\tthe second column defines wave amplitude,\n");
    printw("\t\t\t\t\tthe third column defines wave frequency\n");
    printw("\t\t\t\t\tand the fourth column defines wave duty cycle\n");
    printw("\t\t\t\t\t(use 0 for default settings)\n");
    printw("\t\t\t\t**\tfile example\n");
    printw("\t\t\t\t\t--------------------\n");
    printw("\t\t\t\t\t../data.dat\n");
    printw("\t\t\t\t\t--------------------\n");
    printw("\t\t\t\t\t1\t\t2.5\t\t0\t\t40\n");
    printw("\t\t\t\t\t3\t\t2.32\t\t150.2\t\t60.2\n");
    printw("\t\t\t\t\t0\t\t0\t\t300.5\t\t0\n");
    printw("\t\t\t\t\t1\t\t3.5\t\t100\t\t23.3\n");
    printw("\t\t\t\t\t--------------------\n");
    printw("examples\n");
    printw("\t\t*\tvalid:\t\t./main --fp=../data.dat\n\t\t*\tvalid:\t\t./main --w=sine --f=16.5\n");
    printw("\t\t*\tinvalid:\t./main --fp --f=16.5\n\t\t*\tinvalid:\t./main --w=sine --w=rectangle\n");

    refresh();
    exit(0);
}

void Error_ProgramArguments() {
    ClearLoggingLine();

    attron(COLOR_PAIR(6));
    mvprintw(25, 2, "[Error] Invalid program arguments!");
    attroff(COLOR_PAIR(6));
    refresh();
    getch();
    exit(1);
}

void Error_OpenFile() {
    ClearLoggingLine();

    attron(COLOR_PAIR(6));
    mvprintw(25, 2, "[Error] Cannot open the file specified");
    attroff(COLOR_PAIR(6));
    refresh();
    getch();
    exit(1);
}

void Error_FileData() {
    ClearLoggingLine();

    attron(COLOR_PAIR(6));
    mvprintw(25, 2, "[Error] Something wrong with the file data!");
    attroff(COLOR_PAIR(6));
    refresh();
    getch();
    exit(1);
}

void Error_ArgumentValue() {
    ClearLoggingLine();

    attron(COLOR_PAIR(6));
    mvprintw(25, 2, "[Error] Invalid value exists!");
    attroff(COLOR_PAIR(6));
    refresh();
    getch();
    exit(1);
}

void Info_ProgramTerminated() {
    ClearLoggingLine();

    attron(COLOR_PAIR(7));
    mvprintw(25, 2, "[Info] Program terminated!");
    attroff(COLOR_PAIR(7));
    refresh();
    exit(1);
}

void Error_PCIAttach() {
    ClearLoggingLine();

    attron(COLOR_PAIR(6));
    mvprintw(25, 2, "[Error] PCIe pci_attach() error!");
    attroff(COLOR_PAIR(6));
    refresh();
    getch();
    exit(1);
}

void Error_PCIAttachDevice() {
    ClearLoggingLine();

    attron(COLOR_PAIR(6));
    mvprintw(25, 2, "[Error] PCIe pci_attach_device() error!");
    attroff(COLOR_PAIR(6));
    refresh();
    getch();
    exit(1);
}

void Error_PCIThreadControl() {
    ClearLoggingLine();

    attron(COLOR_PAIR(6));
    mvprintw(25, 2, "[Error] PCIe ThreadCtl() error!");
    attroff(COLOR_PAIR(6));
    refresh();
    getch();
    exit(1);
}

void Error_CreateTimer() {
    ClearLoggingLine();

    attron(COLOR_PAIR(6));
    mvprintw(25, 2, "[Error] Failed to create a timer!");
    attroff(COLOR_PAIR(6));
    refresh();
    getch();
    exit(1);
}

void Error_SetTimer() {
    ClearLoggingLine();

    attron(COLOR_PAIR(6));
    mvprintw(25, 2, "[Error] Failed to set the timer!");
    attroff(COLOR_PAIR(6));
    refresh();
    getch();
    exit(1);
}

void *UpdateDisplay() {
    int i;

    while (1) {
        // process information
        mvprintw(7, 2, "* Remaining Time for the");
        mvprintw(8, 2, "  Current Wave (sec):\t%d ", count_down);

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
            if (i < wave.amplitude * 40 / 2.5) {
                attron(COLOR_PAIR(3));
                mvprintw(14, 25 + i, " ");
                attroff(COLOR_PAIR(3));
            } else {
                attron(COLOR_PAIR(4));
                mvprintw(14, 25 + i, " ");
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
            if (i < wave.frequency * 40 / 300) {
                attron(COLOR_PAIR(3));
                mvprintw(17, 25 + i, " ");
                attroff(COLOR_PAIR(3));
            } else {
                attron(COLOR_PAIR(4));
                mvprintw(17, 25 + i, " ");
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
            if (i < wave.duty_cycle * 40 / 100) {
                attron(COLOR_PAIR(3));
                mvprintw(20, 25 + i, " ");
                attroff(COLOR_PAIR(3));
            } else {
                attron(COLOR_PAIR(4));
                mvprintw(20, 25 + i, " ");
                attroff(COLOR_PAIR(4));
            }
        }
        attroff(A_INVIS);
        mvprintw(20, 64, "|");
        mvprintw(21, 24, "0                                     100");

        refresh();
    }
}

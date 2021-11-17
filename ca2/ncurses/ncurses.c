#include <stdlib.h>
#include <ncurses.h> // cc -o main main.c -lncurses

int main() {
    WINDOW *win;
    int y_min, x_min, y_max, x_max;

    initscr();
    refresh();

    getbegyx(stdscr, y_min, x_min);
    getmaxyx(stdscr, y_max, x_max);

    if (y_max - y_min < 30 || x_max - x_min < 71) {
        printw("Terminal too small!");
        getch();
        exit(1);
    }

    win = newwin(y_max - y_min, x_max - x_min, 0, 0);
    box(win, 0, 0);

    // title
    mvprintw(1, x_max / 2 - 4, "Pendulum");
    mvhline(2, 1, '-', x_max - 2);

    // process information
    mvprintw(3, 5, "Process Information");
    mvhline(4, 1, '-', 26);
    mvprintw(5, 2, "* Total Wave Count:\t%d", 6);   // Initialize once at the start
    mvprintw(6, 2, "* Current Wave Index:\t%d", 1); // Requires update
    mvprintw(7, 2, "* Remaining Time for");
    mvprintw(8, 2, "  the Current Wave:\t%ds", 3);  // Requires update
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

    wrefresh(win);
    getch();
    endwin();
    return 0;
}

#include <ncurses.h>
#include <locale.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <math.h>

#include "drawfunctions.h"
#include "inputfunctions.h"

using namespace std;

int main()
{	
    setlocale(LC_CTYPE, ""); // Set locale so we can display UTF-8 chars.

    float cputemp;
    float cpusmth = 0;
    
    float gputemp;
    float gpusmth = 0;


    initscr();		    // Start curses mode
    start_color();

    short unsigned int maxy,maxx;
    getmaxyx(stdscr, maxy, maxx);

    curs_set(0);
    noecho();

    while(true){
        getmaxyx(stdscr, maxy, maxx);
        erase();
        for(short int x=0; x<=10; x++){
	    cputemp = readf("/sys/class/hwmon/hwmon0/temp2_input");
            cpusmth = (cputemp*.05+cpusmth*.95);

	    gputemp = readf("/sys/class/hwmon/hwmon1/temp2_input");
            gpusmth = (gputemp*.05+gpusmth*.95);

            delln(maxy-2, 1, maxy*8,2);
            addln(maxy-2, 1, cpusmth/90*maxy*8,2);
            mvprintw(maxy-1, 1, "^^cpu");

            delln(maxy-2, 7, maxy*8,2);
            addln(maxy-2, 7, (gpusmth/90)*maxy*8,2);
            mvprintw(maxy-1, 7, "^^gpu");

            refresh();
            
            usleep(25000);
        }
    }

    endwin();			// End curses mode
    
    return 0;
}

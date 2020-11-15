#include <ncurses.h>
#include <locale.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <math.h>
#include <string.h>

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
            

            for(short int labelheight=0; labelheight<=90;labelheight+=10){
                mvprintw(maxy-(labelheight*maxy/90)-2, 1, "%d-", labelheight);
            }

            delln(maxy-2, 4, maxy*8,2);
            addln(maxy-2, 4, cpusmth/90*maxy*8,2);
            mvprintw(maxy-1, 4, "^^cpu");

            delln(maxy-2, 9, maxy*8,2);
            addln(maxy-2, 9, (gpusmth/90)*maxy*8,2);
            mvprintw(maxy-1, 9, "^^gpu");

            refresh();
            
            usleep(25000);
        }
    }

    endwin();			// End curses mode
    
    return 0;
}

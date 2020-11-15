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
    float cputempsmth = 0;
    
    float gputemp;
    float gputempsmth = 0;

    float cpusage;
    float cpusagesmth = 0;

    float gpusage;
    float gpusagesmth = 0;


    initscr();		    // Start curses mode

    short unsigned int maxy,maxx;
    getmaxyx(stdscr, maxy, maxx);

    curs_set(0);
    noecho();

    while(true){
        getmaxyx(stdscr, maxy, maxx);
        erase();
        for(short int x=0; x<=10; x++){
	    cputemp = readf("/sys/class/hwmon/hwmon0/temp2_input", 1000);
            cputempsmth = (cputemp*.05+cputempsmth*.95);

	    gputemp = readf("/sys/class/hwmon/hwmon2/temp2_input", 1000);
            gputempsmth = (gputemp*.05+gputempsmth*.95);
            

            cpusage = readf("/sys/class/hwmon/hwmon0/temp2_input", 1000);
            cpusagesmth = (cpusage*.05+cpusagesmth*.95);

	    gpusage = readf("/sys/class/hwmon/hwmon2/device/gpu_busy_percent");
            gpusagesmth = (gpusage*.05+gpusagesmth*.95);
            


            for(short int labelheight=0; labelheight<=90;labelheight+=10){
                mvprintw(maxy-(labelheight*(maxy-3)/90)-2, 0, "%dC-", labelheight);
            }

            delln(maxy-2, 4, maxy*8,2);
            addln(maxy-2, 4, cputempsmth/90*(maxy-3)*8,2);
            mvprintw(maxy-1, 4, "^^cpu");

            delln(maxy-2, 9, maxy*8,2);
            addln(maxy-2, 9, (gputempsmth/90)*(maxy-3)*8,2);
            mvprintw(maxy-1, 9, "^^gpu");


            for(short int labelheight=0; labelheight<=100;labelheight+=10){
                mvprintw(maxy-(labelheight*(maxy-3)/100)-2, 14, "%dp-", labelheight);
            }

            //delln(maxy-2, 18, maxy*8,2);
            //addln(maxy-2, 18, cpusagesmth/100*(maxy-10)*8,2);
            //mvprintw(maxy-1, 18, "^^cpu");

            delln(maxy-2, 18, maxy*8,2);
            addln(maxy-2, 18, (gpusagesmth/100)*(maxy-3)*8,2);
            mvprintw(maxy-1, 18, "^^gpu");
            refresh();
            
            usleep(25000);
        }
    }

    endwin();			// End curses mode
    
    return 0;
}

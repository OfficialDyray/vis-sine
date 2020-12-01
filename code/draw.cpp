#include <ncurses.h> //include libraries for basic output and setting the locale
#include <locale.h>

#include <iostream> //libraries for file manipulation and sorting
#include <fstream>
#include <sstream>

#include <unistd.h> //libraries for other basic functions
#include <math.h>
#include <string.h>

#include "outputfunctions.h" //include custom code
#include "inputfunctions.h"

using namespace std;

int main()
{	
    setlocale(LC_CTYPE, ""); // Set locale so we can display UTF-8 chars.

    int cpusage, cputemp, gpusage, gputemp, memfree;
    
    unsigned int cpui , pcpui, cput, pcput;

    float cpusagesmth = 0;

    float cputempsmth = 0;
    
    float gpusagesmth = 0;

    float gputempsmth = 0;

    float memfreesmth = 0;


    initscr();		    // Start curses mode

    short unsigned int maxy,maxx;
    getmaxyx(stdscr, maxy, maxx);

    curs_set(0);
    noecho();

    while(true){
        getmaxyx(stdscr, maxy, maxx);

        getcpusage(&cput, &cpui);
        if(cput!=pcput && cpui!=pcpui){
            cpusage = 100-(cpui-pcpui)*100/(cput-pcput);
            pcpui=cpui;
            pcput=cput;
        }

        erase();
        for(short int x=0; x<=10; x++){

	    cputemp = readf("/sys/class/hwmon/hwmon0/temp2_input", 1000);
            cputempsmth = cputemp*.05+cputempsmth*.95;

	    gputemp = readf("/sys/class/hwmon/hwmon1/temp2_input", 1000);
            gputempsmth = gputemp*.05+gputempsmth*.95;

	    gpusage = readf("/sys/class/hwmon/hwmon1/device/gpu_busy_percent");
            gpusagesmth = gpusage*.05+gpusagesmth*.95;
            
            memfree = readmem();
            memfreesmth = memfree*.05+memfreesmth*.95;

            cpusagesmth = cpusage*.05f+cpusagesmth*.95f;

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


            delln(maxy-2, 18, maxy*8,2);
            addln(maxy-2, 18, (cpusagesmth/100.0)*(maxy-3)*8,2);
            mvprintw(maxy-1, 18, "^^cpu");

            delln(maxy-2, 23, maxy*8,2);
            addln(maxy-2, 23, (gpusagesmth/100.0)*(maxy-3)*8,2);
            mvprintw(maxy-1, 23, "^^gpu");

            delln(maxy-2, 28, maxy*8,2);
            addln(maxy-2, 28, (memfreesmth/100.0)*(maxy-3)*8,2);
            mvprintw(maxy-1, 28, "^^mem");

            refresh();
            
            usleep(25000);
        }
    }

    endwin();			// End curses mode
    
    return 0;
}

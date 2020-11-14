using namespace std;

int addln(short unsigned int starty, short unsigned int startx, int height, short unsigned width=1){ //insert a bar at y,x going up "height" amount. 1 is 1/8 of a bar and 8 is one bar

    /*unicode character 2581-88 for higher resolution bars. Starts with a blank character for easier manipulation*/
    const char* partblock [] = {" ","▁","▂","▃","▄","▅","▆","▇","█"};

    int part = height % 8;
    int whole = (height - part)/8;

    for(short int currwidth = 0; currwidth<width; currwidth++){
        for(short int currwhole=0; currwhole < whole; currwhole++){
            mvprintw(starty - currwhole, startx+currwidth, partblock[8]);
        }
        mvprintw(starty-whole, startx+currwidth, partblock[part]);
    }
    return 0;
}

int delln(short unsigned int starty, short unsigned int startx, int height, short unsigned width=1){
    for(short int currwidth = 0; currwidth<width; currwidth++){
        for(int x=0; x <= height; x+=8){
            mvaddch(starty - x/8, startx+currwidth, ' ');
        }
    }
    return 0;
}

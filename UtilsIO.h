#ifndef UTILSIO_H
#define UTILSIO_H

#include <termios.h>
#include <unistd.h>


char getch() { // equivalent to getch() in conio.h for linux/unix
    char buf = 0;
    struct termios old = {0};
    tcgetattr(STDIN_FILENO, &old);        
    old.c_lflag &= ~ICANON;               
    old.c_lflag &= ~ECHO;                 
    tcsetattr(STDIN_FILENO, TCSANOW, &old);
    read(STDIN_FILENO, &buf, 1);          
    old.c_lflag |= ICANON;                
    old.c_lflag |= ECHO;                 
    tcsetattr(STDIN_FILENO, TCSANOW, &old);
    return buf;
}




#endif // UTILSIO_H